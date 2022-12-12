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


// ---------------------------------------
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



// ------------------------------------------
// < WIFI SERVER AND CLIENT x TCP AND UDP >
//
// https://github.com/espressif/esp-idf/tree/master/examples/protocols/sockets/udp_server
// https://github.com/espressif/esp-idf/tree/master/examples/protocols/sockets/udp_client
//
// https://github.com/espressif/esp-idf/blob/master/examples/protocols/sockets/tcp_server/main/tcp_server.c
// https://github.com/espressif/esp-idf/blob/master/examples/protocols/sockets/tcp_client/main/tcp_client.c
// https://github.com/espressif/esp-idf/tree/master/examples/protocols/sockets/tcp_client_multi_net





// --------------------------------
// < EVENT HANDLING >
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/event-handling.html 
//
// Several ESP-IDF components use events to inform application about state changes, 
// such as connection or disconnection. 
//
// This document gives an overview of these event mechanisms.



// ------------------------------------
// esp_wifi_ap_get_sta_list() FUNCTION
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html
//
// esp_err_t esp_wifi_ap_get_sta_list(wifi_sta_list_t *sta)
//                                **** WE NEED THIS STRUCT ****
//                               
//
// Get STAs associated with soft-AP.
//
// Attention
// SSC only API
//
// Parameters
// sta – [out] station list ap can get the connected sta’s phy mode info through the struct member phy_11b，phy_11g，phy_11n，phy_lr in the wifi_sta_info_t struct. For example, phy_11b = 1 imply that sta support 802.11b mode
//
// Returns
// ESP_OK: succeed
//
// ESP_ERR_WIFI_NOT_INIT: WiFi is not initialized by esp_wifi_init
//
// ESP_ERR_INVALID_ARG: invalid argument
//
// ESP_ERR_WIFI_MODE: WiFi mode is wrong
//
// ESP_ERR_WIFI_CONN: WiFi internal error, the station/soft-AP control block is invalid
//


// ----------------------------------
// < struct wifi_sta_list_t > STRUCTURE
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html#_CPPv415wifi_sta_list_t
//
// List of stations associated with the ESP32 Soft-AP.
//
// Public Members
//
// wifi_sta_info_t sta[ESP_WIFI_MAX_CONN_NUM]
//  
// **** WE NEED THIS TYPE **** 
//
// station list
//
// int num
// number of stations in the list (other entries are invalid)
// 


// ----------------------------------
// < struct wifi_sta_info_t > STRUCTURE
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html#_CPPv415wifi_sta_info_t
//
// Description of STA associated with AP.
//
// Public Members
//
// uint8_t mac[6]
// mac address
//
// int8_t rssi
// current average rssi of sta connected
//
// uint32_t phy_11b
// bit: 0 flag to identify if 11b mode is enabled or not
//
// uint32_t phy_11g
// bit: 1 flag to identify if 11g mode is enabled or not
//
// uint32_t phy_11n
// bit: 2 flag to identify if 11n mode is enabled or not
//
// uint32_t phy_lr
// bit: 3 flag to identify if low rate is enabled or not
//
// uint32_t is_mesh_child
// bit: 4 flag to identify mesh child
//
// uint32_t reserved
// bit: 5..31 reserved
//


//esp_wifi_ap_get_sta_list() ??





// < List of stations associated with the ESP32 Soft-AP >
//https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html#_CPPv415wifi_sta_list_t





// // -------------------------------
// // < ABOUT UNBINDING SOCKET >
// // https://stackoverflow.com/questions/4623045/how-to-unbind-a-socket-programmatically

// // --------------------------------------
// // < FILTERING MAC ADDRESS >
// int devIndex_dis = -1;
// devIndex_dis = filterMacAddr(event_data);

// if(devIndex_dis != -1) {
// 	socketDisconnectWork(devIndex_dis);
// } else {
// 	printf("----  WARNING ----  NO SOCKET-WORK (DISCONNECTION) OCCURED !!\n");
// }





// // =======================================
// // < CREATING SOCKETS >
// // https://en.wikipedia.org/wiki/Network_socket#:~:text=The%20socket%20is%20primarily%20a,implementations%20of%20the%20transport%20layer.
// //
// // The socket is primarily a concept used in the transport layer of the Internet protocol 
// // suite or session layer of the OSI model.


// // -------------------------------------
// // < Sockets and multiple IP Addresses >
// // https://stackoverflow.com/questions/10119983/sockets-and-multiple-ip-addresses

// instanceAllSockets();


// // --------------------------------------
// // < FILTERING MAC ADDRESS >
// int devIndex = -1;
// devIndex = filterMacAddr(event_data);


// // --------------------------------------
// // < SETTING SOCKET >
// // https://programming.vip/docs/esp32-learning-notes-tcp-server.html
// //
// // < HOW TO USE NETCAT >
// // https://skipperkongen.dk/2019/06/30/chat-with-netcat/
// //
// // < WE USE SOCKET TO TRANSFER OUR SCENE NUMBER DATA FROM SERVER >  
// //

// // < ADDRESS FAMILY IDENTIFIER >
// // https://en.wikipedia.org/wiki/Address_family_identifier
// // :: THIS INCLUDES 32-BITS IPv4 AND 128-BITS IPv6
// if(devIndex != -1) {
// 	socketConnectWork(devIndex);
// } else {
// 	printf("----  WARNING ----  NO SOCKET-WORK (CONNECTION) OCCURED !!\n");
// }




// // ---------------------
// // < POLL SERVER >
// // https://github.com/weboutin/simple-socket-server/blob/master/poll-server.c
// // :: USING POLL FUNCTION, WE CAN 





// // TODO :: POLL OR SELECT FUNCTION
// // https://github.com/weboutin/simple-socket-server/blob/master/poll-server.c






#include <stdbool.h>
#include <stdio.h>
#include <string.h>


// BASIC FUNCTIONALITIES FOR APPLICATION
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
// #include "freertos/semaphr.h"

// BASIC LOGGING FUNCTIONALITIES FOR LOGGING
#include "esp_err.h"
#include "esp_log.h"

// FOR "NETWORK" LAYER ? (IN BRIEF THOUGHT)
#include "esp_wifi.h"

// FOR "TRANSPORT" LAYER ? (IN BRIEF THOUGHT)
#include "lwip/netdb.h"
#include "lwip/sockets.h"


// "APPLICATION" LAYER ? (IN BRIEF THOUGHT)
#include "app_nvs.h"
#include "http_server.h"
//#include "rgb_led.h"
#include "tasks_common.h"
#include "wifi_app.h"









// -------------------------------
// ESP32 MAC ADDRESS TABLE !!!
// THIS SHOULD BE RE-WRITTEN TO IDENTIFY INDIVIDUAL UNITS OF ESP32
//
// 1.
// 192.168.84.1
// 48 :: 198 :: 247 :: 14 :: 26 :: 84
//
// 2.
// 192.168.84.2
// 132 :: 13 :: 142 :: 44 :: 31 :: 212


static const int g_allMacAddresses[ 9 ][ 6 ] = {
    // CLIENT INDEX 0
    {48, 198, 247, 14, 26, 84},                 // IP-ADDRESS SHOULD BE ==>  192.168.84.1
    // CLIENT INDEX 1
    {132, 13, 142, 44, 31, 212},                // IP-ADDRESS SHOULD BE ==>  192.168.84.2



    // ...
    // ... TO 9 ESP32 CLIENT MODULES


};



static int g_allDevsActive[9] = { -1,-1,-1,-1,-1,-1,-1,-1,-1 };




// DEFINE TAG NAME FOR DISPLAYING TO CONSOLE
static const char TAG [] = "wifi_app";

//static const char TAG_Soc [] = "wifi_app_SOCKET";


// WiFi application callback
static wifi_connected_event_callback_t wifi_connected_event_cb;



// Used for returning the WiFi configuration
wifi_config_t *wifi_config = NULL;



// Used to track the number for retries when a connection attempt fails
static int g_retry_number;


// ------------------------------------------------
// < USING EVENT GROUP FUNCTIONALITY OF FREERTOS >
// IN THIS PROGRAM, WE USE EVENT GROUP BITS FOR "SUB-CATEGORIZING" THE SCENARIO
// WHEN WE CONNECT TO WIFI THEN INTIALIZE THE HTTP SERVER PROGRAM
static EventGroupHandle_t wifi_app_event_group;

const int WIFI_APP_CONNECTING_USING_SAVED_CREDS_BIT			= BIT0;
const int WIFI_APP_CONNECTING_FROM_HTTP_SERVER_BIT			= BIT1;
const int WIFI_APP_USER_REQUESTED_STA_DISCONNECT_BIT		= BIT2;
const int WIFI_APP_STA_CONNECTED_GOT_IP_BIT					= BIT3;



// Queue handle used to manipulate the main queue of events
static QueueHandle_t wifi_app_queue_handle;



static bool g_sockLoopGate = true;


// SEMAPHORE AND TASK HANDLES

SemaphoreHandle_t g_xSemaphore = NULL;

TaskHandle_t g_taskHandle_sock = NULL;
TaskHandle_t g_taskHandle_wifi = NULL;







// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

esp_netif_t* esp_netif_sta = NULL;
esp_netif_t* esp_netif_ap  = NULL;




// INCOMING DEVICE'S IP ADDRESS
char g_ipAddrCreated[128];
int g_ipAddrIndex = -1;


// ALL SOCKET STRUCTS
wifi_socket_connect_t g_allSockConnects[MAX_SOCKET_COUNTS];


char g_addr_str[128];
int g_addr_family = AF_INET;
int g_ip_protocol = 0;
int g_keepAlive = 1;
int g_keepIdle = KEEPALIVE_IDLE;
int g_keepInterval = KEEPALIVE_INTERVAL;
int g_keepCount = KEEPALIVE_COUNT;

struct sockaddr_storage g_dest_addr;


int g_listen_sock;
//int g_accepted_sock;

SOCKET g_max_socket;
// SOCKET g_socket_client;


fd_set g_master_fdset;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// -------------------------
// < SERIALIZING TEXT !!!! >
//
// Function to serialized the array of string
// https://www.geeksforgeeks.org/serialize-deserialize-array-string/
// 
static char* serializeIntList(int* intList, int len) {
	printf("----    SERIALIZATION STARTED    ----\n");
	
	// FINAL RESULT
 	static char result[256];
 	
	//printf(" TESTING intList[0]    -->   %d  \n", intList[0]);

	// VARIABLES FOR CREATING ONE UNIT
	char wordFinal[10];
	size_t wordFinalCnt = 0;

	// INDEX CURSOR
	int cursor = 0;


    // LOOP IN THE INTEGER LIST (WORD LEVEL)
    for (int i=0; i < len; i++) {


    	// GETTING INTEGER
	   	int elem = intList[i];
    	//printf("  PRINTING  elem (INTEGER) ::   %d  \n", elem);


    	// ------------------------------
    	// GETTING COUNT OF NUMBER LETTER 
		char wordForCount[10];

    	// CONVERTING INTEGER TO STRING
    	sprintf(wordForCount, "%d", elem);
		//printf("    CONVERTED INT (STRING)      -->  %s   \n", wordForCount);

		// COUNTING LETTERS OF CONVERTED ABOVE
		size_t wordLetterCnt = strlen(wordForCount);
		//printf("    COUNTING LETTERS OF ABOVE -->  %zu   \n", wordLetterCnt);


		//printf( "-- NOW, SERIALIZING INTEGER...  \n");

		// ------------------------------
		// 

		sprintf(wordFinal, "%zu~%d_", wordLetterCnt, elem);
		//printf("    @@ MODIFIED WORD   (wordFinal)   -->  %s   \n", wordFinal);

		wordFinalCnt = strlen(wordFinal);

		// ASSGNING LETTERS OF ABOVE RESULT (IN ONE UNIT)
		for(int t=0; t < wordFinalCnt; t++) {
			result[cursor + t] =  wordFinal[t];	
		}

		cursor += wordFinalCnt;


    }

    // DELETE LAST SEPERATOR LETTER
    size_t resultLen = strlen(result);
    result[resultLen-1] = '\0';

    printf("#### >> FINAL SERIALIZED DATA    ::   %s   \n", result);
    printf("----    SERIALIZATION COMPLETED    ----\n");
    return result;

}
  
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

	printf("      elem IS (First Try) ---->       '%s'\n", elem);
	printf("      elemLn IS (First Try) ---->       '%zu'\n", elemLn);



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
		printf("FIRST LETTER OF elem  -->  %c\n", elem[0]);


		// < memcpy() FUNCTION > 
		// https://bituse.info/c_func/56
		char buf[] = "0";
		memcpy(buf, elem, 1);


		
		int cnt = atoi(buf);
		printf("cnt(COUNT OF LETTER) IS   %d  \n", cnt);

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

		printf("result[i] (INTEGER)  -->  %d \n", *result[i]);

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

