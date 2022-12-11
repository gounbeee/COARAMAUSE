
// ---------------------
// < WIFI IN OSI MODEL >
// https://www.controleng.com/articles/wi-fi-and-the-osi-model/

// All Wireless LANs operate on the Physical and Data Link layers, 
// layers 1 and 2. All Wi-Fi systems use these layers to format data and 
// control the data to conform with 802.11 standards. Medium arbitration-controlling 
// when the AP can access the medium and transmit or receive data-is done at these 
// two layers. We will discuss the very complex technique of wireless medium arbitration 
// in a future segment; for now, it is important to understand the functions of layers 1 and 2.
//
// The Physical layer, or PHY, is the medium through which communication is effected. 
// It is at this layer the transceiver is controlled to access the medium. We are primarily 
// concerned with the wireless medium. Unlike a bounded, wired medium, WLANs operate "over 
// the air" and are subject to an entirely different set of rules for accessing and controlling 
// the medium. For instance, wired networks have the ability to detect and mitigate data collisions; 
// wireless networks cannot detect collisions, instead, elaborate protocols are in place to allow 
// access and control of the medium and to avoid collisions. Wireless networks are also subject to 
// unintentional interference and intentional disruptions. Wired networks are relatively difficult 
// to hack into while wireless networks can be casually hacked by anyone with a wireless card within 
// range of an access point. These issues have provided developers with significant challenges to 
// overcome to ensure that WLANs are reliable and secure.
//
// The Data Link layer consists of two sublayers: the Logical Link Control (LLC) sublayer and the 
// Medium Access Control (MAC) sublayer. The LLC receives an IP packet from the Network layer above 
// it and encapsulates the data with addressing and control information. This packet, now called a 
// frame, is passed to the MAC, which modifies the addressing and control information in the frame 
// header to ensure the data is in the proper form for application to the Physical layer. The MAC 
// then passes the frame to the PHY, which modulates the data according to the PHY standard in use 
// (DSSS, OFDM), and transmits the bits as RF. The process is reversed at the receiving end.


// < Access Point Mode or Station Mode? >
// https://defineinstruments.com/blog/networking-iot-and-wifi-101/#:~:text=Station%20Mode%20(STA)%20is%20what,your%20WiFi%20network%20at%20home.
//
// Typically devices can run in one of 2 modes: Access Point Mode or Station Mode (often called 
// Client Mode). Station Mode (STA) is what most people would consider the normal mode for a WiFi 
// device. A device uses Station Mode to join a network that already exists, exactly like your 
// smartphone does when its connects to your WiFi network at home. In this instance your phone is 
// running in Station Mode.
//
// In Access Point Mode (AP) the device is the Access Point and so becomes an entity that everything 
// else can connect to, rather than it connecting to a network.


#include <stdbool.h>


// BASIC FUNCTIONALITIES FOR APPLICATION
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

// BASIC LOGGING FUNCTIONALITIES FOR LOGGING
#include "esp_err.h"
#include "esp_log.h"

// FOR "NETWORK" LAYER ? (IN BRIEF THOUGHT)
#include "esp_wifi.h"

// FOR "TRANSPORT" LAYER ? (IN BRIEF THOUGHT)
#include "lwip/netdb.h"
#include "lwip/err.h"
#include "lwip/sockets.h"



// "APPLICATION" LAYER ? (IN BRIEF THOUGHT)
//#include "app_nvs.h"
//#include "http_server.h"
//#include "rgb_led.h"
#include "tasks_common.h"
#include "wifi_app.h"




// DEFINE TAG NAME FOR DISPLAYING TO CONSOLE
static const char TAG [] = "WIFI_APP_STATION";




#define HOST_IP_ADDR "192.168.42.1"
#define PORT 3333


static const char *payload = "Message from ESP32 ";



/**
 * Main task for the WiFi application
 * @param pvParameters parameter which can be passed to the task
 */
