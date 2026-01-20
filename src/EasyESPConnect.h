#ifndef EASY_ESP_CONNECT_H
#define EASY_ESP_CONNECT_H

#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <Preferences.h>
#include <ESPmDNS.h>

// Comment this line to remove all Serial debugging and save Flash/RAM
#define EASY_ESP_DEBUG 

class EasyESPConnect {
public:
    EasyESPConnect(uint8_t resetPin = 27);

    // Optimized with const String& to save RAM
    void setCustomUI(const String& title, const String& token, const String& themeColour);
    
    void begin(const char* apName = "EasyESP-Config");
    void loop();
    void resetSettings();

private:
    uint8_t _resetPin;
    unsigned long _buttonPressTime;
    bool _apMode;
    bool _scanStarted;
    String _ssid, _pass;

    String _uiTitle = "EasyESP Connect";
    String _uiToken = "1xTARS1HA26AP2";
    String _uiColour = "#DFECEA";

    WebServer _server;
    DNSServer _dnsServer;
    Preferences _prefs;

    void _setupAP(const char* apName);
    void _handleRoot();
    void _handleScan();
    void _connectToWiFi();
    void _loadCredentials();
    void _saveCredentials(const String& s, const String& p);
    void _setupCaptivePortal();
    
    // Internal helper for conditional logging
    void log(const String& msg, bool newLine = true);
};

#endif
