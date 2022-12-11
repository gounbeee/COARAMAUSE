
// FORKED BY GOUNBEEE IN 2022
// SO THIS IS A SERVER PROGRAM USING HTTP.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_wifi.h"
#include "sys/param.h"

//#include "DHT22.h"
#include "http_server.h"
//#include "sntp_time_sync.h"
#include "tasks_common.h"
#include "wifi_app.h"
#include "uart_master_wifi.h"
#include "rama_mathlink_db.h"



// ------------------------------------------------------
// Max HTTP URI Length IS IMPORTANT !!!!
// https://github.com/tonyp7/esp32-wifi-manager/issues/127
// :: THERE WAS AN ERROR BECAUSE OF LONG URI LENGTH
//    set idf.py menuconfig > Component config > HTTP Server > Max HTTP URI Length to 1024


// ------------------------------------------------------
// < SCREEN PROGRAM FOR MONITORING SERIAL COMMUNICATION >
// https://geekinc.ca/using-screen-as-a-serial-terminal-on-mac-os-x/




// ------------------------------------------------------
// < SCANNING SSID >
// https://github.com/LetsControltheController/wifi-scan/blob/master/main/main.c
// static void http_server_scan_ssid() {

// 	// configure and run the scan process in blocking mode
// 	wifi_scan_config_t scan_config = {
// 		.ssid = 0,
// 		.bssid = 0,
// 		.channel = 0,
// 	    .show_hidden = true
// 	};


// 	printf("Start scanning...");


// 	// ----------------
// 	// ERROR OCCURED !!
// 	//
// 	// ESP_ERROR_CHECK failed: esp_err_t 0xffffffff (ESP_FAIL) at 0x40089278
// 	// file: "./main/http_server.c" line 111
// 	// func: http_server_scan_ssid
// 	// expression: esp_wifi_scan_start(&scan_config, true)


// 	ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

// 	printf(" completed!\n");


// 	// get the list of APs found in the last scan
// 	uint16_t ap_num;
// 	wifi_ap_record_t ap_records[20];

//     ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_num));

// 	ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_num, ap_records));


// 	// print the list 
// 	printf("Found %d access points:\n", ap_num);

// 	printf("               SSID              | Channel | RSSI |   MAC \n\n");
// 	//printf("----------------------------------------------------------------\n");

// 	for(int i = 0; i < ap_num; i++) {
	
// 		printf("%32s | %7d | %4d   %2x:%2x:%2x:%2x:%2x:%2x   \n", 
// 			ap_records[i].ssid, 
// 			ap_records[i].primary, 
// 			ap_records[i].rssi , 
// 			*ap_records[i].bssid, 
// 			*(ap_records[i].bssid+1), 
// 			*(ap_records[i].bssid+2), 
// 			*(ap_records[i].bssid+3), 
// 			*(ap_records[i].bssid+4), 
// 			*(ap_records[i].bssid+5));
// 	}

// 	//  printf("----------------------------------------------------------------\n");   

// }






// Tag used for ESP serial console messages
static const char TAG[] = "http_server";

// Wifi connect status
static int g_wifi_connect_status = NONE;


// CURRENT SUBJECT NUMBER (1) AND LINKED SUBJECT NUMBERS (9)  
//
// < INITIALIZING STATIC ARRAY IN C LANGUAGE >
// https://www.codegrepper.com/code-examples/c/initialize+empty+int+array+c
// 
//static int g_http_subjectLinked_result[RAMA_OTHERUNITS_MAX_IN_SINGLELINK + 1];


static http_linkedSubjects_result_t g_http_linkedSubjects_result;




// HTTP server task handle
static httpd_handle_t http_server_handle = NULL;

// HTTP server monitor task handle
static TaskHandle_t task_http_server_monitor = NULL;

// Queue handle used to manipulate the main queue of events
static QueueHandle_t http_server_monitor_queue_handle;



