#include <EasyESPConnect.h>

// Define the reset pin (optional, defaults to 27 or GPIO 27)
EasyESPConnect easyConn(27); 

void setup() {
    Serial.begin(115200);
    // Customize the UI text and theme colour
    // Provide: Title, "", Colour
    easyConn.setCustomUI(
        "EasyESP Portal", // Device Name, example "Tars Smart Planter"
        "", // Access Token, example "1TARSX2026"
        "" // theme colour, example "#ADD7D2" or "" for default theme colour
    );

    easyConn.begin("EasyESP Connect");
}

void loop() {
    // Keeps the captive portal and reset button alive
    easyConn.loop(); 

    if (WiFi.status() == WL_CONNECTED) {
        // Your code here (e.g., send data to MQTT or Web)
    }
}