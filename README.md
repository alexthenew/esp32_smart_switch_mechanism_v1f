# esp32_smart_switch_mechanism_v1f
A HomeKit compatible non-invasive smart switch mechanism, powered by ESP 32.

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
* **Pairing Code**: `111-22-333`
