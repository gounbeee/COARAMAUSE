

#include "uart_master_wifi.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"




static const int RX_BUF_SIZE = 1024;


// SCENE NUMBER CURRENTLY PLAYING
static char g_sceneNumStrNow[1] = "0";
static int g_sceneNumLast = 0;



#define TXD_PIN (GPIO_NUM_4)
#define RXD_PIN (GPIO_NUM_5)



void init(void) {

    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };


    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM_1, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);


}


// < SEND DATA TO DISPLAY MODULE >
int sendData(const char* logName, const char* data) {

    const int len = strlen(data);
    const int txBytes = uart_write_bytes(UART_NUM_1, data, len);

    //ESP_LOGI(logName, "Wrote %d bytes", txBytes);


    return txBytes;

}


static void tx_task(void *arg) {


    static const char *TX_TASK_TAG = "TX_TASK";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);


    
    while (1) {

        int sceneNumNow = atoi(g_sceneNumStrNow);


        if(g_sceneNumLast != sceneNumNow) {

            // SENDING SCENE NUMBER TO DISPLAY MODULE

            sendData(TX_TASK_TAG, g_sceneNumStrNow);

            g_sceneNumLast = sceneNumNow;


            printf("   ----  tx_task :: DATA SENT !!! \r\n");
            printf("   ----  tx_task :: SCENE NUMBER  %s  IS SENT ! \r\n" , g_sceneNumStrNow );

        } else {

            //printf("   ----  tx_task :: SAME SCENE NUMBER IS PRESSED ON THE WEB PAGE UI !!! \r\n");

        }


        vTaskDelay(1000 / portTICK_PERIOD_MS);
            



    }


}





// // BELOW FUNCTION READ THE REPORT FROM LCD MODULE !!!!
// // THE DATA WILL BE CURRENT SCENE NUMBER WHICH LCD MODULE IS PLAYING CURRENTLY,
// // SO IN THIS PROCESS WE 'CHECK' THE REPORTED NUMBER AND PROPER NUMBER,
// // THEN IF THAT IS UNMATCHED, WE NEED TO FIX !
// static void rx_task(void* arg) {

//     static const char *RX_TASK_TAG = "RX_TASK";
//     esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    

//     while(1) {
//         vTaskDelay(1000 / portTICK_PERIOD_MS);


//         char rxBuf[128];

//         const int rxBytes = uart_read_bytes(UART_NUM_1, rxBuf, 16, 20 / portTICK_PERIOD_MS);


//         if (rxBytes > 0) {

//             // DEFINE END OF LINE
//             rxBuf[rxBytes] = '\0';
                      

//             printf(" --------  rx_task  :: Read %d bytes   :   THE DATA IS      ||||| %s |||||\n", rxBytes, rxBuf);

//             // CHECK

//             int currentWifiScn = atoi(g_sceneNumStrNow);
//             int currentLCDScn  = atoi(rxBuf);

//             if(currentWifiScn != currentLCDScn) {

//                 // FIX THE LCD MODULE'S SCENE NUMBER

//                 // SENDING SCENE NUMBER TO DISPLAY MODULE
//                 int txResult = sendData(RX_TASK_TAG, g_sceneNumStrNow);
//                 printf("\n");
//                 printf("   ----  rx_task :: (((((((())))))))  LCD AND WIFI MODULE'S SCENE NUMBER DOES NOT MATCHED !!!!!  \r\n");
//                 printf("   ----  rx_task :: (((((((())))))))  RESENT  DATA   %d  BYTES WAS SENT ! \r\n" , txResult );
//                 printf("\n");

//             }

//         } else {
//             printf(" --------  rx_task  :: THERE IS NO BYTES TO READ...\n");
//         }

//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }

// }






void uart_wifi_SetSceneNumber(char* scnStr) {
    printf("~~~   UART-APP :: uart_wifi_SetSceneNumber() EXECUTED! NUMBER   %s  WILL BE SENT ! \r\n" , scnStr );

    strcpy( g_sceneNumStrNow, scnStr);

    printf("~~~   UART-APP :: g_sceneNumStrNow WAS   %s   ! \r\n" , g_sceneNumStrNow );

}














void uart_wifi_task_start() {


    init();
    
    //xTaskCreate(rx_task, "uart_rx_task", 1024*2, NULL, 2, NULL);
    xTaskCreate(tx_task, "uart_tx_task", 1024*2, NULL, 2, NULL);


}