// < SPLITTING STRING WITH strkok() FUNCTION >
// https://www.educative.io/answers/splitting-a-string-using-strtok-in-c
static void deComposeStringToInt(int* result, char* listStr, char* delimiter, int counts) {

	//printf("----    DE-COMPOSITION STARTED    ----\n");
	char* token = strtok(listStr, delimiter);

	// loop through the string to extract all other tokens
	int loopCnt = 0;

	while( token != NULL ) {
	  //printf( " %s\n", token ); //printing each token

	  result[loopCnt] = atoi(token);

	  token = strtok(NULL, delimiter);

	  loopCnt += 1;
	}

	//printf("----    DE-COMPOSITION COMPLETED    ----\n");

}

// < FOR DISPLAYING MESSAGES WHICH TRANSFERRED FROM STATION >
static void answerToClient(const int sock, 
						   int* sceneNumbersList, 
						   int listCount) {




	// < TRANSFERRING STRUCT DATA WITH SOCKET COMMUNICATION >
	// https://stackoverflow.com/questions/26776994/sending-a-structure-over-socket-in-c
	// ::  if you are trying to send the struct you must use serialization and deserialization,
	//     read about that, you can start with : 
	// 
	// 




	// TODO ::
	// SERIALIZE TEST
	// char* serializedList = 


	printf("sceneNumbersList  TEST  ...    %d  \n", sceneNumbersList[0]);

	// --------------------------
	// < SERIALIZATION OF DATA >
	//
	// **** BELOW IS OUR SERIALZATION FORMAT
	// 
	// 
 	// 1~3_1~4_1~5_1~6_1~7_1~8_1~9_2~10_2~11
	// | |    |         |
	// @COUNT OF LETTERS OF STRING   (FROM 10, LETTER COUNT IS '2' OF COURSE)
	//   |    |         |
	//   @STRING DATA   |
	//        |         |
	//        @ARRAY ELEMENT SEPERATOR
	//                  |
	//                  @SEPERATOR FOR COUNT AND STRING
	char* serializedData = serializeIntList( sceneNumbersList, listCount);
	//printf("      serializedData IS ---->       %s   \n", serializedData);



	// ----------------------------
	// < DE-SERIALIZATION OF DATA >
	// TODO :: MOVE THIS FUNCTION TO STATION MODULES !!!!

	// int** deserialized = deserializeIntList(serializedData);;

	// printf(" AFTER DE-SERIALZATION ::    ");
	// for(int i=0; i<MAX_SOCKET_COUNTS; i++) {
 //  		printf("%d | ", *deserialized[i]);

 //  	}
	// printf("\n");


	// // *********************************
	// // AFTER USING, FREE THE MEMORY !!!!
	// for(int i=0; i<MAX_SOCKET_COUNTS; i++) {
 //  		free(deserialized[i]);  // Allocate each row separately
 //  	}
 //  	free(deserialized);
	






    // // Convert ip address to string
    // if (source_addr.ss_family == PF_INET) {
    //     inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, 
	   //          	g_addr_str, 
	   //          	sizeof(g_addr_str) - 1);
    // }


    ESP_LOGI(TAG, "DATA WILL BE SENT TO   :  %s  ", g_addr_str);




    //int written = send(sock, serializedData + (len - to_write), to_write, 0);
	int written = send( sock, serializedData, strlen(serializedData), 0 );

    if (written < 0) {
        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        
    } else {

		ESP_LOGI(TAG, "SENT : len: %d", written);

    }


	ESP_LOGI(TAG, "-- SENDING DATA ENDED --");

}

static int* getActiveDevs() {

	int cnt = 0;
	int* res;

	for(int i=0; i<9; i++) {
		if(g_allDevsActive[i] == 1) {
			cnt++;
		}
	}

	if(cnt > 0) {
		res = (int*) malloc( sizeof(int)*cnt ); // allocate  cnt  ints	
	}
	
	int ind = 0;
	for(int i=0; i<9; i++) {
		if(g_allDevsActive[i] == 1) {
			
			res[ind] = g_allDevsActive[i];
			ind++;
		}
	}

	if(cnt > 0) {
		return res;
	} else {
		return NULL;
	}

}



// ================================================================================================
// BELOW FUNCTIONS FOR 'MULTIPLE SOCKETS' SCENARIO !!!!
// CURRENTLY WE DO NOT USING IT

static void createAllSocketStructs() {

	// < INITIALIZING ALL SOCKET CONNECTION STRUCT >
	// https://stackoverflow.com/questions/330793/how-to-initialize-a-struct-in-accordance-with-c-programming-language-standards
	//
	for(int i=0; i<MAX_SOCKET_COUNTS; i++) {
		ESP_LOGI(TAG, "||||  INITIALIZING ALL SOCKET CONNECTION STRUCT  ||||");


		g_allSockConnects[i].isConnected  	= false;

		for(int j=0; j<6; j++) g_allSockConnects[i].macAddr[j]  = 0;
		g_allSockConnects[i].devIndex     	= -1;
	
		int indexPlusOne = i+1;

		sprintf(g_allSockConnects[i].ipAddr, "192.168.84.%d", indexPlusOne);

		g_allSockConnects[i].listen_sock  	= -1;



		// =================================================================================================
		// < INITIALIZING STRUCT INSIDE OF STRUCT >

		// < INITIALIZING STRUCT AFTER DECLARATION >
		// https://dixq.net/forum/viewtopic.php?t=15166
		// :: YOU CANNOT INITIALZE STRUCT USING { , ,  ... } AFTER
		//    DECLARATION LIKE 'strctName c; '
		//    NEED TO DO c.a = 111;  c.b = 222; ...

		// < INITIALIZING STRUCTS > 
		// https://stackoverflow.com/questions/20829859/initializing-a-struct-within-a-struct
		// :: YOU CAN INITIALIZE STRUCT WHEN YOU DECLARE LIKE BELOW
		//
		// struct firstStruct 
		// {
		//     int a;
		//     int b;  
		// };
		//
		// struct secondStruct
		// {
		//     S1 a;
		//     char b;
		// };
		//
		// secondstruct = { { 1, 2 }, 3 };


		// < STRUCT sockaddr_in >
		// https://www.coins.tsukuba.ac.jp/~syspro/2022/2022-07-06/sockaddr-struct.html
		//
		// struct sockaddr_in {
		// 	__uint8_t	sin_len;
		// 	sa_family_t	sin_family;
		// 	in_port_t	sin_port;
		// 	struct	in_addr sin_addr;
		// 	char		sin_zero[8];
		// };


		// < STRUCT sockaddr_in6 AND in6_addr >
		// https://pubs.opengroup.org/onlinepubs/000095399/basedefs/netinet/in.h.html
		// https://man7.org/linux/man-pages/man7/ipv6.7.html
		//
		// struct sockaddr_in6 {
		//     sa_family_t     sin6_family;   /* AF_INET6 */
		//     in_port_t       sin6_port;     /* port number */
		//     uint32_t        sin6_flowinfo; /* IPv6 flow information */
		//     struct in6_addr sin6_addr;     /* IPv6 address */
		//     uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */
		// };

		// struct in6_addr {
		//     unsigned char   s6_addr[16];   /* IPv6 address */
		// };


		// < INITIALIZING STRUCT >
		// https://www.codeproject.com/Questions/5253587/How-to-initialize-a-variable-declared-as-unsigned
		// :: WE CAN INITIALIZE LIKE 
		//    .sin6_addr.s6_addr = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//              ^
		//              *  (INSIDE sin6_addr, THERE IS s6_addtr STRUCT)



		ESP_LOGI(TAG, "||||  INITIALIZING ALL SOCKET CONNECTION STRUCT  ::  dest_addr  ||||");
		// https://techoverflow.net/2022/07/27/how-to-initialize-struct-sockaddr_in-using-initializer-lists/
		//
		struct sockaddr_in server_addr = {
		    .sin_family = AF_INET,
		    .sin_port = htons(3333),
		    .sin_addr = {.s_addr = inet_addr(g_allSockConnects[i].ipAddr)}
		};
		g_allSockConnects[i].dest_addr = &server_addr;


		g_allSockConnects[i].connect_sock   = -1;



		// ESP_LOGI(TAG, "||||  INITIALIZING ALL SOCKET CONNECTION STRUCT  ::  source_addr  ||||");
		// struct sockaddr_in6 src_addr = {
		//     .sin6_len = 0,
		//     .sin6_family = 0,
		//     .sin6_port = 0,
		//     .sin6_flowinfo = 0,
		//     .sin6_addr.s6_addr = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		//     .sin6_scope_id = 0

		// };
		// g_allSockConnects[i].source_addr = &src_addr;


		// g_allSockConnects[i].addr_len    	= -1;


		g_allSockConnects[i].errBind    	= -1;
		g_allSockConnects[i].errListen    	= -1;

	}

}

static void createOneSocketStruct(int ind) {

	// < INITIALIZING ALL SOCKET CONNECTION STRUCT >
	// https://stackoverflow.com/questions/330793/how-to-initialize-a-struct-in-accordance-with-c-programming-language-standards

	ESP_LOGI(TAG, "||||  INITIALIZING ONE SOCKET CONNECTION STRUCT  ||||");




	g_allSockConnects[ind].isConnected  	= false;

	for(int j=0; j<6; j++) g_allSockConnects[ind].macAddr[j]  = 0;
	g_allSockConnects[ind].devIndex     	= -1;

	int indexPlusOne = ind+1;

	sprintf(g_allSockConnects[ind].ipAddr, "192.168.84.%d", indexPlusOne);

	g_allSockConnects[ind].listen_sock  	= -1;






	ESP_LOGI(TAG, "||||  INITIALIZING ONE SOCKET CONNECTION STRUCT  ::  dest_addr  ||||");
	// https://techoverflow.net/2022/07/27/how-to-initialize-struct-sockaddr_in-using-initializer-lists/
	//
	struct sockaddr_in server_addr = {
	    .sin_family = AF_INET,
	    .sin_port = htons(3333),
	    .sin_addr = {.s_addr = inet_addr(g_allSockConnects[ind].ipAddr)}
	};
	g_allSockConnects[ind].dest_addr = &server_addr;


	g_allSockConnects[ind].connect_sock   = -1;



	// ESP_LOGI(TAG, "||||  INITIALIZING ALL SOCKET CONNECTION STRUCT  ::  source_addr  ||||");
	// struct sockaddr_in6 src_addr = {
	//     .sin6_len = 0,
	//     .sin6_family = 0,
	//     .sin6_port = 0,
	//     .sin6_flowinfo = 0,
	//     .sin6_addr.s6_addr = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//     .sin6_scope_id = 0

	// };
	// g_allSockConnects[i].source_addr = &src_addr;


	// g_allSockConnects[i].addr_len    	= -1;


	g_allSockConnects[ind].errBind    		= -1;
	g_allSockConnects[ind].errListen    	= -1;

}

static void instanceOneSocket(int ind) {


	g_allSockConnects[ind].listen_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_IP );

	//fcntl(g_allSockConnects[ind].listen_sock, F_SETFL, O_NONBLOCK);

	if(g_allSockConnects[ind].listen_sock < 0) {
	    ESP_LOGE(TAG, "Unable to create socket NUMBER   %d   :   errno %d", ind, errno);
	}

}