// /**
//  * ESP32 timer configuration passed to esp_timer_create.
//  */
// const esp_timer_create_args_t fw_update_reset_args = {
// 		.callback = &http_server_fw_update_reset_callback,
// 		.arg = NULL,
// 		.dispatch_method = ESP_TIMER_TASK,
// 		.name = "fw_update_reset"
// };
// esp_timer_handle_t fw_update_reset;




// Embedded files: JQuery, index.html, app.css, app.js and favicon.ico files
extern const uint8_t jquery_3_3_1_min_js_start[]	asm("_binary_jquery_3_3_1_min_js_start");
extern const uint8_t jquery_3_3_1_min_js_end[]		asm("_binary_jquery_3_3_1_min_js_end");
extern const uint8_t index_html_start[]				asm("_binary_index_html_start");
extern const uint8_t index_html_end[]				asm("_binary_index_html_end");
extern const uint8_t app_css_start[]				asm("_binary_app_css_start");
extern const uint8_t app_css_end[]					asm("_binary_app_css_end");
extern const uint8_t app_js_start[]					asm("_binary_app_js_start");
extern const uint8_t app_js_end[]					asm("_binary_app_js_end");
extern const uint8_t favicon_ico_start[]			asm("_binary_favicon_ico_start");
extern const uint8_t favicon_ico_end[]				asm("_binary_favicon_ico_end");









// HTTP server monitor task used to track events of the HTTP server
// pvParameters parameter which can be passed to the task.
//
// < UPDATING STATUS OF WIFI CONNECTION >
// : BASICALLY IN THIS FUNCTION, WE GET MESSAGE AND SET PROPER STATUS
//
//   MESSAGE IS TYPE 'http_server_queue_message_t'
// 
static void http_server_monitor(void *parameter) {

	http_server_queue_message_t msg;

	// SETTING STATUS WITH MESSAGES WE GET
	for (;;) {


		// USING MESSAGE FROM QUEUE FOR MONITORING SERVER
		if ( xQueueReceive(http_server_monitor_queue_handle, &msg, portMAX_DELAY) ) {

			// < MESSAGES WE DEFINED >
			// 
			// HTTP_MSG_WIFI_CONNECT_INIT = 0,
			// HTTP_MSG_WIFI_CONNECT_SUCCESS,
			// HTTP_MSG_WIFI_CONNECT_FAIL,
			// HTTP_MSG_WIFI_USER_DISCONNECT,
			// HTTP_MSG_OTA_UPDATE_SUCCESSFUL,
			// HTTP_MSG_OTA_UPDATE_FAILED,
			// HTTP_MSG_TIME_SERVICE_INITIALIZED,
			//
			switch (msg.msgID) {


				case HTTP_MSG_WIFI_CONNECT_INIT:
					ESP_LOGI(TAG, "HTTP_MSG_WIFI_CONNECT_INIT");
					
					// SETTING STATUS VALUE TO GLOBAL VARIABLE
					g_wifi_connect_status = HTTP_WIFI_STATUS_CONNECTING;

					break;

				case HTTP_MSG_WIFI_CONNECT_SUCCESS:
					ESP_LOGI(TAG, "HTTP_MSG_WIFI_CONNECT_SUCCESS");

					// SETTING STATUS VALUE TO GLOBAL VARIABLE
					g_wifi_connect_status = HTTP_WIFI_STATUS_CONNECT_SUCCESS;

					break;

				case HTTP_MSG_WIFI_CONNECT_FAIL:
					ESP_LOGI(TAG, "HTTP_MSG_WIFI_CONNECT_FAIL");

					// SETTING STATUS VALUE TO GLOBAL VARIABLE
					g_wifi_connect_status = HTTP_WIFI_STATUS_CONNECT_FAILED;

					break;

				case HTTP_MSG_WIFI_USER_DISCONNECT:
					ESP_LOGI(TAG, "HTTP_MSG_WIFI_USER_DISCONNECT");

					// SETTING STATUS VALUE TO GLOBAL VARIABLE
					g_wifi_connect_status = HTTP_WIFI_STATUS_DISCONNECTED;

					break;

				default:
					break;
					
			}
		}
	}
}



