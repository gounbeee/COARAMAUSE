/*
 * uart_slave_lcd.c
 *
 *  Created on: 2022/03/05
 *      Author: gounbeee
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"


#include "uart_slave_lcd.h"




static const int RX_BUF_SIZE = 1024;

#define TXD_PIN (GPIO_NUM_22)
#define RXD_PIN (GPIO_NUM_5)


//static uint8_t* gUartData;
static char gUartData[128];




// // REPORTING BACK TO LCD MODULE
// static void tx_task(void *arg) {
//     //vTaskDelay(NULL); // this will prevent task from running right after it is initialised, NULL parameter known that it is asking itself to delay.
    
//     printf("((((****))))  FROM NOW, UART DATA WILL BE REPORTED !\n");

//     while(1) {

//         // 2 DELAY TIMERS
//         // WE WANTED THIS PROCESS IS MIDDLE TIME AREA
//         // IN ALL OF OUR PROCESS 
//         vTaskDelay( 1000 / portTICK_PERIOD_MS );


//         // -----------------------
//         // UART SENDING BACK TO WIFI MODULE !
//         printf("((((****))))  UART tx_task :: FROM NOW, UART DATA WILL BE REPORTED !\n");

//         if( gUartData != NULL) {

//             int txbts = uartTxSend(gUartData);

//             if( txbts > 0 ) {
//                 printf("  ((((****))))  pngSlide  ****   UART DATA REPORTED (currScn) TO LCD !!  ----  DATA WAS  %s  \r\n", gUartData);
//             }
//         }
//         vTaskDelay( 1000 / portTICK_PERIOD_MS );
//     }
// }


void uartInit(void) {

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




int uartTxSend(char* uartDt) {

    int len = strlen(uartDt);
    int txBytes = uart_write_bytes(UART_NUM_1, uartDt, len);
    printf("** uartTxSend ::  Wrote %d bytes\n", txBytes);

    return txBytes;
}







char* uartRxRead() {


    char rxBuf[128];


    //const int rxBytes = uart_read_bytes(UART_NUM_1, gUartData, 16, 20 / portTICK_PERIOD_MS);
    const int rxBytes = uart_read_bytes(UART_NUM_1, rxBuf, 16, 20 / portTICK_PERIOD_MS);


    if (rxBytes > 0) {

        // DEFINE END OF LINE
        rxBuf[rxBytes] = '\0';
        sprintf(gUartData, "%s", rxBuf);
        


    } else {


        //printf(" --------   THERE IS NO BYTES TO READ...\n");

    }

    printf("Read %d bytes: '%s\n'", rxBytes, gUartData);
    //ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, gUartData, rxBytes, ESP_LOG_INFO);




    return gUartData;

}





// void uart_lcd_task_start(void* param, int scale, int priority, int cpuCoreInd) {

//     xTaskCreatePinnedToCore(tx_task, "uart_tx_task", 1024 * scale, param, priority, NULL, cpuCoreInd);


// }



