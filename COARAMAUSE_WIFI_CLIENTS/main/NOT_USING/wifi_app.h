
#ifndef MAIN_WIFI_APP_H_
#define MAIN_WIFI_APP_H_

#include "esp_netif.h"




// Callback typedef
typedef void (*wifi_connected_event_callback_t)(void);


// ---------------------------------------------------------
// ** CHANGE BELOW'S SETTINGS WITH wifi_app_X.h FILES !! **

// WiFi application settings
#define WIFI_AP_SSID                "ESP32_AP_2"            // AP name
#define WIFI_AP_PASSWORD            "password"              // AP password
#define WIFI_AP_CHANNEL             1                   // AP channel
#define WIFI_AP_SSID_HIDDEN         0                   // AP visibility
#define WIFI_AP_MAX_CONNECTIONS     10                   // AP max clients
#define WIFI_AP_BEACON_INTERVAL     100                 // AP beacon: 100 milliseconds recommended
#define WIFI_AP_IP                  "192.168.0.2"       // AP default IP
#define WIFI_AP_GATEWAY             "192.168.0.2"       // AP default Gateway (should be the same as the IP)
#define WIFI_AP_NETMASK             "255.255.255.0"     // AP netmask
#define WIFI_AP_BANDWIDTH           WIFI_BW_HT20        // AP bandwidth 20 MHz (40 MHz is the other option)
#define WIFI_STA_POWER_SAVE         WIFI_PS_NONE        // Power save not used
#define MAX_SSID_LENGTH             32                  // IEEE standard maximum
#define MAX_PASSWORD_LENGTH         64                  // IEEE standard maximum
#define MAX_CONNECTION_RETRIES      5                   // Retry number on disconnect



// --------------------------------
// < NETWORK INTERFACE >

// netif object for the Station and Access Point
extern esp_netif_t* esp_netif_sta;
extern esp_netif_t* esp_netif_ap;



/**
 * Starts the WiFi RTOS task
 */
void wifi_app_start(void);






#endif /* MAIN_WIFI_APP_H_ */




