/**
 * Jquery get handler is requested when accessing the web page.
 * @param req HTTP request for which the uri needs to be handled.
 * @return ESP_OK
 */

static esp_err_t http_server_jquery_handler(httpd_req_t *req) {

	ESP_LOGI(TAG, "Jquery requested");

	httpd_resp_set_type(req, "application/javascript");
	httpd_resp_send(req, (const char *)jquery_3_3_1_min_js_start, jquery_3_3_1_min_js_end - jquery_3_3_1_min_js_start);

	return ESP_OK;


}


// --------------------------------
// < SENDING index.html HTML FILE >
// HERE, WE SEND index.html TO URI'S REQUEST

/**
 * Sends the index.html page.
 * @param req HTTP request for which the uri needs to be handled.
 * @return ESP_OK
 */
static esp_err_t http_server_index_html_handler(httpd_req_t *req) {

	ESP_LOGI(TAG, "index.html requested");

	httpd_resp_set_type(req, "text/html");
	httpd_resp_send(req, (const char *)index_html_start, index_html_end - index_html_start);

	return ESP_OK;

}





/**
 * app.css get handler is requested when accessing the web page.
 * @param req HTTP request for which the uri needs to be handled.
 * @return ESP_OK
 */
static esp_err_t http_server_app_css_handler(httpd_req_t *req) {

	ESP_LOGI(TAG, "app.css requested");

	httpd_resp_set_type(req, "text/css");
	httpd_resp_send(req, (const char *)app_css_start, app_css_end - app_css_start);

	return ESP_OK;

}




/**
 * app.js get handler is requested when accessing the web page.
 * @param req HTTP request for which the uri needs to be handled.
 * @return ESP_OK
 */
static esp_err_t http_server_app_js_handler(httpd_req_t *req) {

	ESP_LOGI(TAG, "app.js requested");

	httpd_resp_set_type(req, "application/javascript");
	httpd_resp_send(req, (const char *)app_js_start, app_js_end - app_js_start);

	return ESP_OK;

}




/**
 * Sends the .ico (icon) file when accessing the web page.
 * @param req HTTP request for which the uri needs to be handled.
 * @return ESP_OK
 */
static esp_err_t http_server_favicon_ico_handler(httpd_req_t *req) {

	ESP_LOGI(TAG, "favicon.ico requested");

	httpd_resp_set_type(req, "image/x-icon");
	httpd_resp_send(req, (const char *)favicon_ico_start, favicon_ico_end - favicon_ico_start);

	return ESP_OK;
	
}



