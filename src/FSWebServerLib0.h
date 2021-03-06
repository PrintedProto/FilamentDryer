// FSWebServerLib.h

#ifndef _FSWEBSERVERLIB_h
#define _FSWEBSERVERLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "TimeLib.h"
//#include "NtpClientLib.h"
#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ESP8266mDNS.h"
#include "FS.h"
#include "AsyncWebSocket.h"
#include "Ticker.h"
#include "ArduinoOTA.h"
#include "ArduinoJson.h"
#include "german.h"
#include "RtcDS3231.h"

#define RELEASE  // Comment to enable debug output

#define DBG_OUTPUT_PORT Serial

#ifndef RELEASE
#define DEBUGLOG(...) DBG_OUTPUT_PORT.printf(__VA_ARGS__)
#else
#define DEBUGLOG(...)
#endif

#define CONNECTION_LED -1 // Connection LED pin (Built in). -1 to disable
#define AP_ENABLE_BUTTON -1 // Button pin to enable AP during startup for configuration. -1 to disable


#define CONFIG_FILE "/config.json"
#define SECRET_FILE "/secret.json"

typedef struct {
    String ssid;
    String password;
    IPAddress  ip;
    IPAddress  netmask;
    IPAddress  gateway;
    IPAddress  dns;
    bool dhcp;
    String ntpServerName;
    long updateNTPTimeEvery;
    long timezone;
    bool daylight;
    String deviceName;
} strConfig;

typedef struct {
    String APssid = "Filadry"; // ChipID is appended to this name
    String APpassword = "12345678";
    bool APenable = false; // AP disabled by default
} strApConfig;

typedef struct {
    bool auth;
    String wwwUsername;
    String wwwPassword;
} strHTTPAuth;


class AsyncFSWebServer : public AsyncWebServer {
public:
    AsyncFSWebServer(uint16_t port);
    void begin(FS* fs);
    void handle();
    bool getTime();
    void showTime();
    void Word_Init(German * _wordAddress);
    RtcDateTime _curTime; //RtcDateTime(year, month, dayOfMonth, hour, minute, second);
    German * _word;
    bool chkTk();
    static bool _secondFlag;
    void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);


protected:
    strConfig _config; // General and WiFi configuration
    strApConfig _apConfig; // Static AP config settings
    strHTTPAuth _httpAuth;
    FS* _fs;
    long wifiDisconnectedSince = 0;
    String _browserMD5 = "";
    uint32_t _updateSize = 0;

    WiFiEventHandler onStationModeConnectedHandler, onStationModeDisconnectedHandler;

    //uint currentWifiStatus;

    Ticker _secondTk;

    AsyncWebSocket _ws = AsyncWebSocket("/ws");// url will be ws://esp-ip/ws
    AsyncEventSource _evs = AsyncEventSource("/events");

    //void sendTimeData();
    bool load_config();
    void defaultConfig();
    bool save_config();
    bool loadHTTPAuth();
    bool saveHTTPAuth();
    void configureWifiAP();
    void configureWifi();
    //void ConfigureOTA(String password);
    void serverInit();

    void onWiFiConnected(WiFiEventStationModeConnected data);
    void onWiFiDisconnected(WiFiEventStationModeDisconnected data);

    //static void s_secondTick(void* arg);
    static void s_secondTick();


    String getMacAddress();

    bool checkAuth(AsyncWebServerRequest *request);
    void handleFileList(AsyncWebServerRequest *request);
    //void handleFileRead_edit_html(AsyncWebServerRequest *request);
    bool handleFileRead(String path, AsyncWebServerRequest *request);
    void handleFileCreate(AsyncWebServerRequest *request);
    void handleFileDelete(AsyncWebServerRequest *request);
    void handleFileUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
    void send_general_configuration_values_html(AsyncWebServerRequest *request);
    void send_network_configuration_values_html(AsyncWebServerRequest *request);
    void send_connection_state_values_html(AsyncWebServerRequest *request);
    void send_information_values_html(AsyncWebServerRequest *request);
    void send_NTP_configuration_values_html(AsyncWebServerRequest *request);
    void send_network_configuration_html(AsyncWebServerRequest *request);
    void send_general_configuration_html(AsyncWebServerRequest *request);
    void send_NTP_configuration_html(AsyncWebServerRequest *request);
    void restart_esp(AsyncWebServerRequest *request);
    void send_wwwauth_configuration_values_html(AsyncWebServerRequest *request);
    void send_wwwauth_configuration_html(AsyncWebServerRequest *request);
    void send_update_firmware_values_html(AsyncWebServerRequest *request);
    void setUpdateMD5(AsyncWebServerRequest *request);
    void updateFirmware(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
    void disConnect(AsyncWebServerRequest *request);
    void handleTime(AsyncWebServerRequest *request);
    void toggleTicker(bool state, float sec);


    static String urldecode(String input); // (based on https://code.google.com/p/avr-netino/)
    static unsigned char h2int(char c);
    static boolean checkRange(String Value);
};

extern AsyncFSWebServer ESPHTTPServer;
//extern AsyncWebSocket ws;

#endif // _FSWEBSERVERLIB_h
