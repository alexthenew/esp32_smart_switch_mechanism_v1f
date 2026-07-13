<div align="center">
  <img src="https://github.com/user-attachments/assets/c2c642bc-b950-4546-a7f7-ddeab13150f7" width="400">
  <img src="https://github.com/user-attachments/assets/e9dcf80e-d102-453d-8519-50d3614e7a82" width="400">
</div>

# AirSwitch : ESP32 Smart Switch Mechanism

A HomeKit compatible non-invasive smart switch mechanism, powered by ESP32.

This project is an Apple HomeKit-enabled smart switch pusher built with ESP32 and the HomeSpan library. It upgrades traditional lighting into smart home appliances by physically toggling wall switches using servo motors.

---

## ✨ Features
* **Native HomeKit Support**: Direct pairing with Apple devices without requiring additional bridges like Homebridge.
* **Non-blocking State Machine**: Utilizes `millis()` instead of `delay()` to ensure uninterrupted HomeSpan background connections.
* **Inrush Current Protection**: If both motors receive commands simultaneously, their startup times are offset by 500ms to protect the ESP32's power stability.
* **Auto-detach Sleep Mode**: Motors automatically `detach()` after toggling to prevent continuous power draw, overheating, and unnecessary noise.

## 🔌 Hardware Configuration
* **Microcontroller**: ESP32
* **Actuators**: SG90 Servo Motor x 2

| Device Name | GPIO Pin | Rest Angle | On Angle | Off Angle | Startup Delay |
| :--- | :---: | :---: | :---: | :---: | :---: |
| Window Light | 16 | 90° | 55° | 125° | 0 ms |
| Door Light | 17 | 90° | 55° | 125° | 500 ms |

## 📱 Pairing Information
When adding the accessory in the Apple Home app, enter the following setup code:
* **Pairing Code**: `11122333`

## 🙏 Acknowledgments
* Apple HomeKit integration is powered by the awesome [HomeSpan](https://github.com/HomeSpan/HomeSpan) library.
* Servo motor control on ESP32 is handled by the [ESP32Servo](https://github.com/madhephaestus/ESP32Servo) library.
* The geometric wall art pattern on the 3D printed case was sourced from MakerWorld. (If you are the original author, please let me know so I can properly credit you!)

---

# 繁體中文說明 (Traditional Chinese)

## AirSwitch : ESP32 智能開關物理機構

這是一個基於 ESP32 與 HomeSpan 開發的 Apple HomeKit 智能開關推手專案。
透過伺服馬達物理推動牆壁開關，將傳統電燈升級為智慧家電。

## ✨ 核心特色
* **原生 HomeKit 支援**：不需透過 Homebridge 等額外橋接器，直接與 Apple 裝置配對。
* **非阻塞狀態機設計**：使用 `millis()` 取代 `delay()`，確保 HomeSpan 背景連線不中斷。
* **防電流尖峰機制**：兩組馬達若同時接收指令，會自動錯開 500ms 啟動，保護 ESP32 供電穩定。
* **自動斷電休眠**：馬達推動完成後會自動 `detach()`，避免持續通電發熱與不必要的雜音。

## 🔌 硬體配置
* **微控制器**：ESP32
* **執行設備**：SG90伺服馬達 (Servo Motor) x 2

| 設備名稱 | GPIO 腳位 | 待機角度 | 開啟角度 | 關閉角度 | 啟動延遲 |
| :--- | :---: | :---: | :---: | :---: | :---: |
| 窗戶燈 (Window Light) | 16 | 90° | 55° | 125° | 0 ms |
| 門口燈 (Door Light) | 17 | 90° | 55° | 125° | 500 ms |

## 📱 配對資訊
在 Apple「家庭」App 中加入配件時，請輸入以下配對碼：
* **Pairing Code**: `11122333`

## 🙏 鳴謝
* 本專案的 HomeKit 連線底層，高度仰賴強大的 [HomeSpan](https://github.com/HomeSpan/HomeSpan) 開源函式庫。
* 伺服馬達控制採用針對 ESP32 優化的 [ESP32Servo](https://github.com/madhephaestus/ESP32Servo) 函式庫。
* 3D 列印外殼上的牆面藝術圖騰取自 MakerWorld 的開源設計。（因遺失原模型連結，若您是原作者，歡迎聯繫我以補上正確的授權資訊！）
