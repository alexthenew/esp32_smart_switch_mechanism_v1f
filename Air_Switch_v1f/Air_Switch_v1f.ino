#include "HomeSpan.h"
#include <ESP32Servo.h>

// ==========WiFi settings==========
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ==========腳位與【獨立】角度設定==========
// --- 窗戶燈 (Pin 16) 專屬角度 ---
#define WINDOW_PIN  16
#define WINDOW_REST 90  
#define WINDOW_ON   55  
#define WINDOW_OFF  125  

// --- 門口燈 (Pin 17) 專屬角度 ---
#define DOOR_PIN    17
#define DOOR_REST   90  
#define DOOR_ON     55
#define DOOR_OFF    125

// ==========伺服馬達非阻塞控制模組 (FSM)==========
struct ServoSwitch : Service::Switch {
  int servoPin;
  int angleRest;
  int angleOn;
  int angleOff;
  int startDelay; 
 
  Servo myServo;
  SpanCharacteristic *power;
 
  boolean isMoving = false;
  unsigned long actionTimer = 0;
  int phase = 0; // 0:待機, 1:等待啟動, 2:推出中, 3:縮回中
  int targetAngle;
 
  ServoSwitch(int pin, int rest, int on, int off, int delay_ms = 0) : Service::Switch(){
    servoPin = pin;
    angleRest = rest;
    angleOn = on;
    angleOff = off;
    startDelay = delay_ms;
   
    targetAngle = angleRest;
   
    power = new Characteristic::On();
    myServo.setPeriodHertz(50);
  }

  boolean update(){
    if(isMoving) {
      Serial.println("馬達作動中，忽略重複指令");
      return true;
    }

    bool isOn = power->getNewVal();
    targetAngle = isOn ? angleOn : angleOff;
   
    Serial.printf("馬達 (Pin %d) 收到指令，將於 %d 毫秒後啟動\n", servoPin, startDelay);
   
    isMoving = true;
    phase = 1;
    actionTimer = millis();
   
    return true; 
  }

  void loop(){
    if(!isMoving) return;

    unsigned long currentTime = millis();

    // 階段 1 -> 階段 2 (等待時間結束，通電並推動)
    if(phase == 1 && (currentTime - actionTimer >= startDelay)){
      myServo.attach(servoPin, 500, 2400);
      myServo.write(targetAngle);
      phase = 2;
      actionTimer = currentTime;
    }
   
    // 階段 2 -> 階段 3 (推滿 400ms 後，準備縮回)
    else if(phase == 2 && (currentTime - actionTimer >= 400)){
      myServo.write(angleRest);  
      phase = 3;                  
      actionTimer = currentTime;  
    }
   
    // 階段 3 -> 待機 (縮回滿 400ms 後，斷電)
    else if(phase == 3 && (currentTime - actionTimer >= 400)){
      myServo.detach();          
      isMoving = false;          
      phase = 0;                  
      Serial.printf("馬達 (Pin %d) 動作完成並斷電\n", servoPin);
    }
  }
};

// ==========系統初始化==========
void setup() {
  Serial.begin(115200);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  homeSpan.setWifiCredentials(ssid, password);
  homeSpan.setPairingCode("11122333");

  homeSpan.begin(Category::Bridges, "Dorm Hub");

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name("Dorm Hub");

  // --- 配件 1: 窗戶燈 (立刻啟動延遲 0ms) ---
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name("Window Light");
    new ServoSwitch(WINDOW_PIN, WINDOW_REST, WINDOW_ON, WINDOW_OFF, 0);

  // --- 配件 2: 門口燈 (延遲 500ms 避開電流尖峰) ---
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name("Door Light");  
    new ServoSwitch(DOOR_PIN, DOOR_REST, DOOR_ON, DOOR_OFF, 500);  
}

void loop() {
  homeSpan.poll();
}
