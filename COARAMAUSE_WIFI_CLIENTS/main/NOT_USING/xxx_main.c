// < WIFI MODULE >
// by gounbeee 2022
//
//



// <LOWER BAUD RATE NEEDED>
// https://docs.espressif.com/projects/esptool/en/latest/esp32/esptool/basic-options.html#:~:text=The%20default%20esptool%20baud%20rate%20is%20115200bps.
// :: WE NEEDED TO LOWER BAUD RATE IN MAC MINI ENVIRONMENT
// LIKE, idf.py -p /dev/cu.usbserial-0001 flash -b 230400
//                                               ^~~~~~~~  




// TODO :
// 1. ANALYZE WIFI FUNCTIONS
// 2. EDITTING HTML DOCUMENT TO SEND SCENE NUMBER
// 3. 
//
//


// FOR LOGGING
#include "esp_log.h"

// FOR STORING TO MEMORY
#include "nvs_flash.h"

// THIS APPLICATION WILL 'FIRE(TX)' THE SCENE NUMBER USING UART
#include "uart_master_wifi.h"

// IMPLEMENTATION FOR APPLCATION LAYER IN THE NETWORK
#include "wifi_app.h"



// TAG DEFINITION FOR LOGGING
static const char TAG[] = "main";






// EVENT HANDLER FOR LOGGING WHEN WIFI IS CONNECTED !
void wifi_application_connected_events(void) {

	ESP_LOGI(TAG, "WiFi Application Connected!!");

}




void app_main(void) {


    // INITIALIZING FLASH MEMORY ON THE CHIP
    //
    // < ABOUT NVS FLASH >
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/nvs_flash.html
    // : Non-Volatile Storage FOR NVS
    //   
    //
	esp_err_t ret = nvs_flash_init();


	// IF ERROR IS RETURNED WHEN FLASH MEMORY INITIALIZED,
	// AND IF THE ERROR OCCURED BY LACKING SPACE,
	// ERASE THE CARD
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {

		ESP_ERROR_CHECK(nvs_flash_erase());			// ERASING FLASH THEN CHECK THE ERROR
		ret = nvs_flash_init();						// RE-INITIALIZATION

	}
	
	ESP_ERROR_CHECK(ret);


	// STARTING WIFI
	wifi_app_start();


	// START UART COMMUNICATION
	uart_wifi_task_start();

}