// < HANDLER FUNCTION FOR DISPLAYING NEW SCENE >
static esp_err_t http_server_displayScene_handler(httpd_req_t *req) {

	ESP_LOGI(TAG, "REQUESTED FROM CLIENT (WEB BROWSER) :: DISPLAYING SCENE");



	// WE ALLOW FOR THE SCENE NUMBER FOR 3-DIGITS
	// 1~999
    char content[SCENENUM_DIGIT_MAX];


    // < MAXIMUM LENGTH CHECK >
    // Truncate if content length larger than the buffer
    size_t recv_size = MIN(req->content_len, sizeof(content));



    // < RECEIVING DATA FROM REQUEST (POST) >
    //
    int ret = httpd_req_recv(req, content, recv_size);


    //printf(" ==       %d  IS RETURNED\r\n", ret);
	//printf(" ==       %s  IS THE CONTENT WE RECEIVED\r\n", content);
	//printf(" ==       %d  IS THE SIZE OF THE CONTENT\r\n", recv_size);


 	// 0 return value indicates connection closed
    if (ret <= 0) {  
        // Check if timeout occurred
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            

            // In case of timeout one can choose to retry calling
            // httpd_req_recv(), but to keep it simple, here we
            // respond with an HTTP 408 (Request Timeout) error

            httpd_resp_send_408(req);

        }

        // In case of error, returning ESP_FAIL will
        // ensure that the underlying socket is closed 
        return ESP_FAIL;
    }


	// TRIMMING UNUSED DIGITS
	content[recv_size] = '\0';


    printf("HTTP-SERVER :: BEFORE SENDING SCENE NUMBER -- TRIMMED content IS    %s   ! \r\n" , content );


	// ---------------------------------	
    // GETTING MY SSID AND UNIT'S NUMBER
    int unitNumber = wifi_get_Unit_Number();
    printf("HTTP-SERVER ::  UNIT NUMBER FROM SSID IS    %d   ! \r\n" , unitNumber );


    // ---------------------------------------------
    // < CONSTRUNCTING EXCLUDED UNIT'S INDEX ARRAY >
    int* excludedUnitNumList = wifi_get_Ex_Unit_Numbers(unitNumber);



	printf(" HTTP-SERVER ::  vvvv EXCLUDED UNIT NUMBER LIST   ::   \r\n");
	for(int i=0; i < 9; i++) {	
		printf(" | %d | ", excludedUnitNumList[i]);
	}
	printf("\r\n");



    // -------------------------------------------------
    // < CONSTRUCTING DISPLAY NUMBER AND UNIT'S NUMBER >

    // FROM NOW WE GOT THE SUBJECT NAME TO DISPLAY THE ANIMATION
    // NOW, 
    // WE NEED TO DO BELOW THINGS


    // ----------------------------------------------------------
    // 1. PLAY THE SUBJECT'S ANIMATION ON OUR OWN UNIT'S DISPLAY
    uart_wifi_SetSceneNumber(content);


    // ------------------------------------------------------------
    // 2. GETTING LINKED ANIMATION SCENE FROM INFORMATION DATABASE
	// +    
    // 3. CONTRUCTING "PLAY CHART" BY MAPPING THE UNIT'S INDEX AND ANIMATION SCENE NUMBER
    int contentInt = atoi(content) - 1;
    printf("contentInt  :::  %d \r\n", contentInt);

    // SETTING UP "FIRST ELEMENT" OF GLOBAL LINKED SUBJECTS DATA 
    g_http_linkedSubjects_result.unitNumber = contentInt;
    g_http_linkedSubjects_result.linkedCount = OTHERUNITS_MAX_IN_SINGLELINK;
    

    // SETTING OTHER SCENE NUMBERS
    // SETTING UP "REST ELEMENT" OF GLOBAL LINKED SUBJECTS DATA 
	for(int t=0; t < OTHERUNITS_MAX_IN_SINGLELINK; t++) {
		g_http_linkedSubjects_result.linkedSubjects[t] = g_rama_allMathRelations[contentInt][t];
		printf(" | %d | ", g_http_linkedSubjects_result.linkedSubjects[t] );
	}
	printf("\r\n");


	// ----------------------------
	// ABOVE WILL PRINT LIKE BELOW
	// contentInt  :::  2 
 	// | 3 |  | 4 |  | 5 |  | 6 |  | 7 |  | 8 |  | 9 |  | 10 |  | 11 | 



    // --------------------------------
    // 4. SENDING MESSAGE TO WIFI-APP

	// --------------------------------
	// WHEN SOME STATION IS CONNECTED,
	// TAKE ATTEMPT TO EASTABLISH SOCKET COMMUNICATIION



	wifi_app_send_message(WIFI_APP_MSG_SOCKET_COMMUNICATION);





    // SENDING RESPONSE TO WEB BROWSER
    const char resp[] = "URI POST Response";
    httpd_resp_set_type(req, "‘text/html");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);


    return ESP_OK;

}







/**
 * apSSID.json handler responds by sending the AP SSID.
 * @param req HTTP request for which the uri needs to be handled.
 * @return ESP_OK
 */
