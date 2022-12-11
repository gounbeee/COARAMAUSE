

#ifndef MAIN_UART_MASTER_WIFI_H_
#define MAIN_UART_MASTER_WIFI_H_



void init(void);
int sendData(const char* logName, const char* data);
void uart_wifi_task_start();


void uart_wifi_SetSceneNumber(char* scnStr);




#endif /* MAIN_UART_MASTER_WIFI_H_ */