static void instanceAllSockets() {

	for(int i=0; i<MAX_SOCKET_COUNTS; i++) {
		instanceOneSocket(i);
	}

}

static void acceptSocket() {



	printf("LET US DO SOCKET CONNECTION !\n");

	// CHECKING g_allSockConnects STRUCT ARRAY ...
	for(int i=0; i<MAX_SOCKET_COUNTS; i++) {

		if( g_allSockConnects[i].isConnected == true ) {

			printf("OK, IP-ADDRESS    %s    SHOULD BE ACCEPTED WITH SOCKET !!!!\n", g_allSockConnects[i].ipAddr);

		}

	}
	

	// < SETTING UP LISTENER FOR OUR SOCKET >
	// :: WE DEFINED IPv4 AS SETTING "AF_INET" TO sockaddr STRUCT
	//    THEN WE SETTED PORT NUMBER WE WANT TO LISTEN
	//    SO,
	//    OUT SERVER DEVICE WILL LISTEN ANY CONNECTIONS IN PORT NUMBER (IN THIS CASE 3333)
	// 
	//
	//  < htonl, htons > 
	//  https://www.gta.ufrj.br/ensino/eel878/sockets/htonsman.html
	//
	//
	//  https://linuxhint.com/sockaddr-in-structure-usage-c/#:~:text=The%20%E2%80%9Csockaddr_in%E2%80%9D%20structure%20is%20very,to%20the%20clients'%20connection%20requests.
	//
	// 
	// < How to give to a client specific ip address in C >
	// https://stackoverflow.com/questions/15673846/how-to-give-to-a-client-specific-ip-address-in-c
	//



	// ------------------------------------------------------------------
	// SETTING UP IP ADDRESS TO DESTINATION ADDRESS
	//
	// < struct sockaddr_in, struct in_addr >
	// https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html


	// for(int i=0; i<MAX_SOCKET_COUNTS; i++) {

	// 	if( g_allSockConnects[i].isConnected == true ) {

	// 		printf("SETTING UP IP ADDRESS    %s    TO DESTINATION ADDRESS   !!!!\n", g_allSockConnects[i].ipAddr);

	// 		//inet_aton("192.168.84.1", g_allSockConnects[i].dest_addr->sin_addr.s_addr);
	// 		//inet_aton(g_allSockConnects[i].ipAddr, g_allSockConnects[i].dest_addr->sin_addr.s_addr);
			
	// 		//g_allSockConnects[i].dest_addr->sin_addr.s_addr = htonl(INADDR_ANY);

	// 	}

	// }





	// ---------------------------------
	// < LISTENING SOCKET >
	// 
	// < socket() FUNCTION >
	// PARAMETERS:
	// addr_family  -->  IP ADDRESS FAMILY 
	// SOCK_STREAM  -->  TYPE OF SOCKET
	// ip_protocol  -->  IP PROTOCOL




	// < BINDING + LISTENING SOCKET TO IP ADDRESS WE SETTED ABOVE >

	// CHECKING g_allSockConnects STRUCT ARRAY ...
	for(int i=0; i<MAX_SOCKET_COUNTS; i++) {

		if( g_allSockConnects[i].isConnected == true ) {


			struct sockaddr_in dest_addr;
			dest_addr.sin_family = AF_INET;
			dest_addr.sin_addr.s_addr = inet_addr(g_allSockConnects[i].ipAddr);
			//dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			//dest_addr.sin_addr.s_addr = htons(INADDR_ANY);
			dest_addr.sin_port = htons(TCP_PORT);



			g_allSockConnects[i].dest_addr = &dest_addr;

			g_allSockConnects[i].addr_len = sizeof(g_allSockConnects[i].dest_addr);


			// BINDING SOCKET
			// g_allSockConnects[i].errBind = bind(g_allSockConnects[i].listen_sock, 
			// 									(struct sockaddr*)g_allSockConnects[i].dest_addr, 
			// 									sizeof(struct sockaddr_in));

			g_allSockConnects[i].errBind = bind(g_allSockConnects[i].listen_sock, 
												(struct sockaddr*)&dest_addr, 
												sizeof(dest_addr));

			// ERROR CHECKING...
			if(g_allSockConnects[i].errBind != 0) {

			    ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
			    ESP_LOGE(TAG, "IPPROTO: %d", AF_INET);
			    close(g_allSockConnects[i].listen_sock);

			    ESP_LOGI(TAG, "(*(((*(**(    SOCKET WAS FAILED  TO BIND !!!!!!!!\n");

			} else {

				ESP_LOGI(TAG, "Socket INDEX  | %d |  IS bound, port %d", g_allSockConnects[i].devIndex, TCP_PORT);

			}


			printf("**********************************\n");
			printf("ATTEMPTING TO LISTEN THE PORT ... \n");


			// < SOCKET LISTENING START >
			g_allSockConnects[i].errListen = listen(g_allSockConnects[i].listen_sock, 1);    // Most of them are online 5, why is it here

			// ERROR CHECKING...
			if(g_allSockConnects[i].errListen != 0) {

			    printf("Error occurred during listen: errno %d\n", errno);
			    close(g_allSockConnects[i].listen_sock);
			} else {

				printf("SUCCESSFULLY LISTENING !!!!\n");

			}


		}


	}







	// // =================================================================================


	// //ESP_LOGI(TAG, "< SOCKET COMMUNICATION >");



	// // ----------------------------------------------------
	// // < LOOP FOR SOCKET >
	// // 
	// // THIS SOCKET IS FOR TRANSFERRING EVERY SINGLE MESSAGE ONE BY ONE !!!!


	// // -------------------------------------------------
	// // < ABOUT ERRNO 9 WHEN USING SOCKET >
	// // https://stackoverflow.com/questions/17207051/what-could-be-the-reason-for-a-socket-error-errno-9-bad-file-descriptor
	// //
	// // :: Read the documentation for socket.close(). 
	// // You cannot reuse it in any operation (including connect) once you 
	// // close it. It needs to be reinitialized with a call to socket.socket. – 


 // 	//  struct sockaddr_in6 source_addr; // Large enough for both IPv4 or IPv6
 // 	//  uint addr_len = sizeof(source_addr);


	// // ---------------------
	// // < POLL SERVER >
	// // https://github.com/weboutin/simple-socket-server/blob/master/poll-server.c
	// // :: USING POLL FUNCTION, WE CAN 





	// // TODO :: POLL OR SELECT FUNCTION
	// // https://github.com/weboutin/simple-socket-server/blob/master/poll-server.c





	// // if( g_allSockConnects[0].isConnected == true ) {

	// //     g_allSockConnects[0].connect_sock = accept(g_allSockConnects[0].listen_sock, 
	// //     										   (struct sockaddr *)g_allSockConnects[0].dest_addr, 
	// //     										   g_allSockConnects[0].addr_len);

	// //     if(g_allSockConnects[0].connect_sock < 0) {

	// //         ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
	// //         close(g_allSockConnects[0].listen_sock);

	// //     }   
	// // }



	// ESP_LOGI(TAG, "FROM NOW, WE WILL ACCEPT THE COMMUNICATION WITH SOCKET....................");

	// // CHECKING g_allSockConnects STRUCT ARRAY ...
	// for(int i=0; i<MAX_SOCKET_COUNTS; i++) {

	// 	if( g_allSockConnects[i].isConnected == true ) {

	// 	    g_allSockConnects[i].connect_sock = accept(g_allSockConnects[i].listen_sock, 
	// 	    										   (struct sockaddr *)g_allSockConnects[i].dest_addr, 
	// 	    										   (socklen_t *)g_allSockConnects[i].addr_len);

	// 	    if(g_allSockConnects[i].connect_sock < 0) {

	// 	        ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
	// 	        close(g_allSockConnects[i].listen_sock);

	// 	    }   

	// 	}

	// }

}

static int filterMacAddr(void* event_data) {

	// ====================================================================================

	// CONTAINER FOR MAC-ADDRESS OF INCOMING DEVICE
	int devMacAddr[6];


	// -----------------------------------------
	// GETTING MAC ADDRESS OF CONTACTED DEVICE
	wifi_event_ap_staconnected_t* ev_connected = (wifi_event_ap_staconnected_t*) event_data;

	printf("ev_connected->mac    ");
	for(int i=0; i<6; i++) {
		printf(" | %d  ", ev_connected->mac[i] );

		// STORING MAC ADDRESS
		devMacAddr[i] = ev_connected->mac[i];
	
	}
	printf("\n");




	// ======================================================
	// TODO :: >>>>>>

	// 1. FILTERING HTTP SERVER AND ESP32 MODULES !!
	//    :: WE WILL USE "MAC-ADDRESS" !!!!
	// 



	// SEARCHING MAC ADDRESS WITH ABOVE ADDRESS
	int matchedMacAddr[6];
	int deviceIndex = -1;
	int matchScore = 0;

	// FOR 9 CLIENT MAC-ADDRESSES
	for(int i=0; i<MAX_SOCKET_COUNTS; i++) {
		

		// CHECK 1st ZONE OF SINGLE MAC-ADDRESS NUMBER
		if( g_allMacAddresses[i][0] == devMacAddr[0] ) {

			// IF IT MATCHED...

			// FOR 6 NUMBERS WHICH CONSTRUCTS SINGLE MAC-ADDRESS
			for(int j=0; j<6; j++) {

				// CHECK IF WHOLE NUMBERS ARE MATCHING...
				if(g_allMacAddresses[i][j] != devMacAddr[j]) {
					//printf("$$$$  WARNING $$$$   THERE IS NO-MATCHED MAC-ADDRESS !!!!\n");
					break;

				} else {
					// INCREASING SCORE
					matchScore += 1;
					//printf("CURRENT match SCORE   ::   %d \n", matchScore );
				}
			}
			if( matchScore >= 6) {

				// STORING DEVICE INDEX
				deviceIndex = i;

			}

		} else {

			//printf("NOT MATCHED WITH INCOMING IP ADDRESS AND DEVICE INDEX ...   %d \n", i);						

			//printf("------------------ \n");
			//printf("&&&&  BELOW MAC-ADDRESS vvvv\n");
			// for(int k=0; k<6; k++) {

			// 	printf("%d :: ", g_allMacAddresses[i][k] );

			// }
			//printf("\n WAS NOT MATCHED WITH INCOMING IP ADDRESS\n");
			//printf("vvvv\n");
			// for(int m=0; m<6; m++) {
			// 	printf("%d :: ", devMacAddr[m] );
			// }
			// printf("\n ------------------ \n");

		}

	}


	// SCORE CHECK
	if( matchScore >= 6) {
		printf("---------------------------------------------------\n");

		printf("THERE IS INCOMING DEVICE + MATCHED MAC-ADDRESS !!!!\n");

		// TRANSFERRING DATA
		printf("MATCHED MAC-ADDRESS  ::     ");
		for(int l=0; l<6; l++) {
			printf("%d :: ", devMacAddr[l] );
			matchedMacAddr[l] = devMacAddr[l];
		}
		printf("\n");

		
		// 0 TO 9 IS TRUTHFUL DATA
		return deviceIndex;

	} else {

		// -1 IS FALSE
		return -1;


	}

}

static void socketConnectWork(int deviceIndex) {

	// FORMATTING IP ADDRESS FROM MAC-ADDRESS
	char ipAddrCreated[128];


	int ipAddrLastNum = deviceIndex+1;
	sprintf(ipAddrCreated, "192.168.84.%d", ipAddrLastNum);
	ipAddrCreated[12] = '\0';

	printf("&&&*&&  INCOMING  IP-ADDRESS IS  ipAddrCreated   -->    %s\n", ipAddrCreated );


	// IF SOCKET CONNECT IS NOT USED (ALREADY CONNECTED)...
	if(g_allSockConnects[deviceIndex].isConnected == false) {

		g_allSockConnects[deviceIndex].isConnected = true;

		for(int n=0; n<6; n++) g_allSockConnects[deviceIndex].macAddr[n] = g_allMacAddresses[deviceIndex][n];
		g_allSockConnects[deviceIndex].devIndex    = deviceIndex;
		sprintf(g_allSockConnects[deviceIndex].ipAddr, "%s", ipAddrCreated);

	}

}