static esp_err_t http_server_get_ap_ssid_json_handler(httpd_req_t *req) {
	ESP_LOGI(TAG, "/apSSID.json requested");

	char ssidJSON[50];

	wifi_config_t *wifi_config = wifi_app_get_wifi_config();
	esp_wifi_get_config(ESP_IF_WIFI_AP, wifi_config);
	char *ssid = (char*)wifi_config->ap.ssid;

	// CREATING JSON TEXT DATA !!
	sprintf(ssidJSON, "{\"ssid\":\"%s\"}", ssid);

	httpd_resp_set_type(req, "application/json");
	httpd_resp_send(req, ssidJSON, strlen(ssidJSON));

	return ESP_OK;
	
}









// -----------------------------------------------------------------------
// < CONFIGURE HTTP SERVER FOR STARTING >


/**
 * Sets up the default httpd server configuration.
 * @return http server instance handle if successful, NULL otherwise.
 */
static httpd_handle_t http_server_configure(void) {


	// Generate the default configuration
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();


	// Create HTTP server monitor task
	xTaskCreatePinnedToCore(&http_server_monitor, "http_server_monitor", HTTP_SERVER_MONITOR_STACK_SIZE, NULL, HTTP_SERVER_MONITOR_PRIORITY, &task_http_server_monitor, HTTP_SERVER_MONITOR_CORE_ID);


	// Create the message queue
	
	// TODO :: 3 MESSAGES IS ENOUGH ???

	http_server_monitor_queue_handle = xQueueCreate(3, sizeof(http_server_queue_message_t));


	// The core that the HTTP server will run on
	config.core_id = HTTP_SERVER_TASK_CORE_ID;


	// Adjust the default priority to 1 less than the wifi application task
	config.task_priority = HTTP_SERVER_TASK_PRIORITY;


	// Bump up the stack size (default is 4096)
	config.stack_size = HTTP_SERVER_TASK_STACK_SIZE;


	// Increase uri handlers
	config.max_uri_handlers = 20;

	// Increase the timeout limits
	// DEFAULT VALUE WAS 10
	config.recv_wait_timeout = 10;
	config.send_wait_timeout = 10;


	ESP_LOGI(TAG,
			"http_server_configure: Starting server on port: '%d' with task priority: '%d'",
			config.server_port,
			config.task_priority);



	
	// STARTING THE HTTPD SERVER
	// 
	if ( httpd_start(&http_server_handle, &config) == ESP_OK ) {

		ESP_LOGI(TAG, "http_server_configure: Registering URI handlers");


		// ----------------------------------------------------------------------------
		// < ACTUALLY, BELOWS ARE REGISTRATION OF CONTROLLER FUNCTIONS IN MVC MODEL ! >
		// ----------------------------------------------------------------------------


		// ------------------------------------------
		// < DEFINING URI STRUCTURES >
		//
		// register Jquery handler
		// 
		// DEFINING URI STRUCTURE (FOR JQUERY FILE)
		httpd_uri_t jquery_js = {
				.uri = "/jquery-3.3.1.min.js",					// URI ROUTING
				.method = HTTP_GET,								// REQUEST METHOD
				.handler = http_server_jquery_handler,			// HANDLER FUNCTION (CONTROLLER IN MVC)
																// WHEN ABOVE URI IS ACCESED, WE CALL THIS HANDLER FUNCTION
				.user_ctx = NULL
		};

		// < httpd_register_uri_handler FUNCTION >
		// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/protocols/esp_http_server.html#_CPPv426httpd_register_uri_handler14httpd_handle_tPK11httpd_uri_t
		// : Registers a URI handler.
		//
		// < REGISTER ABOVE SETUP >
		httpd_register_uri_handler(http_server_handle, &jquery_js);




		// ------------------------------------------
		// < REGISTERING HANDLER FUNCTION FOR GETTING index.html FILE > 
		// 
		// register index.html handler
		httpd_uri_t index_html = {
				.uri = "/",										// URI ROUTING
				.method = HTTP_GET,								// METHOD OF REQUEST
				.handler = http_server_index_html_handler,		// HANDLER FUNCTION (CONTROLLER IN MVC)
				.user_ctx = NULL
		};
		httpd_register_uri_handler(http_server_handle, &index_html);



		// register app.css handler
		httpd_uri_t app_css = {
				.uri = "/app.css",
				.method = HTTP_GET,
				.handler = http_server_app_css_handler,
				.user_ctx = NULL
		};
		httpd_register_uri_handler(http_server_handle, &app_css);


		// register app.js handler
		httpd_uri_t app_js = {
				.uri = "/app.js",
				.method = HTTP_GET,
				.handler = http_server_app_js_handler,
				.user_ctx = NULL
		};
		httpd_register_uri_handler(http_server_handle, &app_js);


		// register favicon.ico handler
		httpd_uri_t favicon_ico = {
				.uri = "/favicon.ico",
				.method = HTTP_GET,
				.handler = http_server_favicon_ico_handler,
				.user_ctx = NULL
		};
		httpd_register_uri_handler(http_server_handle, &favicon_ico);


		// < REGISTER DISPLAY SCENE HANDLER WITH WEB BROWSER >
		httpd_uri_t displayScene = {
				.uri = "/displayScene",
				.method = HTTP_POST,
				.handler = http_server_displayScene_handler,
				.user_ctx = NULL
		};
		httpd_register_uri_handler(http_server_handle, &displayScene);


		// register apSSID.json handler
		httpd_uri_t ap_ssid_json = {
				.uri = "/apSSID.json",
				.method = HTTP_GET,
				.handler = http_server_get_ap_ssid_json_handler,
				.user_ctx = NULL
		};
		httpd_register_uri_handler(http_server_handle, &ap_ssid_json);


		// // < REGISTER HANDLER TO BROADCAST SCENE HANDLER >
		// httpd_uri_t get_sceneNumber = {
		// 		.uri = "/get_scene",
		// 		.method = HTTP_GET,
		// 		.handler = http_server_get_scene_handler,
		// 		.user_ctx = NULL
		// };
		// httpd_register_uri_handler(http_server_handle, &get_sceneNumber);



		return http_server_handle;



	}

	return NULL;

}



