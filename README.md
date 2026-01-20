![Maintained](https://img.shields.io/badge/Maintained%3F-yes-green.svg)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)
![Framework](https://img.shields.io/badge/Framework-Arduino-orange.svg)
![Version](https://img.shields.io/badge/Version-1.1.0-red.svg)

# EasyESPConnect -- ESP32 WiFi Manager (NVS Based, Lightweight)

**EasyESPConnect** is a fast, lightweight, and production-ready **ESP32
WiFi Manager library** that uses **native NVS (Preferences)** instead of
SPIFFS/LittleFS.

Designed for **Arduino Library Manager visibility**, minimal RAM usage,
and real-world IoT products, EasyESPConnect provides a **modern captive
portal UI**, async WiFi scanning, and hardware-based factory reset ---
without filesystem overhead.

> 🔑 Perfect for ESP32 IoT, smart devices, consumer electronics, and
> low-memory applications.

------------------------------------------------------------------------

## 🚀 Features

-   ✅ **ESP32 WiFi Manager (No SPIFFS / LittleFS)**
-   ✅ **Uses Native NVS (Preferences)**
-   ✅ **Ultra-Low RAM & Flash Usage**
-   ✅ **Async WiFi Network Scanning**
-   ✅ **Modern Mobile-First Captive Portal UI**
-   ✅ **Hardware Factory Reset Button**
-   ✅ **Arduino IDE & Arduino Library Manager Compatible**

------------------------------------------------------------------------

## 📦 Installation

### 1️⃣ Arduino Library Manager (Recommended)
1.  Open **Arduino IDE**
2.  Go to\
    `Sketch → Include Library → Manage Libraries…`
3.  Search for **EasyESPConnect**
4.  Click **Install**

### 2️⃣ Manual Installation

1.  Download `EasyESPConnect.zip`
2.  Open Arduino IDE
3.  Go to\
    `Sketch → Include Library → Add .ZIP Library…`
4.  Select the downloaded ZIP file

> ✔ No additional dependencies required

------------------------------------------------------------------------

## 🧠 Why EasyESPConnect?

Most ESP32 WiFi managers rely on filesystems that increase flash usage
and complexity.

EasyESPConnect: - Uses **ESP32 Preferences (NVS)** --- faster & safer -
Avoids filesystem corruption risks - Boots faster - Uses less RAM -
Looks professional on mobile devices

------------------------------------------------------------------------

## 🛠️ Basic Usage Example

``` cpp
#include <EasyESPConnect.h>

// Optional reset button pin (default: GPIO 27)
EasyESPConnect easyConn(27);

void setup() {
    Serial.begin(115200);

    // Optional UI customization
    easyConn.setCustomUI(
        "My Smart Device",
        "TARS-X2026",
        "#ADD7D2"
    );

    // Start WiFi or Captive Portal
    easyConn.begin("EasyESP-Config");
}

void loop() {
    // Required for captive portal & reset logic
    easyConn.loop();

    if (WiFi.status() == WL_CONNECTED) {
        // Your IoT logic here
    }
}
```

------------------------------------------------------------------------

## 🔄 Connection Flow

1.  Device boots
2.  Checks saved WiFi credentials in NVS
3.  Attempts connection (10 seconds)
4.  If failed → Captive Portal starts
5.  User selects WiFi & enters password
6.  Credentials saved to NVS
7.  Device restarts in Station Mode

------------------------------------------------------------------------

## 🔘 Factory Reset Button

-   Hold reset button for **5 seconds**
-   Clears all saved WiFi data from NVS
-   Restarts captive portal
-   Fully non-blocking implementation

(Default pin: **GPIO 27**)

------------------------------------------------------------------------

## 📊 Comparison

| Feature | EasyESPConnect | WiFiManager | AutoConnect |
| :--- | :--- | :--- | :--- |
| **Storage Method** | **NVS (Fastest)** | Filesystem (Slower) | Filesystem (Complex) |
| **RAM Usage** | **Ultra-Low** | Moderate | High |
| **UI Design** | **Modern / Responsive** | Classic / Basic | Business / Dense |
| **Async Scanning** | **Yes** | No | No |

------------------------------------------------------------------------

## 🧩 Customization

Change UI branding with **one function call**: - Device name - Token - Theme color

No HTML editing required.

------------------------------------------------------------------------

## 📚 Supported Hardware

-   ESP32 (All variants)
-   Arduino IDE
-   PlatformIO (Arduino framework)

> ❌ ESP8266 not supported

------------------------------------------------------------------------

## 📜 License

MIT License

------------------------------------------------------------------------

## ⭐ Keywords (Arduino Library Manager)

ESP32 WiFi Manager, ESP32 NVS WiFi, Captive Portal ESP32, Arduino ESP32
WiFi, ESP32 Preferences, IoT WiFi Provisioning