static void socketDisconnectWork(int deviceIndex_dis) {

	// FORMATTING IP ADDRESS FROM MAC-ADDRESS
	char ipAddrCreated_dis[128];

	int ipAddrLastNum = deviceIndex_dis+1;
	sprintf(ipAddrCreated_dis, "192.168.84.%d", ipAddrLastNum);
	ipAddrCreated_dis[12] = '\0';

	printf("&&&*&&  DISCONNECTING  IP-ADDRESS IS  ipAddrCreated_dis   -->    %s\n", ipAddrCreated_dis );


	// IF SOCKET CONNECT IS NOT USED (ALREADY CONNECTED)...
	if(g_allSockConnects[deviceIndex_dis].isConnected == true) {


		printf("SHUTTING DOWN CONNECTION   -->    %s\n", ipAddrCreated_dis );
        shutdown(g_allSockConnects[deviceIndex_dis].connect_sock, 0);


        printf("CLOSING DOWN CONNECTION   -->    %s\n", ipAddrCreated_dis );
        close(g_allSockConnects[deviceIndex_dis].connect_sock);

        // printf("CLOSING DOWN LISTENING   -->    %s\n", ipAddrCreated_dis );
        // close(g_allSockConnects[deviceIndex_dis].listen_sock);


		g_allSockConnects[deviceIndex_dis].isConnected = false;


        printf("INITIALIZING  DEVICE INDEX   ::   %d... \n", deviceIndex_dis );

		createOneSocketStruct(deviceIndex_dis);

	}

}




// ================================================================================================
// < EVENT GROUP BIT HANDLING >
//
// WiFi application event handler
// arg 			: data, aside from event data, that is passed to the handler when it is called
// event_base 	: the base id of the event to register the handler for
// event_id 	: the id for the event to register the handler for
// event_data 	: event data
//
static void wifi_app_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {


	if (event_base == WIFI_EVENT) {

		switch (event_id) {

			case WIFI_EVENT_AP_START:
				ESP_LOGI(TAG, "WIFI_EVENT_AP_START");
				break;

			case WIFI_EVENT_AP_STOP:
				ESP_LOGI(TAG, "WIFI_EVENT_AP_STOP");
				break;

			case WIFI_EVENT_AP_STACONNECTED:
				ESP_LOGI(TAG, "WIFI_EVENT_AP_SOME_STA_IS_CONNECTED");

				break;

			case WIFI_EVENT_AP_STADISCONNECTED:
				ESP_LOGI(TAG, "WIFI_EVENT_AP_SOME_STA_IS_DISCONNECTED");

				break;

			case WIFI_EVENT_STA_START:
				ESP_LOGI(TAG, "WIFI_EVENT_THIS_STA_START");
				break;

			case WIFI_EVENT_STA_CONNECTED:
				ESP_LOGI(TAG, "WIFI_EVENT_THIS_STA_CONNECTED");
				break;

			case WIFI_EVENT_STA_DISCONNECTED:
				ESP_LOGI(TAG, "WIFI_EVENT_THIS_STA_DISCONNECTED");

				wifi_event_sta_disconnected_t *wifi_event_sta_disconnected = (wifi_event_sta_disconnected_t*)malloc(sizeof(wifi_event_sta_disconnected_t));
				*wifi_event_sta_disconnected = *((wifi_event_sta_disconnected_t*)event_data);
				printf("WIFI_EVENT_THIS_STA_DISCONNECTED, reason code %d\n", wifi_event_sta_disconnected->reason);

				if (g_retry_number < MAX_CONNECTION_RETRIES)
				{
					esp_wifi_connect();
					g_retry_number ++;
				}
				else
				{
					wifi_app_send_message(WIFI_APP_MSG_STA_DISCONNECTED);
				}

				break;
		}


	} else if (event_base == IP_EVENT) {

		switch (event_id) {

			case IP_EVENT_STA_GOT_IP:
				ESP_LOGI(TAG, "IP_EVENT_STA_GOT_IP");

				wifi_app_send_message(WIFI_APP_MSG_STA_CONNECTED_GOT_IP);

				break;
		}
	}

}

// < THIS FUNCTION IS FOR "WIFI EVENT" AND "IP EVENT" >
// :: SO WE CAN SAY THAT THIS COVERS "NETWORK" LAYER IN OSI MODEL !
//  
static void wifi_app_event_handler_init(void) {

	// -----------------------
	// < CREATING EVENT LOOP >
	// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/esp_event.html#event-loop-library
	// : THIS LIBRARY ALLOWS TO DEFINE EVENT AND 
	//   HANDLERS WHEN THE EVENT WAS RECEIVED

	// CREATING 'DEFAULT TYPE' OF EVENT LOOP
	ESP_ERROR_CHECK( esp_event_loop_create_default() );


	// -----------------------
	// EVENT HANDLER INSTANCE OBJECT
	// 
	// < THIS DEALS WITH WIFI AND IP EVENT >
	//
	esp_event_handler_instance_t instance_wifi_event;
	esp_event_handler_instance_t instance_ip_event;


	// -------------------------------------------------------------
	// < REGISTER AN INSTANCE OF EVENT HANDLER TO THE DEFAULT LOOP >
	//
	// < esp_event_handler_instance_register FUNCTION >
	// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/esp_event.html#_CPPv435esp_event_handler_instance_register16esp_event_base_t7int32_t19esp_event_handler_tPvP28esp_event_handler_instance_t 
	// : REGISTERING EVENT HANDLER TO THE 'DEFAULT LOOP' 
	// 
	//   ARGUMENTS
	//   esp_event_base_t 				event_base 			: BASE ID OF EVENT (IT IS LIKE LAST NAME! )
	//   int32_t 						event_id 			: SPECIFIC ID OF EVENT (FIRST NAME!)
	//   esp_event_handler_t 			event_handler 		: EVENT HANDLER FUNCTION TO EXECUTE!
	//   void * 						event_handler_arg 	: ARGUMENTS PASSING TO ABOVE EVENT HANDLER!
	//   esp_event_handler_instance_t *	instance 			: EVENT HANDLER INSTANCE OBJECT WHICH IS RELATED TO THE REGISTERED EVENT HANDLER AND DATA
	//
	//
	ESP_ERROR_CHECK( esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_app_event_handler, NULL, &instance_wifi_event));
	ESP_ERROR_CHECK( esp_event_handler_instance_register(IP_EVENT,   ESP_EVENT_ANY_ID, &wifi_app_event_handler, NULL, &instance_ip_event));

}

// < THIS FUNCTION IS FOR "TCP CONNECTION" AND "WIFI CONFIGURATION" >
// :: SO WE CAN SAY THAT THIS COVERS "TRANSPORT" LAYER IN OSI MODEL !
//  
static void wifi_app_default_wifi_init(void) {

	// Initialize the TCP stack
	ESP_ERROR_CHECK( esp_netif_init() );

	// Default WiFi config - operations must be in this order!
	wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(  esp_wifi_init(&wifi_init_config)  );
	ESP_ERROR_CHECK(  esp_wifi_set_storage(WIFI_STORAGE_RAM)  );

	// CREATING PROPER HANDLERS !
	esp_netif_sta = esp_netif_create_default_wifi_sta();
	esp_netif_ap  = esp_netif_create_default_wifi_ap();

}

// --------------------------------------
// < STATION AND SOFT-AP MODE IN ESP32 >
//
// 1.
// https://techtutorialsx.com/2021/01/04/esp32-soft-ap-and-station-modes/
//
// When working in station mode, the ESP32 is acting as a WiFi enabled device connected 
// to an existing WiFi network. 
// 
// ****  WHEN WORKING IN SOFT AP MODE, THE ESP32 IS ACTING AS HOST OF A WIFI NETWORK, ****
// to which other devices can connect.
//
//
// 2.
// https://randomnerdtutorials.com/esp32-access-point-ap-web-server/
// 
// In most projects with the ESP32, we connect the ESP32 to a wireless router 
// (see our ESP32 web server tutorial). This way we can access the ESP32 through the local network.
//
// In this situation the router acts as an access point and the ESP32 is set as a station. 
// In this scenario, you need to be connected to your router (local network) to control the ESP32.
//
// But if you set the ESP32 as an access point (hotspot), you can be connected to the ESP32 using 
// any device with Wi-Fi capabilities without the need to connect to your router.
//
// In simple words, when you set the ESP32 as an access point you create its own Wi-Fi network and 
// nearby Wi-Fi devices (stations) can connect to it (like your smartphone or your computer).
//
//
// < SETTING SOFT AP MODE >
// Configures the WiFi access point settings and assigns the static IP to the SoftAP.

static void wifi_app_soft_ap_config(void) {

	// SoftAP - WiFi access point configuration
	wifi_config_t ap_config =
	{
		.ap = {
				.ssid = WIFI_AP_SSID,
				.ssid_len = strlen(WIFI_AP_SSID),
				.password = WIFI_AP_PASSWORD,
				.channel = WIFI_AP_CHANNEL,
				.ssid_hidden = WIFI_AP_SSID_HIDDEN,
				.authmode = WIFI_AUTH_WPA2_PSK,
				.max_connection = WIFI_AP_MAX_CONNECTIONS,
				.beacon_interval = WIFI_AP_BEACON_INTERVAL,
		},
	};

	// Configure DHCP for the AP
	esp_netif_ip_info_t ap_ip_info;
	memset(&ap_ip_info, 0x00, sizeof(ap_ip_info));


	// SETTING UP OUR SERVER
	// IP ADDRESS, AND SETTINGS

	// SEEMS LIKE WE NEED TO RUN BELOW AT THE FIRST PLACE !!

	// --------------------------------
	// esp_netif_dhcps_stop() FUNCTION
	// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_netif.html
	// :: Stop DHCP server (only if enabled in interface object)
	//
	// Parameters
	// esp_netif – [in] Handle to esp-netif instance
	//
	esp_netif_dhcps_stop(esp_netif_ap);												///> must call this first


	// SETTING UP IP ADDRESS FOR OUR SERVER
	inet_pton(AF_INET, WIFI_AP_IP, &ap_ip_info.ip);									///> Assign access point's static IP, GW, and netmask
	inet_pton(AF_INET, WIFI_AP_GATEWAY, &ap_ip_info.gw);
	inet_pton(AF_INET, WIFI_AP_NETMASK, &ap_ip_info.netmask);

	ESP_ERROR_CHECK( esp_netif_set_ip_info(esp_netif_ap, &ap_ip_info) );			///> Statically configure the network interface

	// FOR CONNECTION WITH OUR CLIENT DEVICES !
	// WE RUN DHCP STYLE SO WE WILL GIVE THE GENERATED IP ADDRESS TO OUR NEWCOMER !!
	ESP_ERROR_CHECK( esp_netif_dhcps_start(esp_netif_ap) );							///> Start the AP DHCP server (for connecting stations e.g. your mobile device)

	// CONFIGURE THIS SERVER DEVICE TO ACCESS POINT + STATION MODE
	// SO THIS SERVER DEVICE "CAN ACCESS" TO OTHER ACCESS POINT !!
	//
	ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_APSTA) );							///> Setting the mode as Access Point / Station Mode
	ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_AP, &ap_config) );				///> Set our configuration
	ESP_ERROR_CHECK( esp_wifi_set_bandwidth(WIFI_IF_AP, WIFI_AP_BANDWIDTH) );		///> Our default bandwidth 20 MHz
	ESP_ERROR_CHECK( esp_wifi_set_ps(WIFI_STA_POWER_SAVE) );						///> Power save set to "NONE"

}

// < WHEN THIS MODULE IS CONNECTED TO ANOTHER MODULE >
// :: THIS MODULE WILL BE "STATION" 
static void wifi_app_connect_sta(void) {

	ESP_ERROR_CHECK(esp_wifi_set_config( ESP_IF_WIFI_STA, wifi_app_get_wifi_config() ));
	ESP_ERROR_CHECK(esp_wifi_connect());

}

