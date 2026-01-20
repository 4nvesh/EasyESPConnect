#include "EasyESPConnect.h"
#include "EasyESPConnectUI.h"

EasyESPConnect::EasyESPConnect(uint8_t resetPin) : _server(80), _resetPin(resetPin) {
    _apMode = false;
    _scanStarted = false;
    _buttonPressTime = 0;
}

void EasyESPConnect::log(const String& msg, bool newLine) {
#ifdef EASY_ESP_DEBUG
    if (newLine) Serial.println(msg);
    else Serial.print(msg);
#endif
}

void EasyESPConnect::setCustomUI(const String& title, const String& token, const String& themeColour) {
    if (title.length() > 0) _uiTitle = title;
    if (token.length() > 0) _uiToken = token;
    if (themeColour.length() > 0) _uiColour = themeColour;
}

void EasyESPConnect::begin(const char* apName) {
    pinMode(_resetPin, INPUT_PULLUP);
    _prefs.begin("wifi-creds", false);
    _loadCredentials();

    if (_ssid.length() > 0) {
        log(String(F("Attempting to connect to: ")) + _ssid);
        _connectToWiFi();
    } else {
        _setupAP(apName);
    }
}

void EasyESPConnect::loop() {
    if (_apMode) {
        _dnsServer.processNextRequest();
        _server.handleClient();
    }

    if (digitalRead(_resetPin) == LOW) {
        if (_buttonPressTime == 0) _buttonPressTime = millis();
        if (millis() - _buttonPressTime > 5000) {
            log(F("Hardware reset triggered."));
            resetSettings();
        }
    } else {
        _buttonPressTime = 0;
    }
}

void EasyESPConnect::_setupAP(const char* apName) {
    _apMode = true;
    WiFi.mode(WIFI_AP);
    WiFi.softAP(apName);
    log(String(F("AP Started: ")) + apName);
    _setupCaptivePortal();
}

void EasyESPConnect::_setupCaptivePortal() {
    _dnsServer.start(53, "*", WiFi.softAPIP());
    _server.on("/", [this]() { _handleRoot(); });
    _server.on("/scan", [this]() { _handleScan(); });
    _server.on("/save", HTTP_POST, [this]() {
        _saveCredentials(_server.arg("ssid"), _server.arg("password"));
        _server.send(200, "text/html", success_html);
        delay(2000);
        ESP.restart();
    });
    _server.onNotFound([this]() { _handleRoot(); });
    _server.begin();
}

void EasyESPConnect::_handleRoot() {
    String html = index_html;
    html.replace(F("%TITLE%"), _uiTitle);
    html.replace(F("%TOKEN%"), _uiToken);
    html.replace(F("%THEME_COLOUR%"), _uiColour);
    _server.sendHeader(F("Cache-Control"), F("no-cache"));
    _server.send(200, "text/html", html);
}

void EasyESPConnect::_handleScan() {
    if (!_scanStarted) {
        WiFi.scanNetworks(true);
        _scanStarted = true;
        _server.send(200, "application/json", "{\"status\":\"scanning\"}");
        return;
    }
    int n = WiFi.scanComplete();
    if (n == WIFI_SCAN_RUNNING) {
        _server.send(200, "application/json", "{\"status\":\"scanning\"}");
    } else {
        String json = "{\"status\":\"done\",\"networks\":[";
        for (int i = 0; i < n; i++) {
            json += "\"" + WiFi.SSID(i) + "\"" + (i < n - 1 ? "," : "");
        }
        json += "]}";
        WiFi.scanDelete();
        _scanStarted = false;
        _server.send(200, "application/json", json);
    }
}

void EasyESPConnect::_connectToWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid.c_str(), _pass.c_str());
    int count = 0;
    while (WiFi.status() != WL_CONNECTED && count < 20) {
        delay(500);
        log(".", false);
        count++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        log(String(F("\nConnected! IP: ")) + WiFi.localIP().toString());
    } else {
        _setupAP("EasyESP-Recovery");
    }
}

void EasyESPConnect::resetSettings() {
    _prefs.clear();
    delay(500);
    ESP.restart();
}

void EasyESPConnect::_loadCredentials() {
    _ssid = _prefs.getString("ssid", "");
    _pass = _prefs.getString("pass", "");
}

void EasyESPConnect::_saveCredentials(const String& s, const String& p) {
    _prefs.putString("ssid", s);
    _prefs.putString("pass", p);
}