static void wifi_app_task(void *pvParameters) {



    char rx_buffer[128];
    char host_ip[] = HOST_IP_ADDR;
    int addr_family = 0;
    int ip_protocol = 0;







    // const struct addrinfo hints = {
    //     .ai_family = AF_INET,
    //     .ai_socktype = SOCK_STREAM,
    // };
    // struct addrinfo *res;
    // struct in_addr *addr;
    // int s, r;


    // char recv_buf[64];



    while( 1 ) {


        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(host_ip);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;




        int sock =  socket(addr_family, SOCK_STREAM, ip_protocol);


        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }

        ESP_LOGI(TAG, "Socket created, connecting to %s:%d", host_ip, PORT);



        int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in6));


        if (err != 0) {
            ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
            break;
        }


        ESP_LOGI(TAG, "Successfully connected"); 




        while(1) {


            int err = send(sock, payload, strlen(payload), 0);

            if (err < 0) {
                ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                break;
            }




            int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);


            // Error occurred during receiving
            if (len < 0) {
                ESP_LOGE(TAG, "recv failed: errno %d", errno);
                break;
            }
            // Data received
            else {
                rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string

                // PRINTING OUT THE DATA
                ESP_LOGI(TAG, "RECEIVED DATA    %d   BYTES FROM    %s  !!", len, host_ip);
                ESP_LOGI(TAG, "THE DATA WAS... ");
                ESP_LOGI(TAG, "%s", rx_buffer);

            }

            vTaskDelay(2000 / portTICK_PERIOD_MS);





            // int err = getaddrinfo(WEB_SERVER, WEB_PORT, &hints, &res);


            // if(err != 0 || res == NULL) {
            //     ESP_LOGE(TAG, "DNS lookup failed err=%d res=%p", err, res);
            //     vTaskDelay(1000 / portTICK_PERIOD_MS);
            //     continue;
            // }


            // /* Code to print the resolved IP.
            //    Note: inet_ntoa is non-reentrant, look at ipaddr_ntoa_r for "real" code */

            // addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
            // ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", inet_ntoa(*addr));


            // s = socket(res->ai_family, res->ai_socktype, 0);


            // if(s < 0) {
            //     ESP_LOGE(TAG, "... Failed to allocate socket.");
            //     freeaddrinfo(res);
            //     vTaskDelay(1000 / portTICK_PERIOD_MS);
            //     continue;
            // }
            // ESP_LOGI(TAG, "... allocated socket");



            // if(connect(s, res->ai_addr, res->ai_addrlen) != 0) {
            //     ESP_LOGE(TAG, "... socket connect failed errno=%d", errno);
            //     close(s);
            //     freeaddrinfo(res);
            //     vTaskDelay(4000 / portTICK_PERIOD_MS);
            //     continue;
            // }

            // ESP_LOGI(TAG, "... connected");
            // freeaddrinfo(res);



            // if (write(s, REQUEST, strlen(REQUEST)) < 0) {
            //     ESP_LOGE(TAG, "... socket send failed");
            //     close(s);
            //     vTaskDelay(4000 / portTICK_PERIOD_MS);
            //     continue;
            // }
            // ESP_LOGI(TAG, "... socket send success");



            // struct timeval receiving_timeout;
            // receiving_timeout.tv_sec = 5;
            // receiving_timeout.tv_usec = 0;
            // if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout,
            //         sizeof(receiving_timeout)) < 0) {
            //     ESP_LOGE(TAG, "... failed to set socket receiving timeout");
            //     close(s);
            //     vTaskDelay(4000 / portTICK_PERIOD_MS);
            //     continue;
            // }
            // ESP_LOGI(TAG, "... set socket receiving timeout success");



            // /* Read HTTP response */
            // do {
            //     bzero(recv_buf, sizeof(recv_buf));
            //     r = read(s, recv_buf, sizeof(recv_buf)-1);
            //     for(int i = 0; i < r; i++) {
            //         putchar(recv_buf[i]);
            //     }
            // } while(r > 0);


            // ESP_LOGI(TAG, "... done reading from socket. Last read return=%d errno=%d.", r, errno);
            // close(s);

            
            // for(int countdown = 10; countdown >= 0; countdown--) {
            //     ESP_LOGI(TAG, "%d... ", countdown);
            //     vTaskDelay(1000 / portTICK_PERIOD_MS);
            // }
            // ESP_LOGI(TAG, "Starting again!");


        }


        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }

    }

    vTaskDelete(NULL);

}








// -------------------------
// < INITIALIZING WIFI APP >
// 
// 1. MAKING SPACE IN MEMORY FOR CONFIGURATION
// 2. CREATING QUEUE FOR COMMUNICATION BETWEEN TASKS
// 3. SETTING EVENT-GROUP FUNCTIONALITIES OF FREERTOS TO HANDLE MESSAGES 
// 4. SETTING AND STARTING TASK FOR THIS WIFI APPLICATION
// 
void wifi_app_start(void) {


	ESP_LOGI(TAG, "STARTING WIFI STA APPLICATION");


	// LED LIGHTING FOR INDICATING STATUS OF WIFI CONECTION
	// Start WiFi started LED
	// rgb_led_wifi_app_started();


	// Disable default WiFi logging messages
	esp_log_level_set("wifi", ESP_LOG_NONE);



	tcpip_adapter_init();

	wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));

	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    
    ESP_ERROR_CHECK(esp_event_loop_create_default());


	wifi_config_t sta_config = {
		.sta = {
			.ssid= "192.168.42.1",
			.password = "password"
		},
	};



	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA,&sta_config));

	ESP_ERROR_CHECK(esp_wifi_start());// starts wifi usage
	ESP_ERROR_CHECK(esp_wifi_connect());


	// Start the WiFi application task
	xTaskCreatePinnedToCore(&wifi_app_task, "wifi_app_task", WIFI_APP_TASK_STACK_SIZE, NULL, WIFI_APP_TASK_PRIORITY, NULL, WIFI_APP_TASK_CORE_ID);




}