static void getMessageFromClient(const int sock, char* buff) {
    int len = -1;

	printf("++++++++++    WE ARE NOW BLOCKED AND RECEIVING DATA    ++++++++++\n++++++++++    BUT WE ALREADY SELECTED SO IT WILL GET THROUGH   ++++++++++\n");

	char dat[128];
    len = recv(sock, dat, sizeof(dat) - 1, 0);

    sprintf(buff, "%s", dat);
    buff[len] = '\0';


    printf("getMessageFromClient  ::    %s   IS GOT ,  len IS   %d  \n", buff, len);



    if (len < 0) {

        ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        buff = "\0";

    } else if (len == 0) {

        ESP_LOGW(TAG, "Connection closed");
        buff = "\0";

    } else {

        buff[len] = '\0'; // Null-terminate whatever is received and treat it like a string
        ESP_LOGI(TAG, "Received %d bytes: %s", len, buff);
        
    }

}

static void do_sendSceneList(const int sock) {

	// BELOW FUNCTION http_server_getLinkedSubjectsResult() 
	// JUST GETS THE GLOBAL VARIABLE FROM HTTP-SERVER 
	// SO,
	// JUST WAIT FOR A WHILE TO GET THE GLOBAL VARIABLE FROM HTTP SERVER,
	// BECAUSE WHEN HTML BUTTON IS CLICKED, IT NEEDS TO BE CALCULATED TO STORE THE RESULT TO 
	// THAT GLOBAL VARIABLE 
	//vTaskDelay( 500 / portTICK_PERIOD_MS);

	ESP_LOGI(TAG, "WIFI_APP_MSG_SOCKET_COMMUNICATION: FIRST, OUR COLLECTED SCENE NUMBER IS...");



	// GETTING SCENE NUMBERS FROM HTTP SERVER !!!!
	http_linkedSubjects_result_t sceneNumberResult;
	sceneNumberResult = http_server_getLinkedSubjectsResult();

	// GETTING OTHER SCENE NUMBER
	int* linkedScenes = sceneNumberResult.linkedSubjects;
	int  linkedCount  = sceneNumberResult.linkedCount;


	// FOR DEBUG
	printf("PRINTING OUT linkedScenes  --vvv\n");
	for(int t=0; t < 9; t++) {
		printf(" | %d  ", linkedScenes[t]);
	}
	printf("\r\n");



	// RECEIVING DATA AND SEND BACK TO CLIENT
	//printf("linkedScenes  TEST  ...    %d  \n", linkedScenes[0]);

	if(linkedScenes[0] != 0) {

		answerToClient(sock, 
			  		   linkedScenes, 
			  		   linkedCount);

	} else {

		printf("linkedScenes IS  0 !!!! WE DO NOT SEND DATA TO CLIENT !!!!\n");

	}

}


static int sendMessage(SOCKET sock, char* msg, int len) {

	int written = send( sock, msg, len, 0 );

    if (written < 0) {
        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        return -1;

    } else {

		ESP_LOGI(TAG, "SENT : len: %d", written);
		return 0;

    }

} 


// WE CHECK STRING IS INCLUDING ".",
// &&
// EXCLUDING "~" 
static bool checkStrIsIp(char* str) {

	char* token_ipChk;
	char* token_scnChk;

	char copied_ipChk[64];
	char copied_scnChk[64];
	int len = strlen(str);



	for(int i=0; i<len; i++) {
		copied_ipChk[i] = str[i];
		copied_scnChk[i] = str[i];
	}

	copied_ipChk[len] = '\0';
	copied_scnChk[len] = '\0';
	
	token_ipChk = strtok(copied_ipChk, ".");
	token_scnChk = strtok(copied_scnChk, "_");

	//printf("TOKEN FOR IP ADDRESS   ->  %s  \n", token_ipChk);
	//printf("TOKEN FOR SCENE NUMBER ->  %s  \n", token_scnChk);


	bool isIpAddr = true;
	bool isScnNum = true;


	// IF TOEKNIZED WORD IS SAME AS ORIGINAL ONE, THAT MEANS "NO MATCHED"
	if( strcmp(token_ipChk,  str) == 0 ) isIpAddr = false;
	if( strcmp(token_scnChk, str) == 0 ) isScnNum = false;



	if( isIpAddr == true && isScnNum == false) {

		// THEN THIS CASE IS FOR IP ADDRESS
		return true;	

	} else {

		return false;

	}
}



static void wifi_sock_task(void *pvParameters) {


    if (g_addr_family == AF_INET) {
        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&g_dest_addr;
        dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
        dest_addr_ip4->sin_family = AF_INET;
        dest_addr_ip4->sin_port = htons(TCP_PORT);
        g_ip_protocol = IPPROTO_IP;
    }


    g_listen_sock = socket(g_addr_family, SOCK_STREAM, g_ip_protocol);



    if (g_listen_sock < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }


    int opt = 1;
    setsockopt(g_listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    ESP_LOGI(TAG, "Socket created");




    int err = bind(g_listen_sock, (struct sockaddr *)&g_dest_addr, sizeof(g_dest_addr));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        ESP_LOGE(TAG, "IPPROTO: %d", g_addr_family);
        goto CLEAN_UP;
    }
    ESP_LOGI(TAG, "Socket bound, port %d", TCP_PORT);



    err = listen(g_listen_sock, 1);
    if (err != 0) {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        goto CLEAN_UP;
    }







    FD_ZERO(&g_master_fdset);
    FD_SET(g_listen_sock, &g_master_fdset);
    g_max_socket = g_listen_sock;



    SOCKET socket_client;


    while (1) {


        fd_set readFd;
        readFd = g_master_fdset;

		printf("++++++++++++++   BLOCKED (SELECTING)  ++++++++++++++++\n");


        if ( select(g_max_socket+1, &readFd, 0, 0, 0) < 0 ) {

        	// IF SELECT FUNCTION IS FAILED ...
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            goto CLEAN_UP;
        }

		// WHEN SOME CLIENT IS << CONNECTED >> TO THIS, 
		// THE PROCESS WILL GET THROUGH !!!!

		printf("////   BLOCKING PURGED !! -- THEN WE NEED TO ACCEPT THE CLIENT TO EASTABLISH THE CONNECTION !!\n");
		printf("       vvvvvvvvvvvvvvv\n");


        SOCKET i;

        // FOR EVERY SOCKETS ......
        for(i = 1; i <= g_max_socket; ++i) {

        	//printf("FILE DESC FOR-LOOP    ::  SOCKET  i  ::   %d   ,   g_max_socket  ::   %d \n", i, g_max_socket);

        	// // ================================================
        	// // SEMAPHORE CHECK !!!!
        	// // ================================================

        	// if( xSemaphoreTake ( g_xSemaphore, portMAX_DELAY) ) {

        	// 	printf("-*-*-*-    GOT SEMAPHORE !   ==   WE CAN GET THROUGH !!!!  ==   %d    -*-**-*-*-- \n", xTaskGetTickCount());

        	if( g_sockLoopGate == true ) {


	        	// ----------------------------------------------------------------------------
	        	// IF ANY FILE DESCRIPTOR IN FD SET IS READY FOR << READING >>
	        	// ----------------------------------------------------------------------------
	            if (FD_ISSET(i, &readFd)) {
	            	printf("< READING >  FILE DESC FOR-LOOP    ::  SOCKET  i  ::   %d   OF   g_max_socket  ::   %d \n", i, g_max_socket);
	            	printf("< READING >                            CHECKING CURRENT SOCKET || %d || IS READY OR NOT...\n", i);

	                if (i == g_listen_sock) {

		            	printf("< READING >                            SOCKET || %d || IS READY !!!!\n", i);
				        
				        
				        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
				        socklen_t addr_len = sizeof(source_addr);

				        // ===================================================================================================
				        // ACCEPTING CONNECTIONS
	     
				        socket_client = accept(g_listen_sock, 
				        					   (struct sockaddr *)&source_addr, 
				        					   &addr_len);
				   	    printf("< READING >                            SOCKET || %d || IS ACCEPTED AND MADE IT CONNECTED !!!!\n", i);
				        
				        if (socket_client < 0) {
				            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
				            break;
				        }



				        // ---------------------------------------------------------------------------------------------------
				        // SETTING ACCEPTED SOCKET'S FD TO FD-SET
	                    FD_SET(socket_client, &g_master_fdset);

	                    // IF ACCEPTED SOCKET'S INDEX IS OVER THAN MAXIMUM
	               		// EXPAND MAXIMUM VALUE TO THAT NUMBER !!!!
	                    if (socket_client > g_max_socket) g_max_socket = socket_client;


				        // ---------------------------------------------------------------------------------------------------
				        // Set tcp keepalive option
				        setsockopt(socket_client, SOL_SOCKET, SO_KEEPALIVE, &g_keepAlive, sizeof(int));
				        setsockopt(socket_client, IPPROTO_TCP, TCP_KEEPIDLE, &g_keepIdle, sizeof(int));
				        setsockopt(socket_client, IPPROTO_TCP, TCP_KEEPINTVL, &g_keepInterval, sizeof(int));
				        setsockopt(socket_client, IPPROTO_TCP, TCP_KEEPCNT, &g_keepCount, sizeof(int));

				        // Convert ip address to string
				        if (source_addr.ss_family == PF_INET) {
				            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, 
						            	g_addr_str, 
						            	sizeof(g_addr_str) - 1);
				        }

				        ESP_LOGI(TAG, "Socket accepted ip address: %s", g_addr_str);
				        printf("CONNECTION EASTABLISHED !!!! \n");


				        // GETTING DEVICE INDEX TO DECIDE 
				        // WE SEND SCENE LIST TO OUT CLIENTS
						char rtnMsg[128];

						// GETTING IP ADDRESS FROM CLIENT
						printf("GETTING MESSAGE FROM CLIENT getMessageFromClient() !!!! \n");
						getMessageFromClient(socket_client, rtnMsg);
					    printf("&&&&&&   INCOMING MESSAGE  -->      %s \n", rtnMsg);



						// IF MESSAGE IS IP-ADDRESS...
						if(checkStrIsIp(rtnMsg)) {


					    	printf("	MESSAGE  ::  IP ADDRESS -->      %s \n", rtnMsg);

					    	// EXTRACTING IP ADRRESS AS AN INTEGER
					    	int* ipAddrIntList;
					    	ipAddrIntList = malloc(4 * sizeof(int));

							deComposeStringToInt(ipAddrIntList, rtnMsg, ".", 4);

							// FOR DEBUG
							// printf(" AFTER DE-COMPOSITION ::    ");
							// for(int i=0; i<4; i++) {
						 	// 		printf("%d | ", ipAddrIntList[i]);

						 	//  	}
							// printf("\n");

							//ipAddrIntList[3]



							// ----------------------------------
							// SENDING OK MESSAGE TO CLIENT !!
							char ipAddrRcvOK[32] = "SERVER_IPADDR_RECEIVED_OK";
							int ln = strlen(ipAddrRcvOK);

							ipAddrRcvOK[ln] = '\0';
							//printf("ln   -->      %d \n", ln);

							sendMessage(socket_client, ipAddrRcvOK, strlen(ipAddrRcvOK));


							// FLAGGING ON !!!!
							g_allDevsActive[ipAddrIntList[3]-1] = 1;
							


							// FOR DEBUG
							printf(" AFTER FLAGGING  ::  g_allDevsActive vvvvv   ");
							for(int z=0; z<9; z++) {
						 		printf("%d | ", g_allDevsActive[z]);

						 	}
							printf("\n");


							// ************************
							// FILE DESCRIPTOR CLEARED
							// ************************
							FD_CLR(socket_client, &g_master_fdset);

							shutdown(socket_client,0);
							close(socket_client);


						} else if(strcmp(rtnMsg, "CLIENT_REQUEST_SCENENUMBERS") == 0) {

							printf("SENDING SCENE NUMBER LIST TO CLIENT !!!!\n");
							printf("	MESSAGE  -->      %s \n", rtnMsg);



							// GETTING SCENE NUMBERS FROM HTTP SERVER !!!!
							http_linkedSubjects_result_t sceneNumberResult;
							sceneNumberResult = http_server_getLinkedSubjectsResult();

							// GETTING OTHER SCENE NUMBER
							int* linkedScenes = sceneNumberResult.linkedSubjects;
							int  linkedCount  = sceneNumberResult.linkedCount;


							// FOR DEBUG
							printf("PRINTING OUT linkedScenes  --vvv\n");
							for(int t=0; t < 9; t++) {
								printf(" | %d  ", linkedScenes[t]);
							}
							printf("\r\n");



							// RECEIVING DATA AND SEND BACK TO CLIENT
							//printf("linkedScenes  TEST  ...    %d  \n", linkedScenes[0]);

							if(linkedScenes[0] != 0) {

								printf("linkedScenes  TEST  ...    %d  \n", linkedScenes[0]);

								char* serializedData = serializeIntList( linkedScenes, linkedCount);
								//printf("      serializedData IS ---->       %s   \n", serializedData);


							    ESP_LOGI(TAG, "DATA WILL BE SENT TO   :  %s  ", g_addr_str);


							    //int written = send(sock, serializedData + (len - to_write), to_write, 0);
								int written = send( socket_client, serializedData, strlen(serializedData), 0 );

							    if (written < 0) {
							        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
							        
							    } else {

									ESP_LOGI(TAG, "SENT : len: %d", written);

							    }

								ESP_LOGI(TAG, "-- SENDING DATA ENDED --");

							} else {

								printf("linkedScenes IS  0 !!!! WE DO NOT SEND DATA TO CLIENT !!!!\n");

							}

							// ************************
							// FILE DESCRIPTOR CLEARED
							// ************************
							FD_CLR(socket_client, &g_master_fdset);
							shutdown(socket_client,0);
							close(socket_client);

						}




				    } 

				
				} else {

					//printf("THERE IS NO FILE DESCRIPTOR TO READING\n");

				}




			} else {

				printf("g_sockLoopGate IS CLOSED\n");
				printf("          SOCKET   i   IS   ->   %d\n", i);


			}





		}

    	vTaskDelay(1);
    	//vTaskDelay( 1000 / portTICK_PERIOD_MS);
	

    }


    shutdown(socket_client, 0);
    close(socket_client);



	CLEAN_UP:
	    close(g_listen_sock);
	    vTaskDelete(NULL);


}



