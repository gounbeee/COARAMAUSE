

#ifndef MAIN_UART_SLAVE_LCD_H_
#define MAIN_UART_SLAVE_LCD_H_


#include <esp_heap_caps.h>


// ------------------------------------------------------------------------------------------
// FOR DEBUGGING HEAP MEMORY
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/heap_debug.html
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/mem_alloc.html#_CPPv423heap_caps_get_free_size8uint32_t

size_t gHEAPMEMORY_REMAINED;




void uartInit(void);
//void uart_lcd_task_start(void* param, int scale, int priority, int cpuCoreInd);



char* uartRxRead();


//int uartTxSend(char* uartDt);



#endif /* MAIN_UART_SLAVE_LCD_H_ */
