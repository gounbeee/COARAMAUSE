
#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "addr_from_stdin.h"


#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"

#include "uart_master_wifi.h"



#define HOST_IP_ADDR "192.168.42.1"
//#define HOST_IP_ADDR "192.168.3.10"
#define PORT 3333


#define KEEPALIVE_IDLE              5
#define KEEPALIVE_INTERVAL          5
#define KEEPALIVE_COUNT             3



#define IP_ADDR_PART_1 192
#define IP_ADDR_PART_2 168
#define IP_ADDR_PART_3 84

// BELOW IS ACTUAL INDEX NUMBER OF CLIENT DEVICE !!!!
// SO WE WILL HAVE THIS VALUE FROM 1 TO 9 
// BECAUSE OUR LIMITATION OF CLIENTS IS 9 !
// +
// AND BELOW WILL BE USED IN OTHER PLACE IN THIS CODE !

#define IP_ADDR_PART_4 1
// #define IP_ADDR_PART_4 2
// #define IP_ADDR_PART_4 3
// #define IP_ADDR_PART_4 4
// #define IP_ADDR_PART_4 5
// #define IP_ADDR_PART_4 6
// #define IP_ADDR_PART_4 7
// #define IP_ADDR_PART_4 8
// #define IP_ADDR_PART_4 9



#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)