// -----------------------------------
// < MAIN TASK FOR THIS APPLICATION >
// 
static void wifi_app_task(void *pvParameters) {

	// FOR ACTUAL MESSAGE USING WITH QUEUE
	wifi_app_queue_message_t msg;

	// FOR OUR EVENT GROUP 
	// :: THIS CAN BE USED IN OUR EVENT LOOP IN PROCESSING THE MESSAGES WE GOT 
	//    AND ADDITIONALLY THE EVENT BITS FROM EVENT GROUP
	//
	EventBits_t eventBits;



	// =======================================
	// < NETWORK + TRANSPORT LAYER SETTINGS >

	// INITIALIZING EVENT HANDLER FOR "WIFI AND IP EVENTS"
	wifi_app_event_handler_init();

	// Initialize the TCP/IP stack and WiFi config
	wifi_app_default_wifi_init();

	// SoftAP config
	wifi_app_soft_ap_config();





	// =======================================
	// < NETWORK + TRANSPORT LAYER STARTING >

	// Start WiFi
	ESP_ERROR_CHECK( esp_wifi_start() );

	// Send first event message
	wifi_app_send_message(WIFI_APP_MSG_LOAD_SAVED_CREDENTIALS);





	// -----------------------
	// MAIN LOOP FOR WIFI APP
	// FOR PROCESSING EVENTS
	//
	// SO THIS IS THE 'EVENT LOOP' FOR WIFI EVENTS OCCURED WITH THE PRE-DEFINED MESSAGES
	//
	for (;;) {

		// ----------------------------------------------------
		// < LOOP FOR WIFI APP + QUEUE >
		//
		//
		// 
		if ( xQueueReceive(wifi_app_queue_handle, &msg, portMAX_DELAY) ) {

			switch (msg.msgID) {

				// ------------------------------------------------
				// BEFORE STARTING HTTP SERVER, WE NEED CREDENTIALS
				case WIFI_APP_MSG_LOAD_SAVED_CREDENTIALS:
					ESP_LOGI(TAG, "WIFI_APP_MSG_LOAD_SAVED_CREDENTIALS");

					// WE WILL LOAD CREDENTIALS DATA FROM NON VOLITILE STORAGE 
					if (app_nvs_load_sta_creds()) {

						ESP_LOGI(TAG, "Loaded station configuration");

						// BECAUSE WE EXECUTED ABOVE FUNCTION app_nvs_load() FUNCTION 
						// WE CAN GET THE CRERENDTIAL INFORMATION FROM NVS
						// < WE ARE SIMPLY SHARING wifi_config_t *wifi_sta_config > 

						// WIFI CONNECTION AS STATION
						wifi_app_connect_sta();

						xEventGroupSetBits(wifi_app_event_group, WIFI_APP_CONNECTING_USING_SAVED_CREDS_BIT);

					} else {

						ESP_LOGI(TAG, "Unable to load station configuration");

					}

					// Next, start the web server
					wifi_app_send_message(WIFI_APP_MSG_START_HTTP_SERVER);

					break;


				// -----------------------------
				// STARTING HTTP SERVER HERE !!!
				case WIFI_APP_MSG_START_HTTP_SERVER:

					ESP_LOGI(TAG, "WIFI_APP_MSG_START_HTTP_SERVER");

					// STARTING HTTP SERVER
					// THIS WILL RUN http_server_configure() FUNCTION IN HTTP SERVER CODE
					// THEN "HANDLE OBJECT" TO CONTROL HTTP SERVER INSTANCE WILL BE OBTAINED !!!!
					http_server_start();


					// TODO :: LED INIDICATING ????
					//rgb_led_http_server_started();


					break;


				// -----------------------------------------------
				// ACTUAL INITIALIZATION TO CONNECT TO HTTP SERVER
				case WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER:

					ESP_LOGI(TAG, "WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER");

					// SETTING GROUP EVENT BIT 
					xEventGroupSetBits(wifi_app_event_group, WIFI_APP_CONNECTING_FROM_HTTP_SERVER_BIT);

					// TRY TO CONNECT TO ANOTHER AP
					// (STATION MODE)
					wifi_app_connect_sta();

					// Set current number of retries to zero
					g_retry_number = 0;

					// Let the HTTP server know about the connection attempt
					http_server_monitor_send_message(HTTP_MSG_WIFI_CONNECT_INIT);


					break;


				// ---------------------------------------------------------------------
				// EXECUTE BELOW WHEN ANY STATION IS CONNECTED AND GOT THEIR IP ADDRESS
				// 
				case WIFI_APP_MSG_STA_CONNECTED_GOT_IP:
					ESP_LOGI(TAG, "WIFI_APP_MSG_STA_CONNECTED_GOT_IP");

					xEventGroupSetBits(wifi_app_event_group, WIFI_APP_STA_CONNECTED_GOT_IP_BIT);

					//rgb_led_wifi_connected();

					// SEND MESSAGE TO THIS DEVICE'S HTTP SERVER PROGRAM
					// SO THIS TELLS "WIFI CONNECTION IS OK"
					http_server_monitor_send_message(HTTP_MSG_WIFI_CONNECT_SUCCESS);

					// GETTING THIS DEVICE'S EVENT GROUP BIT
					eventBits = xEventGroupGetBits(wifi_app_event_group);


					// THIS DEVICE'S WIFI APP SAVES CREDENTIALS 
					// WHEN THE HTTP SERVER PROGRAM IS CONNECTED WITH THIS DEVICE
					//
					// BUT AT THE WAY, NON-VOLITILE STORAGE ALSO CONNECTS TO WIFI APP,
					// WHEN WE "LOAD THE CREDENTIALS" FROM NVS
					// IT SEEMS THAT IS WHY THE BELOW COMMENTS CAME IN
					// |
					// Save STA creds only if connecting from the http server (not loaded from NVS)
					if (eventBits & WIFI_APP_CONNECTING_USING_SAVED_CREDS_BIT) {

						xEventGroupClearBits(wifi_app_event_group, WIFI_APP_CONNECTING_USING_SAVED_CREDS_BIT); ///> Clear the bits, in case we want to disconnect and reconnect, then start again
					
					} else {

						app_nvs_save_sta_creds();

					}

					if (eventBits & WIFI_APP_CONNECTING_FROM_HTTP_SERVER_BIT) {

						xEventGroupClearBits(wifi_app_event_group, WIFI_APP_CONNECTING_FROM_HTTP_SERVER_BIT);

					}


					// IF THERE IS CALLBACK FUNCTION DEFINED WHEN INITIALIZATION PHASE,
					// WE EXECUTE THAT
					//
					// Check for connection callback
					if (wifi_connected_event_cb) {

						wifi_app_call_callback();

					}

					break;


				// ----------------------------------
				// WHEN USER REQUESTED TO DISCONNECT
				case WIFI_APP_MSG_USER_REQUESTED_STA_DISCONNECT:
					ESP_LOGI(TAG, "WIFI_APP_MSG_USER_REQUESTED_STA_DISCONNECT");

					// GETTING CURRENT EVENT GROUP BITS
					eventBits = xEventGroupGetBits(wifi_app_event_group);

					// AND, IF THIS CASE IS "ONLINE" SITUATION WHICH THE STATION TRIED TO CONNECT WITH THIS WIFI-APP... 
					if (eventBits & WIFI_APP_STA_CONNECTED_GOT_IP_BIT) {

						// THEN, WE CAN TREAT THIS CASE AS
						// THE STATION WE'VE GOT REQUESTED DISCONNECTION
						xEventGroupSetBits(wifi_app_event_group, WIFI_APP_USER_REQUESTED_STA_DISCONNECT_BIT);

						// SO, CHANGE THE RETRY COUNT TO MAX, BECAUSE WE DO NOT WANT TO RE-CONNECTION ANYMORE,
						g_retry_number = MAX_CONNECTION_RETRIES;

						// THEN, JUST PLUG OFF THIS DEVICe'S WIFI-APP
						ESP_ERROR_CHECK(esp_wifi_disconnect());

						// THEN, NVS WILL DELETE THE CREDENTIAL RECORD
						app_nvs_clear_sta_creds();

						//rgb_led_http_server_started(); ///> todo: rename this status LED to a name more meaningful (to your liking)...
					}

					break;


				// -----------------------------
				// WHEN STATION IS DISCONNECTED
				case WIFI_APP_MSG_STA_DISCONNECTED:

					ESP_LOGI(TAG, "WIFI_APP_MSG_STA_DISCONNECTED");

					eventBits = xEventGroupGetBits(wifi_app_event_group);


					// < USING EVENT GROUP BITS >
					// USING THIS APP'S EVENT GROUP BITS, 
					// WE CAN SEPERATE THE CASE AND SWITCH THE PROCESS TO SEVERAL WAYS
					// WE NEED THESE ROUTING PROCESS BECAUSE WE WANT TO KNOW EXACT MOMENT TO GET PROPER INFORMATION 
					// WHEN WE DISCONNECTED OUR CONNECTION BETWEEN WIFI APP AND HTTP SERVER APP etc.


					// IF THE CASE IS WHEN WE CONNECT WITH CREDENTIAL INFORMATION FROM NVS
					// THEN WE NEED TO DISCONNECT...
					// WE NEED TO CLEAR CREDENTIAL INFORMATION FROM NVS
					if (eventBits & WIFI_APP_CONNECTING_USING_SAVED_CREDS_BIT) {

						ESP_LOGI(TAG, "WIFI_APP_MSG_STA_DISCONNECTED: ATTEMPT USING SAVED CREDENTIALS");
						xEventGroupClearBits(wifi_app_event_group, WIFI_APP_CONNECTING_USING_SAVED_CREDS_BIT);

						app_nvs_clear_sta_creds();


					// IF THE CASE IS WHEN WE ARE CONNECTING THIS WIFI-APP WITH HTTP SERVER PROGRAM
					// AND WE NEED TO DISCONNECT CURRENT WIFI CONNECTION,
					// THAT MEANS "WE COULD NOT CONNECT" WITH WIFI
					} else if (eventBits & WIFI_APP_CONNECTING_FROM_HTTP_SERVER_BIT) {

						ESP_LOGI(TAG, "WIFI_APP_MSG_STA_DISCONNECTED: ATTEMPT FROM THE HTTP SERVER");
						xEventGroupClearBits(wifi_app_event_group, WIFI_APP_CONNECTING_FROM_HTTP_SERVER_BIT);

						// SO SEND MESSAGE TO HTTP SERVER PROGRAM "WE FAILED TO CONNECT"
						http_server_monitor_send_message(HTTP_MSG_WIFI_CONNECT_FAIL);

					// OR, IF THE USER PUSHED BUTTON TO DISCONNECT CURRENT WIFI CONNECTION,
					// THAT CASE IS FROM THE USER 
					} else if (eventBits & WIFI_APP_USER_REQUESTED_STA_DISCONNECT_BIT) {


						ESP_LOGI(TAG, "WIFI_APP_MSG_STA_DISCONNECTED: USER REQUESTED DISCONNECTION");
						xEventGroupClearBits(wifi_app_event_group, WIFI_APP_USER_REQUESTED_STA_DISCONNECT_BIT);

						http_server_monitor_send_message(HTTP_MSG_WIFI_USER_DISCONNECT);

					} else {

						ESP_LOGI(TAG, "WIFI_APP_MSG_STA_DISCONNECTED: ATTEMPT FAILED, CHECK WIFI ACCESS POINT AVAILABILITY");
						// Adjust this case to your needs - maybe you want to keep trying to connect...
						
						
					}



					if (eventBits & WIFI_APP_STA_CONNECTED_GOT_IP_BIT) {

						xEventGroupClearBits(wifi_app_event_group, WIFI_APP_STA_CONNECTED_GOT_IP_BIT);

					}


					break;

				// --------------------------------------
				// WHEN WE WANT TO SCAN OTHER SSIDs !!!!
				case WIFI_APP_MSG_SCAN_SSID:


					ESP_LOGI(TAG, "WIFI_APP_MSG_SCAN_SSID: NOW WE WILL SCAN OTHER APS");

					//eventBits = xEventGroupGetBits(wifi_app_event_group);

					break;


				// -------------------------------------------
				// WHEN WE WANT TO NETWORK USING SOCKET !!

				// < LABEL AND DECLARATION PROBLEM >
				// https://stackoverflow.com/questions/18496282/why-do-i-get-a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a
				// The language standard simply doesn't allow for it. 
				// Labels can only be followed by statements, and declarations 
				// do not count as statements in C. The easiest way to get around 
				// this is by inserting an empty statement after your label, which 
				// relieves you from keeping track of the scope the way you would need 
				// to inside a block.


				case WIFI_APP_MSG_SOCKET_CONNECTION:       ;			// WE NEED TO ADD SEMI-COLON !
					ESP_LOGI(TAG, "====+++++++++   WIFI_APP_MSG_SOCKET_CONNECTION     +++++++++======");
					break;


				case WIFI_APP_MSG_SOCKET_COMMUNICATION:       ;			// WE NEED TO ADD SEMI-COLON !
					ESP_LOGI(TAG, "====+++++++++   WIFI_APP_MSG_SOCKET_COMMUNICATION     +++++++++======");
					
					// printf("BROADCASTING TO CLIENTS\n");


					// //g_allDevsActive







					// // g_sockLoopGate = false;


				 // //    FD_ZERO(&g_master_fdset);
				 // //    FD_SET(g_listen_sock, &g_master_fdset);
				 // //    g_max_socket = g_listen_sock;







					// // ----------------------------------
					// // SENDING OK MESSAGE TO CLIENT !!
					// char ipAddrRcvOK[64] = "CLIENT_BROADCAST_SHOULD_BE_REQUIRED";
					// int ln = strlen(ipAddrRcvOK);

					// ipAddrRcvOK[ln] = '\0';
					// printf("ln   -->      %d \n", ln);


					// // ----------------------------------

					// ESP_LOGI(TAG, "STARTING ONE TIME SOCKET FOR HTTP CLIENT...");

					// SOCKET oneTimeSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


					// struct sockaddr_in serverAddress;
					// serverAddress.sin_family = AF_INET;

					// // WE USED <<  WIFI_AP_GATEWAY  >> MACRO !!!!
					// // 
					// inet_pton(AF_INET, WIFI_AP_GATEWAY, &serverAddress.sin_addr.s_addr);
					// serverAddress.sin_port = htons(TCP_PORT);



					// //FD_SET(oneTimeSock, &g_master_fdset);



					// // CONNECTING TO SERVER
					// int rc = connect(oneTimeSock, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in));
					// if( rc == -1 ) {
					// 	printf(" &**&*  ERROR OCCURED !!  ::  rc:   %d\n", rc);	
					// } else {
					// 	printf("CONNECTED !!  ::  rc:   %d\n", rc);
					// }



					// sendMessage(oneTimeSock, ipAddrRcvOK, strlen(ipAddrRcvOK));



					// shutdown(oneTimeSock, 0);
					// close(oneTimeSock);


					// printf("oneTimeSock  IS SHUTDOWN AND CLOSED !!!! \n");













					// ------------------------------------------------------------------------------------

				  //   FD_ZERO(&g_master_fdset);
				  //   FD_SET(g_listen_sock, &g_master_fdset);
				  //   g_max_socket = g_listen_sock;



				  //   SOCKET socket_client;


				  //   while (1) {


				  //       fd_set readFd;
				  //       readFd = g_master_fdset;

						// printf("++++++++++++++   BLOCKED  <<  HTTP  >>  (SELECTING)  ++++++++++++++++\n");


				  //       if ( select(g_max_socket+1, &readFd, 0, 0, 0) < 0 ) {

				  //       	// IF SELECT FUNCTION IS FAILED ...
				  //           fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
				  //           break;
				  //       }

						// // WHEN SOME CLIENT IS << CONNECTED >> TO THIS, 
						// // THE PROCESS WILL GET THROUGH !!!!

						// printf("////   BLOCKING PURGED !!   <<  HTTP  >>  -- THEN WE NEED TO ACCEPT THE CLIENT TO EASTABLISH THE CONNECTION !!\n");
						// printf("       vvvvvvvvvvvvvvv\n");


				  //       SOCKET i;

				  //       // FOR EVERY SOCKETS ......
				  //       for(i = 1; i <= g_max_socket; ++i) {

				  //       	//printf("FILE DESC FOR-LOOP    ::  SOCKET  i  ::   %d   ,   g_max_socket  ::   %d \n", i, g_max_socket);

				  //       	// // ================================================
				  //       	// // SEMAPHORE CHECK !!!!
				  //       	// // ================================================

				  //       	// if( xSemaphoreTake ( g_xSemaphore, portMAX_DELAY) ) {

				  //       	// 	printf("-*-*-*-    GOT SEMAPHORE !   ==   WE CAN GET THROUGH !!!!  ==   %d    -*-**-*-*-- \n", xTaskGetTickCount());

				  //       	if( g_sockLoopGate == true ) {


					 //        	// ----------------------------------------------------------------------------
					 //        	// IF ANY FILE DESCRIPTOR IN FD SET IS READY FOR << READING >>
					 //        	// ----------------------------------------------------------------------------
					 //            if (FD_ISSET(i, &readFd)) {
					 //            	printf("< READING >  FILE DESC FOR-LOOP  <<  HTTP  >>      ::  SOCKET  i  ::   %d   OF   g_max_socket  ::   %d \n", i, g_max_socket);
					 //            	printf("< READING >                      <<  HTTP  >>          CHECKING CURRENT SOCKET || %d || IS READY OR NOT...\n", i);

					 //                if (i == g_listen_sock) {

						//             	printf("< READING >                        <<  HTTP  >>        SOCKET || %d || IS READY !!!!\n", i);
								        
								        
						// 		        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
						// 		        socklen_t addr_len = sizeof(source_addr);

						// 		        // ===================================================================================================
						// 		        // ACCEPTING CONNECTIONS
					     
						// 		        socket_client = accept(g_listen_sock, 
						// 		        					   (struct sockaddr *)&source_addr, 
						// 		        					   &addr_len);
						// 		   	    printf("< READING >                      <<  HTTP  >>          SOCKET || %d || IS ACCEPTED AND MADE IT CONNECTED !!!!\n", i);
								        
						// 		        if (socket_client < 0) {
						// 		            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
						// 		            break;
						// 		        }



						// 		        // ---------------------------------------------------------------------------------------------------
						// 		        // SETTING ACCEPTED SOCKET'S FD TO FD-SET
					 //                    FD_SET(socket_client, &g_master_fdset);

					 //                    // IF ACCEPTED SOCKET'S INDEX IS OVER THAN MAXIMUM
					 //               		// EXPAND MAXIMUM VALUE TO THAT NUMBER !!!!
					 //                    if (socket_client > g_max_socket) g_max_socket = socket_client;


						// 		        // ---------------------------------------------------------------------------------------------------
						// 		        // Set tcp keepalive option
						// 		        setsockopt(socket_client, SOL_SOCKET, SO_KEEPALIVE, &g_keepAlive, sizeof(int));
						// 		        setsockopt(socket_client, IPPROTO_TCP, TCP_KEEPIDLE, &g_keepIdle, sizeof(int));
						// 		        setsockopt(socket_client, IPPROTO_TCP, TCP_KEEPINTVL, &g_keepInterval, sizeof(int));
						// 		        setsockopt(socket_client, IPPROTO_TCP, TCP_KEEPCNT, &g_keepCount, sizeof(int));

						// 		        // Convert ip address to string
						// 		        if (source_addr.ss_family == PF_INET) {
						// 		            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, 
						// 				            	g_addr_str, 
						// 				            	sizeof(g_addr_str) - 1);
						// 		        }

						// 		        ESP_LOGI(TAG, "Socket accepted ip address: %s", g_addr_str);
						// 		        printf("CONNECTION EASTABLISHED !!!! \n");


						// 		        // GETTING DEVICE INDEX TO DECIDE 
						// 		        // WE SEND SCENE LIST TO OUT CLIENTS
						// 				char rtnMsg[128];

						// 				// GETTING IP ADDRESS FROM CLIENT
						// 				printf("GETTING MESSAGE FROM CLIENT getMessageFromClient() !!!! \n");
						// 				getMessageFromClient(socket_client, rtnMsg);
						// 			    printf("&&&&&&   INCOMING MESSAGE  -->      %s \n", rtnMsg);




						// 				// IF MESSAGE IS IP-ADDRESS...
						// 				if(checkStrIsIp(rtnMsg)) {


						// 			    	printf("	MESSAGE  ::  IP ADDRESS -->      %s \n", rtnMsg);

						// 			    	// EXTRACTING IP ADRRESS AS AN INTEGER
						// 			    	int* ipAddrIntList;
						// 			    	ipAddrIntList = malloc(4 * sizeof(int));

						// 					deComposeStringToInt(ipAddrIntList, rtnMsg, ".", 4);

						// 					// FOR DEBUG
						// 					// printf(" AFTER DE-COMPOSITION ::    ");
						// 					// for(int i=0; i<4; i++) {
						// 				 	// 		printf("%d | ", ipAddrIntList[i]);

						// 				 	//  	}
						// 					// printf("\n");

						// 					//ipAddrIntList[3]



						// 					// ----------------------------------
						// 					// SENDING OK MESSAGE TO CLIENT !!
						// 					char ipAddrRcvOK[32] = "SERVER_IPADDR_RECEIVED_OK";
						// 					int ln = strlen(ipAddrRcvOK);

						// 					ipAddrRcvOK[ln] = '\0';
						// 					//printf("ln   -->      %d \n", ln);

						// 					sendMessage(socket_client, ipAddrRcvOK, strlen(ipAddrRcvOK));


						// 					// FLAGGING ON !!!!
						// 					g_allDevsActive[ipAddrIntList[3]-1] = 1;
											


						// 					// FOR DEBUG
						// 					printf(" AFTER FLAGGING  ::  g_allDevsActive vvvvv   ");
						// 					for(int z=0; z<9; z++) {
						// 				 		printf("%d | ", g_allDevsActive[z]);

						// 				 	}
						// 					printf("\n");


						// 					// ************************
						// 					// FILE DESCRIPTOR CLEARED
						// 					// ************************
						// 					FD_CLR(socket_client, &g_master_fdset);


						// 				} 

						// 		    } 


								
						// 		} else {

						// 			//printf("THERE IS NO FILE DESCRIPTOR TO READING\n");

						// 		}



						// 	} else {

						// 		printf("g_sockLoopGate IS CLOSED\n");
						// 		printf("          SOCKET   i   IS   ->   %d\n", i);


						// 	}



						// }

				  //   	vTaskDelay( 1000 / portTICK_PERIOD_MS);
					

				  //   }













					// g_sockLoopGate = true;





					//int* activeSocks = getActiveDevs();





					// // // ----------------------------------
					// // // SENDING OK MESSAGE TO CLIENT !!
					// // char ipAddrRcvOK[33] = "CLIENT_REQUEST_SCENE_CHANGED_HTTP";
					// // int ln = strlen(ipAddrRcvOK);

					// // ipAddrRcvOK[ln] = '\0';
					// // //printf("ln   -->      %d \n", ln);


					// // // ----------------------------------

					// // ESP_LOGI(TAG, "STARTING ONE TIME SOCKET FOR HTTP CLIENT...");

					// // SOCKET oneTimeSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


					// // struct sockaddr_in serverAddress;
					// // serverAddress.sin_family = AF_INET;

					// // // WE USED <<  WIFI_AP_GATEWAY  >> MACRO !!!!
					// // // 
					// // inet_pton(AF_INET, WIFI_AP_GATEWAY, &serverAddress.sin_addr.s_addr);
					// // serverAddress.sin_port = htons(TCP_PORT);



					// // //FD_SET(oneTimeSock, &g_master_fdset);



					// // // CONNECTING TO SERVER
					// // int rc = connect(oneTimeSock, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in));
					// // if( rc == -1 ) {
					// // 	printf(" &**&*  ERROR OCCURED !!  ::  rc:   %d\n", rc);	
					// // } else {
					// // 	printf("CONNECTED !!  ::  rc:   %d\n", rc);
					// // }



					// // sendMessage(oneTimeSock, ipAddrRcvOK, strlen(ipAddrRcvOK));



					// // shutdown(oneTimeSock, 0);
					// // close(oneTimeSock);


					// // printf("oneTimeSock  IS SHUTDOWN AND CLOSED !!!! \n");




					break;


				case WIFI_APP_MSG_SOCKET_DISCONNECTION:       ;
					ESP_LOGI(TAG, "====+++++++++   WIFI_APP_MSG_SOCKET_DISCONNECTION     +++++++++======");
					break;

				default:
					break;

			}

		}

	}

}