// ----------------------------
// < STARTING HTTP SERVER >
// : STARTING SERVER FUNCTION SIMPLY RUN ABOVE FUNCTION
// 
void http_server_start(void) {

	if (http_server_handle == NULL) {

		// ------------------------------------
		// SETUP HTTP SERVER AND GETTING HANDLE
		http_server_handle = http_server_configure();


		// ---------------------------------
		// PRINTING g_rama_allMathRelations

		// for( int i=0; i < RAMA_ALL_MATHLINSKS_MAX; i++) {

		// 	printf("   --- +++  DATABASE... SUBJECT NO.  %i   ::  ", i );

		// 	for(int t=0; t < 9; t++) {
		// 		printf(" | %i | ", g_rama_allMathRelations[i][t] );
		// 	}
		// 	printf("\r\n");
		// }



	}

}


// STOP HTTPS SERVER
void http_server_stop(void) {

	if (http_server_handle) {

		httpd_stop(http_server_handle);
		ESP_LOGI(TAG, "http_server_stop: stopping HTTP server");
		http_server_handle = NULL;

	}

	if (task_http_server_monitor) {

		vTaskDelete(task_http_server_monitor);
		ESP_LOGI(TAG, "http_server_stop: stopping HTTP server monitor");
		task_http_server_monitor = NULL;

	}

}



// SENDING MESSAGE TO QUEUE WHICH MONITORS HTTP SERVER
BaseType_t http_server_monitor_send_message(http_server_message_e msgID) {


	http_server_queue_message_t msg;
	msg.msgID = msgID;


	return xQueueSend(http_server_monitor_queue_handle, &msg, portMAX_DELAY);

}





http_linkedSubjects_result_t http_server_getLinkedSubjectsResult() {


	return g_http_linkedSubjects_result;


}



