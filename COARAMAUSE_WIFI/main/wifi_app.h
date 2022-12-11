
#ifndef MAIN_WIFI_APP_H_
#define MAIN_WIFI_APP_H_

#include "esp_netif.h"




// Callback typedef
typedef void (*wifi_connected_event_callback_t)(void);


// ---------------------------------------------------------
// ** CHANGE BELOW'S SETTINGS WITH wifi_app_X.h FILES !! **

// WiFi application settings
#define WIFI_AP_SSID                "ESP32_AP_1"            // AP name
#define WIFI_AP_PASSWORD            "password"              // AP password
#define WIFI_AP_CHANNEL             1                   // AP channel
#define WIFI_AP_SSID_HIDDEN         0                   // AP visibility
#define WIFI_AP_MAX_CONNECTIONS     10                   // AP max clients
#define WIFI_AP_BEACON_INTERVAL     100                 // AP beacon: 100 milliseconds recommended
#define WIFI_AP_IP                  "192.168.42.1"       // AP default IP
#define WIFI_AP_GATEWAY             "192.168.42.1"       // AP default Gateway (should be the same as the IP)

// NETMASK IS OPENED ! 
#define WIFI_AP_NETMASK             "255.255.0.0"     // AP netmask

#define WIFI_AP_BANDWIDTH           WIFI_BW_HT20        // AP bandwidth 20 MHz (40 MHz is the other option)
#define WIFI_STA_POWER_SAVE         WIFI_PS_NONE        // Power save not used
#define MAX_SSID_LENGTH             32                  // IEEE standard maximum
#define MAX_PASSWORD_LENGTH         64                  // IEEE standard maximum
#define MAX_CONNECTION_RETRIES      5                   // Retry number on disconnect


#define TCP_PORT 3333  // TCP server port number


#define MAX_SOCKET_COUNTS 1


#define KEEPALIVE_IDLE              5
#define KEEPALIVE_INTERVAL          5
#define KEEPALIVE_COUNT             3





#define SOCKET int
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define GETSOCKETERRNO() (errno)





// --------------------------------
// < NETWORK INTERFACE >

// netif object for the Station and Access Point
extern esp_netif_t* esp_netif_sta;
extern esp_netif_t* esp_netif_ap;




// -------------------------------
// < SOCKET STRUCT > 
typedef struct wifi_socket_connect {

    bool isConnected;

    int macAddr[6];
    int devIndex;

    char ipAddr[128];

    int listen_sock;
    struct sockaddr_in* dest_addr;

    int connect_sock;
    //struct sockaddr_in6* source_addr;

    uint addr_len;

    int errBind;
    int errListen;


} wifi_socket_connect_t;








// -------------------------------
// < DEFINING MESSAGE STRUCTURE > 

/**
 * Message IDs for the WiFi application task
 * @note Expand this based on your application requirements.
 */
typedef enum wifi_app_message {

	WIFI_APP_MSG_START_HTTP_SERVER = 0,
	WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER,
	WIFI_APP_MSG_STA_CONNECTED_GOT_IP,
	WIFI_APP_MSG_USER_REQUESTED_STA_DISCONNECT,
	WIFI_APP_MSG_LOAD_SAVED_CREDENTIALS,
	WIFI_APP_MSG_STA_DISCONNECTED,
    WIFI_APP_MSG_SCAN_SSID,
    WIFI_APP_MSG_SOCKET_CONNECTION,
    WIFI_APP_MSG_SOCKET_COMMUNICATION,
    WIFI_APP_MSG_SOCKET_DISCONNECTION,

} wifi_app_message_e;




// --------------------------------------
// < MESSAGE QUEUE? >
// : MESSAGE WILL BE EXCHANGED BETWEEN TASK AND WIFI APPLICATION,
//   AND IT WILL BE STORED USING QUEUE
//
//

/**
 * Structure for the message queue
 * @note Expand this based on application requirements e.g. add another type and parameter as required
 */
typedef struct wifi_app_queue_message {

	wifi_app_message_e msgID;

} wifi_app_queue_message_t;





/**
 * Sends a message to the queue
 * @param msgID message ID from the wifi_app_message_e enum.
 * @return pdTRUE if an item was successfully sent to the queue, otherwise pdFALSE.
 * @note Expand the parameter list based on your requirements e.g. how you've expanded the wifi_app_queue_message_t.
 */
BaseType_t wifi_app_send_message(wifi_app_message_e msgID);




// ----------------------------
// < RTOS TASK START >


/**
 * Starts the WiFi RTOS task
 */
void wifi_app_start(void);




// -----------------------------
// < GETTING WIFI INFORMATION >

/**
 * Gets the wifi configuration
 */
wifi_config_t* wifi_app_get_wifi_config(void);





/**
 * Sets the callback function.
 */
void wifi_app_set_callback(wifi_connected_event_callback_t cb);




/**
 * Calls the callback function.
 */
void wifi_app_call_callback(void);




// GETTING CURRENT MODULE NUMBER
int wifi_get_Unit_Number(void);


// GETTING EXCLUDED INDEX ARRAY OF UNITS
int* wifi_get_Ex_Unit_Numbers(int mainUnitNum);




// HELPER FUNCTION FOR CHECKING INPUT IS INTEGER OF NOT
// https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
bool digit_check(char key[]);



//void initializeSockets();



#endif /* MAIN_WIFI_APP_H_ */




























