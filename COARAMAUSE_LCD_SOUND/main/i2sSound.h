/*
 * MIT License
 *                    i2sSound
 *
 * Copyright (c) 2022 GOUNBEEE
 |                    www.gounbeee.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */




#ifndef MAIN_I2SSOUND_H_
#define MAIN_I2SSOUND_H_





#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_log.h"
#include <math.h>


#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "wavType.h"



#define BUTTON_GPIO_VOL_INCREASE	39
#define BUTTON_GPIO_VOL_DECREASE	34
#define BUTTON_GPIO_RESET			36


#define I2S_NUM         (0)



#define SINE_SAMPLE_RATE     (44100)
#define SINE_DMA_BUF_LEN     (32)
#define SINE_DMA_NUM_BUF     (2)
#define SINE_WAVE_FREQ_HZ    (200.0f)
// #define WAVE_FREQ_HZ    (2235.0f)
// #define WAVE_FREQ_HZ    (235.0f)
#define SINE_TWOPI           (6.28318531f)
#define SINE_PHASE_INC       (SINE_TWOPI * SINE_WAVE_FREQ_HZ / SINE_SAMPLE_RATE)



//#define I2S_BUFFER_SAMPLE_LENGTH  512



// #define SAMPLE_RATE     (36000)
// #define I2S_NUM         (0)
// //#define WAVE_FREQ_HZ    (12000)
// #define WAVE_FREQ_HZ    (100)
// #define PI              (3.14159265)




#define I2S_BCK_IO      (GPIO_NUM_25)   		// TO MAX98357A'S < Bit CLOCK >
#define I2S_WS_IO       (GPIO_NUM_26)   		// TO MAX98357A'S < Left-Right CLOCK >
#define I2S_DO_IO       (GPIO_NUM_13)   		// TO MAX98357A'S < Data IN >
#define I2S_DI_IO       (-1)
												// + VDD 3.3V TO Vin AND GAIN, THEN GROUND

// #define SAMPLE_PER_CYCLE (SAMPLE_RATE/WAVE_FREQ_HZ)


// TYPE FOR STORING SAMPLE DATA OF WAV FILE
typedef struct {

	uint16_t*		buffer;
	int  			bufferLength;

} i2sSound_Data_t;




// TYPE FOR PLAY MODE
typedef enum {

    PLAY_TO_SPECIFIED_NOLOOP,
    PLAY_TO_SPECIFIED_LOOP,
    PLAY_TO_END_NOLOOP,
    PLAY_TO_END_LOOP

} i2sSound_Mode_t;





// TYPE FOR PLAY MODE
typedef enum {

    PLAYING,
    STOPPING,
    STOPPED

} i2sSound_PlayStat_t;



typedef struct {


    char msg[ 20 ];


} i2sSound_QMsg_t;






typedef struct {


    WavType_t wavFileHeader;

    char current_fileName[20];
    char filename_last[20];

    i2sSound_PlayStat_t stat;



} i2sSound_Hnd_t;




// void setup_triangle_sine_waves(int bits);
void i2sSound_Init(QueueHandle_t* queHnd);
void i2sSound_Setup_Volumn();
void i2sSound_Task(void *pvParameters);
void i2sSound_Task_Volumn(void* pvParameters);
//void isr_button_pressed(void *args);

int convertBinaryToDecimal(uint16_t binary);
uint16_t* convertDecimalToBinary(int decimal, uint16_t* resultBin);





#endif