/* The examples use WiFi configuration that you can set via project configuration menu
   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_ESP_WIFI_SSID      CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD
#define EXAMPLE_ESP_MAXIMUM_RETRY  CONFIG_ESP_MAXIMUM_RETRY

#if CONFIG_ESP_WIFI_AUTH_OPEN
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_ESP_WIFI_AUTH_WEP
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif





static const char *TAG = "WIFI_STATION_SOCKET";
static int s_retry_num = 0;
static int g_currentDisplayingNum = -1;

//static bool g_bootInitialized = false;

int g_keepAlive = 1;
int g_keepIdle = KEEPALIVE_IDLE;
int g_keepInterval = KEEPALIVE_INTERVAL;
int g_keepCount = KEEPALIVE_COUNT;






/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1




static int** deserializeIntList(char* listStr) {
	printf("----    DE-SERIALIZATION STARTED    ----\n");

	// OUR RESULT SHOULD BE LIKE BELOW
	// 9   -> WHERE SHOULD BE 9 ELEMENTS
	// 128 -> ENOUGH ROOM FOR 1 STRING ELEMENT
	const int nrows = 9;
	const int ncolumns = 128;


	static int** result;

	result = malloc(nrows * sizeof(int *)); // Allocate row pointers
	for(int i=0; i<nrows; i++) {
  		result[i] = malloc(ncolumns * sizeof(int));  // Allocate each row separately
  	}



	// DELIMETERS WE WERE USING (2 LETTERS)
	char delimiter_elem[] = "_";
	//char delimiter_count[] = "~";
	

	char* elem = strtok(listStr, delimiter_elem);
	size_t elemLn = strlen(elem);

	//printf("      elem IS (First Try) ---->       '%s'\n", elem);
	//printf("      elemLn IS (First Try) ---->       '%zu'\n", elemLn);



	// CREATING LIST OF ELEMENTS
	static char** elemList = NULL;

	// MEMORY ALLOCATION
	elemList = malloc(nrows * sizeof(char *)); // Allocate row pointers
	for(int i=0; i<nrows; i++) {
  		elemList[i] = malloc(ncolumns * sizeof(char));  // Allocate each row separately
  	}

  	// INSERTING DATA TO ARRAY
	for(int i=0; i<nrows; i++) {
		
		// PICKING UP THE FIRST LETTER FROM elem
		//char* cntStr;
		//printf("FIRST LETTER OF elem  -->  %c\n", elem[0]);


		// < memcpy() FUNCTION > 
		// https://bituse.info/c_func/56
		char buf[] = "0";
		memcpy(buf, elem, 1);


		
		int cnt = atoi(buf);
		//printf("cnt(COUNT OF LETTER) IS   %d  \n", cnt);

		//printf("AFTER PICKING COUNT LETTER FROM elem  -->  %s\n", elem);


		// DELETE FIRST 2 LETTERS FROM elem
		char trunc[8];

		size_t elmLen = strlen(elem);
		for(int t=2; t<elmLen; t++) {
			trunc[t-2] = elem[t];
		}

		// PUT '\0' USING LETTER COUNT
		trunc[cnt] = '\0';

		// STORE STRING TO ARRAY
		strcpy( elemList[i] , trunc);

		// NEXT TOKENIZATION
		elem = strtok(NULL, delimiter_elem);

	} 

	for(int i=0; i<nrows; i++) {

		*result[i] = atoi(elemList[i]);

		//printf("result[i] (INTEGER)  -->  %d \n", *result[i]);

	}

	// FREEING MEMORY
	for(int i=0; i<nrows; i++) {
  		free(elemList[i]);  // Allocate each row separately
  	}
  	free(elemList);



  	// **** TODO :: SHOULD WE FREE static LOCAL VARIABLE result ?
  	// result SHOULD BE FREED !!!!


	printf("----    DE-SERIALIZATION COMPLETED    ----\n");
	return result;

}



static int sendMessage(SOCKET sock, char* msg, int len) {

	int written = send( sock, msg, len, 0 );

    if (written < 0) {
        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);

        //vTaskDelay(2000 / portTICK_PERIOD_MS);
        return -1;

    } else {

		ESP_LOGI(TAG, "SENT : len: %d", written);
		return 0;

    }

} 




static void tcp_client_task(void *pvParameters) {


	char thisIpAddress[64];
	int thisIpAddressLength = -1;
	sprintf(thisIpAddress, "%d.%d.%d.%d", IP_ADDR_PART_1, IP_ADDR_PART_2, IP_ADDR_PART_3, IP_ADDR_PART_4);
	thisIpAddressLength = strlen(thisIpAddress);
	thisIpAddress[thisIpAddressLength] = '\0';

	printf("**** COARAMAUSE CLIENT ::  IP ::   %s    ::  LENGTH OF STRING    ::  %d  \n", thisIpAddress, thisIpAddressLength);




	while(1) {


		ESP_LOGI(TAG, "=================================================");
		ESP_LOGI(TAG, "STARTING TCP CLIENT SOCKET...");

		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		ESP_LOGI(TAG, "socket() FUNCTION SUCCESSED !!  ::  %d", sock);


		struct sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;

		inet_pton(AF_INET, HOST_IP_ADDR, &serverAddress.sin_addr.s_addr);
		serverAddress.sin_port = htons(PORT);



		// CONNECTING TO SERVER
		int rc = connect(sock, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in));
		if( rc == -1 ) {
			printf(" &**&*  ERROR OCCURED !!  ::  rc:   %d\n", rc);	
		} else {
			printf("CONNECTED !!  ::  rc:   %d\n", rc);	
		}



        // ---------------------------------------------------------------------------------------------------
        // Set tcp keepalive option
        setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &g_keepAlive, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &g_keepIdle, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &g_keepInterval, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &g_keepCount, sizeof(int));




	    struct timeval timeout;
	    timeout.tv_sec = 10000;
	    timeout.tv_usec = 0;


		ESP_LOGI(TAG, "LET'S SEND SOMETHING !!!!");



		//SAY IP ADDRESS TO TCP SOCKET SERVER
		rc = send( sock, thisIpAddress, thisIpAddressLength, 0 );
		ESP_LOGI(TAG, "SENT : rc: %d", rc);



		for(;;) {

			// < CODE SNIPPET FOR SOCKETING >
			// https://github.com/nkolban/esp32-snippets/blob/master/sockets/client/socketClient.c
			char rx_buffer[128];


	        fd_set readFd;
	        FD_ZERO(&readFd);
	        FD_SET( sock, &readFd );
	        //FD_SET(0, &readFd);

			printf("++++++++++++++   BLOCKED (SELECTING)  ++++++++++++++++\n");

			int ret_select;
			ret_select = select(sock+1, &readFd, 0, 0, &timeout);

			// SELECT FUNCTION FAILED...
	        if ( ret_select == -1 ) {
	            fprintf(stderr, "****&*&*&*&*&*&*      select() FAILED !!!!  (%d)\n", GETSOCKETERRNO());
	            shutdown(sock, 0);
				close(sock);
	            break;

	        } else if(ret_select == 0) {
	            fprintf(stderr, "****&*&*&*&*&*&*      select() TIMED OUT !!!!  (%d)\n", GETSOCKETERRNO());
	            shutdown(sock, 0);
				close(sock);
	            break;

	        } else if(ret_select > 0) {
	        	printf("****&*&*&*&*&*&*      select FUNCTION POSITIVE  ::  READING IS READY !!!!\n");



		        // IF FILE DESCRIPTOR FOR READING IS READY TO READ
		        if ( FD_ISSET(sock, &readFd) ) {

		        	printf("SOCKET FOR READING IS ACCEPTING !!!!\n");


		            char read[128];

		            int bytes_received = recv(sock, read, 128, 0);

		            if (bytes_received < 1) {
		                printf("SERVER DID NOT SEND ANYTHING !!!!\n");
		                printf("MAYBE IT IS INITIALZIED AND NEVER USED HTTP CLIENT\n");

		                FD_ZERO( &readFd );
		                shutdown(sock, 0);
						close(sock);
		                break;

		            } else {

		            	printf("SUCCESSFULLY RECEIVED !!!!\n");
			            printf("Received (%d bytes): %.*s \n",
		        			   bytes_received, 
		        			   bytes_received, 
		        			   read);

			            read[ bytes_received ] = '\0';

			            // ===============================================================
			            // CHECK RETURNED MESSAGE IS "SERVER_IPADDR_RECEIVED_OK",
			            // 
			            if(strcmp(read, "SERVER_IPADDR_RECEIVED_OK") == 0) {

			            	printf("SERVER_IPADDR_RECEIVED_OK    IS RETURNED !!!! \n");


		     				shutdown(sock, 0);
							rc = close(sock);
							//ESP_LOGI(TAG, "close: rc: %d", rc);


			            	// CONTINUOUSLY REQUESTING SCENE NUMBER TO SERVER !!!!!
			            	printf("*****  CONTINUOUSLY REQUESTING SCENE NUMBER TO SERVER !!!!!\n");

			            	bool bSceneNumberReq = true;
			            	int reqCount = 0;

			            	// SEND THE MESSAGE "CLIENT_REQUEST_SCENENUMBERS"
							char requreNumberMsg[32] = "CLIENT_REQUEST_SCENENUMBERS";
							int ln = strlen(requreNumberMsg);
							requreNumberMsg[ln] = '\0';

			            	while (1) {


								SOCKET sockSend = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

						        // ---------------------------------------------------------------------------------------------------
						        // Set tcp keepalive option
						        setsockopt(sockSend, SOL_SOCKET, SO_KEEPALIVE, &g_keepAlive, sizeof(int));
						        setsockopt(sockSend, IPPROTO_TCP, TCP_KEEPIDLE, &g_keepIdle, sizeof(int));
						        setsockopt(sockSend, IPPROTO_TCP, TCP_KEEPINTVL, &g_keepInterval, sizeof(int));
						        setsockopt(sockSend, IPPROTO_TCP, TCP_KEEPCNT, &g_keepCount, sizeof(int));


								ESP_LOGI(TAG, "socket() FUNCTION SUCCESSED !!  ::  %d", sockSend);

								// CONNECTING TO SERVER
								int rcSend = connect(sockSend, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in));
								if( rcSend == -1 ) {
									printf(" &**&*  ERROR OCCURED !!  ::  rcSend:   %d\n", rcSend);	
								} else {
									printf("CONNECTED !!  ::  rcSend:   %d\n", rcSend);	
								}


	            	           	int sentBytes = send(sockSend, requreNumberMsg, strlen(requreNumberMsg), 0);
								ESP_LOGI(TAG, "SENT : sentBytes: %d", sentBytes);
				            	
				            	reqCount++;
				            	printf("*****  REQUEST COUNT  ::    %d  !!!!!\n", reqCount);	




				            	char buffer_read[128];

					            int bytes_rc = recv(sockSend, buffer_read, 128, 0);

					            buffer_read[bytes_rc] = '\0';


					            if (bytes_rc < 1) {

					                printf("ERROR TO RECEIVED SCENE NUMBER IN LOOP !!!!\n");
					                shutdown(sockSend, 0);
									close(sockSend);
					                break;

					            } else {


					            	// IF RECEIVED MESSAGE IS NOT ABOUT IP ADDRESS,
					            	// THAT MEANS SERVER SENT THE SCENE NUMBER LIST
					            	// SO WE CAN USE THAT LIST

									// ----------------------------
									// < DE-SERIALIZATION OF DATA >
									// TODO :: MOVE THIS FUNCTION TO STATION MODULES !!!!

									printf("DE-SERIALIZATION  WILL START !!!! \n");
									printf("%s \n", buffer_read);
				



									int** deserialized = deserializeIntList(buffer_read);;


									printf(" AFTER DE-SERIALZATION ::    ");
									for(int i=0; i<9; i++) {
								  		printf("%d | ", *deserialized[i]);

								  	}
									printf("\n");



									// TODO ::  
									// 1. CHECK CURRENT IP ADDRESS                    -- OK
									// 2. PICK UP LAST VALUE OF IP ADDRESS            -- OK
									// 3. RETREIVE SCENE NUMBER FROM deserialized     -- OK
									g_currentDisplayingNum = *deserialized[IP_ADDR_PART_4 - 1]; 
									//g_currentDisplayingNum -= 1;

									printf("g_currentDisplayingNum    IS   %d \n", g_currentDisplayingNum);


									// CONVERTING INTEGER TO CHAR*
									char sceneNumberChar[10];

							    	// CONVERTING INTEGER TO STRING
							    	sprintf(sceneNumberChar, "%d", g_currentDisplayingNum);


									// 4. SEND UART DATA TO DISPLAY MODULE !
									if(g_currentDisplayingNum != -1) uart_wifi_SetSceneNumber(sceneNumberChar);



									// *********************************
									// AFTER USING, FREE THE MEMORY !!!!
									for(int i=0; i<9; i++) {
								  		free(deserialized[i]);  // Allocate each row separately
								  	}
								  	free(deserialized);



					                shutdown(sockSend, 0);
									close(sockSend);


					            }



				            	vTaskDelay(3000 / portTICK_PERIOD_MS);


			            	}



			            } else if(strcmp(read, "SERVER_IPADDR_RECEIVED_OK") == 0) { 

			 				// CONTINUOUSLY REQUESTING SCENE NUMBER TO SERVER !!!!!
					       	printf("*****  CONTINUOUSLY REQUESTING SCENE NUMBER TO SERVER !!!!!\n");

			            }



		            }



		        } else {

		        	printf("SOCKET FOR READING IS 'JUST' LISTENING !!!!\n");



					
						


		        }




	        }







			// if(FD_ISSET(0, &reads)) {

			// 	ESP_LOGI(TAG, "LET'S SEND SOMETHING !!!!");


			// 	// SAY HELLO TO TCP SOCKET SERVER
			// 	//rc = send( sock, thisIpAddress, thisIpAddressLength, 0 );
			// 	//ESP_LOGI(TAG, "SENT : rc: %d", rc);




	  //           // char read[4096];

	  //           // if (!fgets(read, 4096, stdin)) break;

	  //           // printf("Sending: %s", read);
	  //           // int bytes_sent = send( sock, read, strlen(read), 0 );
	  //           // printf("Sent %d bytes.\n", bytes_sent);


	  //       }




			

			// SAY HELLO TO TCP SOCKET SERVER
			//rc = send( sock, thisIpAddress, thisIpAddressLength, 0 );
			//ESP_LOGI(TAG, "SENT : rc: %d", rc);






			//vTaskDelay(1000 / portTICK_PERIOD_MS);






			// // THEN RECEIVE DATA FROM SERVER
			// ESP_LOGI(TAG, "==== NOW WE WILL RECEIVE ANSWER FROM SERVER...");
	  //       int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
	  //       //int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
	  //       //int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in) );

	  //       ESP_LOGI(TAG, "RETURNED VALUE FROM recv() FUNCTION  ::  len  ->    %d   ", len);



	  //       // Error occurred during receiving
	  //       if (len < 0) {
	  //           ESP_LOGE(TAG, "recv FUNCTION FAILED !!  : errno %d", errno);
	  //           break;
	  //       }
	  //       else if(len == 0) {
	  //       	ESP_LOGI(TAG, "RETURN VALUE IS 0 !!!! NOTHING TO DO !!!!  ::  len  ->    %d   ", len);
			// 	//break;
	  //       }
	  //       // DATA RECEIVED !!
	  //       else {


	  //           rx_buffer[len] = 0; 				// Null-terminate whatever we received and treat like a string
	  //           ESP_LOGI(TAG, "RECEIVED DATA !!    %d    BYTES FROM    %s   !!", len, HOST_IP_ADDR);

	  //          	ESP_LOGI(TAG, "%s", rx_buffer);


			// 	// ----------------------------
			// 	// < DE-SERIALIZATION OF DATA >
			// 	// TODO :: MOVE THIS FUNCTION TO STATION MODULES !!!!

			// 	int** deserialized = deserializeIntList(rx_buffer);;

			// 	printf(" AFTER DE-SERIALZATION ::    ");
			// 	for(int i=0; i<9; i++) {
			//   		printf("%d | ", *deserialized[i]);

			//   	}
			// 	printf("\n");



			// 	// TODO ::  
			// 	// 1. CHECK CURRENT IP ADDRESS                    -- OK
			// 	// 2. PICK UP LAST VALUE OF IP ADDRESS            -- OK
			// 	// 3. RETREIVE SCENE NUMBER FROM deserialized     -- OK
			// 	g_currentDisplayingNum = *deserialized[IP_ADDR_PART_4 - 1]; 
			// 	//g_currentDisplayingNum -= 1;

			// 	printf("g_currentDisplayingNum    IS   %d \n", g_currentDisplayingNum);


			// 	// CONVERTING INTEGER TO CHAR*
			// 	char sceneNumberChar[10];

		 //    	// CONVERTING INTEGER TO STRING
		 //    	sprintf(sceneNumberChar, "%d", g_currentDisplayingNum);


			// 	// 4. SEND UART DATA TO DISPLAY MODULE !
			// 	if(g_currentDisplayingNum != -1) uart_wifi_SetSceneNumber(sceneNumberChar);



			// 	// *********************************
			// 	// AFTER USING, FREE THE MEMORY !!!!
			// 	for(int i=0; i<9; i++) {
			//   		free(deserialized[i]);  // Allocate each row separately
			//   	}
			//   	free(deserialized);
				

	  //       }


			// shutdown(sock, 0);
			// rc = close(sock);
			// ESP_LOGI(TAG, "close: rc: %d", rc);





			//vTaskDelay(5000 / portTICK_PERIOD_MS);
			vTaskDelay(1);



		}




		//printf("=============================================================\n");
		//printf("============  <<<  TASK WILL BE RESETTED !!  >>>  ===========\n");
		//printf("=============================================================\n");
		//vTaskDelay(5000 / portTICK_PERIOD_MS);


	}

}



static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data) {
	

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
    
        esp_wifi_connect();
    
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
    
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {

            esp_wifi_connect();
            s_retry_num++;

            ESP_LOGI(TAG, "retry to connect to the AP");


        } else {

            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);

        }
        ESP_LOGI(TAG,"connect to the AP fail");
    
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
    
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
    
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;

        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    
    }

}




void wifi_init_sta(void) {

    s_wifi_event_group = xEventGroupCreate();


    // ------------------------------------------------------------
    // < SETTING UP NETWORK INTERFACE >
    // WE WANT TO SET UP THE WIFI, SO 
    // WE SETUP THE LOWER WHICH IS "LAYER NETWORK INTERFACE LAYER"

    // INITIALIZE NETWORK INTERFACE
    ESP_ERROR_CHECK(esp_netif_init());

    // INITIALIZE EVENT LOOP
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // CREATE 'STATION' OBJECT USING NETWORK INTERFACE OBJECT 
    esp_netif_t *my_sta = esp_netif_create_default_wifi_sta();

    // STOPPING "DHCP" BECAUSE WE
    // WANT STATIC IP ALLOCATION !!!! <-- *********
	esp_netif_dhcpc_stop(my_sta);

	// SETTING UP IP INFORMATION FOR OUR INITIALIZED STATION OBJECT 
    esp_netif_ip_info_t ip_info;

    // SETTING IP ADDRESS :: IT SHOULD BE 192.168.84.1 ~ 9 IN OUR APPLICATION
    //                                            ^^ ^   ^
    IP4_ADDR(&ip_info.ip, IP_ADDR_PART_1, IP_ADDR_PART_2, IP_ADDR_PART_3, IP_ADDR_PART_4);

    // SETTING GATEWAY    :: GATEWAY SHOULD BE COARAMAUSE SERVER (192.168.42.1) 
    //                                                                    ^^
   	IP4_ADDR(&ip_info.gw, 192, 168, 42, 1);

   	// NETMASK SETTING    :: WE HAVE IP ADDRESS CHANGES OF 'THIRD' AREA 
   	// (LIKE 84 MEANS CLIENT, 42 MEANS SERVER AND HTTP CLIENT)
   	// SO WE SHOULD HAVE '0' IN THE THIRD AREA
   	//                                   *
   	IP4_ADDR(&ip_info.netmask, 255, 255, 0, 0);

   	// FINALLY WE SETTED UP OUR STATION OBJECT
    esp_netif_set_ip_info(my_sta, &ip_info);



    // ------------------------------------------------------------
    // < SETTING UP WIFI >
    //
    // **** USE BELOW MACRO !!!! ****
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html#_CPPv413esp_wifi_initPK18wifi_init_config_t
    // :: FOR THE COMPATIBILITY ISSUES, IT SEEMS BETTER TO USE BELOW MACRO !!
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));


    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));


    // CONSTRUCTING CONFIGURATION FOR WIFI OBJECT
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS,
            /* Setting a password implies station will connect to all security modes including WEP/WPA.
             * However these modes are deprecated and not advisable to be used. Incase your Access point
             * doesn't support WPA2, these mode can be enabled by commenting below line */
	        .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
        },
    };

    // SETTING THIS ESP WIFI APPLICATION AS "STATION" MODE
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );

    // SETTING CONFIGURATION THIS WIFI APPLICATION WITH ABOVE CONFIG
    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );

    // START WIFI APPLICATION
    ESP_ERROR_CHECK( esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");



    // -------------------------------------------------------------------------------------------------------------
    // < EVENT GROUP BIT >
    // :: THIS FUNCTION IS DERIVED FROM FREE RTOS, AND 
    //    WE ARE USING THIS FOR WAITING ("LITERALLY, BLOCKING") BITS UNTIL THE CONNECTION IS GOOD TO GO
    //
    //    < FROM RTOS PAGE >
    //    https://www.freertos.org/xEventGroupWaitBits.html
    //    
    //    :: Read bits within an RTOS event group, optionally 
    //       entering the Blocked state (with a timeout) to wait for 
    //       a bit or group of bits to become set.

    // Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
    // * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) 
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
								           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
								           pdFALSE,
								           pdFALSE,
								           portMAX_DELAY);

    // xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
    // * happened. 
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, 
        		 "connected to ap SSID:%s password:%s",
                 EXAMPLE_ESP_WIFI_SSID, 
                 EXAMPLE_ESP_WIFI_PASS);

    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, 
        		 "Failed to connect to SSID:%s, password:%s",
                 EXAMPLE_ESP_WIFI_SSID, 
                 EXAMPLE_ESP_WIFI_PASS);

    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }


}





void app_main(void) {

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());


    // INITIALIZING NETWORK ~ TRANSPORT LAYER
	wifi_init_sta();

	// TASK EXECUTES EVENT LOOP
    xTaskCreate(tcp_client_task, "tcp_client", 8096, NULL, 5, NULL);

	// START UART COMMUNICATION
	uart_wifi_task_start();

	//
	//g_bootInitialized = true;

}