// FOR SENDING MESSAGE TO WIFI-QUEUE
BaseType_t wifi_app_send_message(wifi_app_message_e msgID) {

	wifi_app_queue_message_t msg;
	msg.msgID = msgID;

	return xQueueSend(wifi_app_queue_handle, &msg, portMAX_DELAY);

}

// GETTER FUNCTION TO GET THE WIFI-SETTINGS
wifi_config_t* wifi_app_get_wifi_config(void) {

	return wifi_config;

}

// SETTING CALLBACK FUNCTION
void wifi_app_set_callback(wifi_connected_event_callback_t cb) {

	wifi_connected_event_cb = cb;

}

// CALLING CALLBACK FUNCTION
void wifi_app_call_callback(void) {

	wifi_connected_event_cb();

}

int wifi_get_Unit_Number(void) {


	int result = 0;

	// < TOKENIZE STRING WITH DELIMITER >
	// https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split

	char currentSSID[] = WIFI_AP_SSID;
	//printf(" -_-  CURRENT MODULE'S SSID IS   =   %s  \r\n", currentSSID);

	char delimiter[] = "_";
	
	// FIRST TIME WE TOKENIZE
	char* ptr = strtok(currentSSID, delimiter);
	

	// AFTER THE FIRST TIME, 
	// WE SHOULD PASS NULL TO strtok() FUNCTION

	while(ptr != NULL) {
		//printf("      ptr IS ---->       '%s'\n", ptr);

		int chk = atoi(ptr);
		if(chk != 0) {
			result = chk;
			//printf("      result IS ---->       %d\n", result);	
		} 
		
		// TOKENIZE AGAIN
		ptr = strtok(NULL, delimiter);

	}

	// --------------------------------
	// ABOVE WILL PRINT OUT LIKE BELOWS
	//
	// -_-  CURRENT MODULE'S SSID IS   =   ESP32_AP_1  
	//      ptr IS ---->       'ESP32'
	//      ptr IS ---->       'AP'
	//      ptr IS ---->       '1'
	//      result IS ---->       1


	return result;

}

// < DELETING ELEMENT FROM ARRAY >
// https://www.javatpoint.com/remove-an-element-from-an-array-in-c#:~:text=In%20C%20programming%2C%20an%20array,the%20size%20of%20an%20array.
//
// :: RETURN
//    POINTER TO THE INTEGER LIST
//
int* wifi_get_Ex_Unit_Numbers(int mainUnitNum) {
	// INPUT : 1 ~ 10

	// ----------------------------
	// < STATIC LOCAL VARIABLE ! >
	// :: C DOES NOT ALLOW TO RETURN LOCAL VARIABLE TO OUTSIDE OF THIS SCOPE !!!!
	//    ARRAY NEITHER ! 
	//
	//    SO, USE THE STATIC AND POINTER TYPE !!!!
	static int excludedList[9];


	int original[10] = {1,2,3,4,5,6,7,8,9,10};
	//                  0 1 2 3 4 5 6 7 8 9
	//                      ^

	for(int i=0; i < 10; i++) {
		// IF i -> 2


		// EXCLUDING FROM original ARRAY

		// 1. SEARCHING FIRST
		// 3. IF MATCHED...
		if( mainUnitNum == original[i] ) {

			// 4. DELETE THAT ONE AND THEN CONSTRUCT REST OF THE (EXCLUDED) LIST
			int restInd = 10 - i;
			//  IF,
			//  MATCHED  2  ->  restInd SHOULD BE 8   LAST INDEX ->  
			//           3  ->  restInd SHOULE BE 7
			//           4  ->  restInd SHOULE BE 6
			//           5  ->  restInd SHOULE BE 5
			//           6  ->  restInd SHOULE BE 4
			//           7  ->  restInd SHOULE BE 3
			//           8  ->  restInd SHOULE BE 2
			//           9  ->  restInd SHOULE BE 1


			// i  ->  2
			//      0             8  						// RANGE 
			for(int t = 0; t < restInd; t++) {	
				//         0             
				//         1             
				//         2             
				//         3             
				//         4             
				//         5             
				//         6             
				//         7

				//                          << NEXT ELEMENT
				excludedList[t+i] = original[t+i+1];


			}
			
			break;

		} else {
			// 2. OR NOT MATCHED...
			//    --> JUST STORE THE SAME ELEMENT
			excludedList[i] = original[i];

		}

	}

	//printf(" vvvv EXCLUDED UNIT NUMBER LIST   ::   \r\n");
	for(int i=0; i < 9; i++) {	
		//printf(" | %d | ", excludedList[i]);
	}
	//printf("\r\n");


	return excludedList;

}

// < CHECKING INPUT IS DIGIT OR NOT >
// https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
bool digit_check(char key[]) {

    for(int i = 0; i < strlen(key); i++) {

        if(isdigit(key[i])==0) {
            return false;
        }
    }

    return true;

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


	ESP_LOGI(TAG, "||||  STARTING WIFI APPLICATION  ||||");


	// --------------------------------------------
	// INITIALIZING GLOBAL SOCKET CONNECTION STRUCT
	//createAllSocketStructs();



	// LED LIGHTING FOR INDICATING STATUS OF WIFI CONECTION
	// Start WiFi started LED
	// rgb_led_wifi_app_started();


	// Disable default WiFi logging messages
	esp_log_level_set("wifi", ESP_LOG_NONE);




	// =====================================================
	// < FOR WIFI CONNECTION >



	// ----------------------------
	// < WIFI CONNECTION >
	// Allocate memory for the wifi configuration

	wifi_config = (wifi_config_t*) malloc( sizeof(wifi_config_t) );
	memset(wifi_config, 0x00, sizeof( wifi_config_t ));
	ESP_LOGI(TAG, "1. (FOR HTTP SERVER) INITIALZING WIFI CONFIG STRUCT...");
	ESP_LOGI(TAG, "                     SIZE OF WIFI CONFIG IS ->   %d", sizeof(wifi_config_t) );


	// =====================================================
	// < FOR DATA HANDLING IN WIFI APP >



	// -----------------------------------------------
	// < HANDLE OF QUEUE FOR STORING EVENT MESSAGES >
	// : THIS QUEUE WILL BE FILLED WITH EVENT MESSAGES USING EVENTGROUP FUNCTIONALITIES OF FREERTOS
	// 
	// Create message queue
	// < STATIC STRUCT >


	wifi_app_queue_handle = xQueueCreate(3, sizeof(wifi_app_queue_message_t));
	ESP_LOGI(TAG, "2. INITIALZING < QUEUE >USING IN THIS WIFI APP...");
	ESP_LOGI(TAG, "   SIZE OF wifi_app_queue_handle IS ->   %d", sizeof(wifi_app_queue_handle) );



    // ----------------------------
	// < EVENT GROUP IN FREERTOS >
 	// https://www.freertos.org/FreeRTOS-Event-Groups.html 
 	// : Event bits are used to indicate if an event has occurred or not. 
 	//   Event bits are often referred to as event flags. 
 	//
 	//   EXAMPLE CASE >  
 	//   Define a bit (or flag) that means "A message has been received and is 
 	//   ready for processing" when it is set to 1, and "there are no messages 
 	//   waiting to be processed" when it is set to 0.
 	//
 	//
 	//
	// Create Wifi application event group
	// https://www.freertos.org/xEventGroupCreate.html
	// 
	//

	wifi_app_event_group = xEventGroupCreate();
	ESP_LOGI(TAG, "3. INITIALZING < EVENT GROUP > IN THIS WIFI APP...");
	ESP_LOGI(TAG, "   SIZE OF wifi_app_event_group IS ->   %d", sizeof(wifi_app_event_group) );




	// =====================================================
	// < FOR EVENT HANDLING IN OUR APPLICATION >


	g_xSemaphore = xSemaphoreCreateBinary();


	// Start the WiFi application task

	ESP_LOGI(TAG, "4. RUNNING TASK FOR THIS WIFI APP...");
	xTaskCreatePinnedToCore(&wifi_app_task, "wifi_app_task", WIFI_APP_TASK_STACK_SIZE, NULL, WIFI_APP_TASK_PRIORITY, &g_taskHandle_wifi, WIFI_APP_TASK_CORE_ID);



	ESP_LOGI(TAG, "5. RUNNING TASK FOR SOCKET ...");
	//xTaskCreatePinnedToCore(&wifi_sock_task, "wifi_sock_task", WIFI_APP_TASK_STACK_SIZE, NULL, WIFI_APP_TASK_PRIORITY, NULL, WIFI_APP_TASK_CORE_ID);

	xTaskCreate(wifi_sock_task, "wifi_sock_task", 8096, (void*)AF_INET, 5, &g_taskHandle_sock);

}





