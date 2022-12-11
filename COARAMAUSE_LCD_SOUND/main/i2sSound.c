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





#include <esp_heap_caps.h>
#include <string.h>
#include <stdbool.h>

#include "i2sSound.h"




// https://www.youtube.com/watch?v=oVVcuUuJ9CM&t=260s
// https://github.com/MrBuddyCasino/ESP32_Soundboard



// < GPIO POTENTIOMETER > 
// https://embeddedexplorer.com/esp32-adc-esp-idf-tutorial/
// https://github.com/espressif/esp-idf/blob/5c1044d84d625219eafa18c24758d9f0e4006b2c/examples/peripherals/gpio/generic_gpio/main/gpio_example_main.c



// -----------------
// < ESP32 SYNTH >
// https://github.com/infrasonicaudio/esp32-i2s-synth-example



// < ESP32 CONNECTION >
// https://dronebotworkshop.com/esp32-i2s/




static const char* TAG = "i2sSound";

static i2sSound_Hnd_t s_hnd;
static QueueHandle_t* s_queue_hnd;
static TaskHandle_t s_taskhnd_i2sSound = NULL;


// FOR ADC CHARACTERISTICS FOR VOLUMN CONTROL
//static esp_adc_cal_characteristics_t adc1_chars;
//static float volumn_read = 0.0f;


// Accumulated phase
//static float p = 0.0f;
    
// Output buffer (2ch interleaved)
// static uint16_t out_buf[SINE_DMA_BUF_LEN * 2];






static void checkHeap() {

    // ------------------------------------------------------------------------------------------
    // FOR DEBUGGING HEAP MEMORY
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/heap_debug.html
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/mem_alloc.html#_CPPv423heap_caps_get_free_size8uint32_t

    size_t gHEAPMEMORY_REMAINED;

    gHEAPMEMORY_REMAINED = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    printf("===================================================\r\n");
    printf("MEMORY CHECKING REMAINED     ::     PNGSLIDE      ::  %d\r\n", gHEAPMEMORY_REMAINED);
    printf("task stack: %d\n", uxTaskGetStackHighWaterMark(NULL));

    //vTaskDelay(1000 / portTICK_PERIOD_MS);

}






// // Fill the output buffer and write to I2S DMA
// static void playSineWave() {



//     float samp = 0.0f;
//     size_t bytes_written;



//     for (int i=0; i < SINE_DMA_BUF_LEN; i++) {


//         // Scale sine sample to 0-1 for internal DAC
//         // (can't output negative voltage)

//         // APPLYING VOLUME CONTROL
//         samp = (sinf(p) + 1.0f) * 0.5f;             // FLOAT OVER ZERO AND SCALE DOWN TO UNDER 1


//         // Increment and wrap phase
//         p += SINE_PHASE_INC;
//         if (p >= SINE_TWOPI)
//             p -= SINE_TWOPI;
        
//         // Scale to 8-bit integer range
//         samp *= 255.0f;
//         //samp *= 0.005f;
//         samp *= volumn_read;
//         if(samp < 0) samp = 0;


//         //printf("%f ", samp);


//         // Shift to MSB of 16-bit int for internal DAC
//         //
//         // FLOAT IS 32 BITS DATA
//         // 
//         out_buf[i*2+1] = (uint16_t)samp << 8;           // FOR RIGHT CHANNEL

//         out_buf[i*2] = out_buf[i*2+1];                  // FOR LEFT CHANNEL
            




//     }

//     // Write with max delay. We want to push buffers as fast as we
//     // can into DMA memory. If DMA memory isn't transmitted yet this
//     // will yield the task until the interrupt fires when DMA buffer has 
//     // space again. If we aren't keeping up with the real-time deadline,
//     // audio will glitch and the task will completely consume the CPU,
//     // not allowing any task switching interrupts to be processed.
//     i2s_write(I2S_NUM, out_buf, sizeof(out_buf), &bytes_written, portMAX_DELAY);

//     // You could put a taskYIELD() here to ensure other tasks always have a chance to run.
//     taskYIELD();
// }





static void playSamples(WavType_t* wavFileHead, int length, i2sSound_Mode_t playMode, char* msgPngSlide) {


    // IF playMode IS 'PLAY_TO_END_'
    // length WILL BE IGNORED!
    if( playMode == PLAY_TO_END_LOOP || playMode == PLAY_TO_END_NOLOOP) {
        length = -1;
    }


    // ------------------------------------------------------------
    // PLAYING

    size_t bytes_written;


    // printf("=========== WAITING\n");       
    // vTaskDelay(5000 / portTICK_PERIOD_MS);
    // printf("=========== PLAY\n");       


    // -------------------------
    // PLAYER < START >
    i2s_zero_dma_buffer(I2S_NUM_0);
    i2s_start(I2S_NUM_0);



    // -------------------------
    // PLAYER < PLAY >

    // BECAUSE WavType IS INITIALIZED, WE WILL GET FIRST SAMPLE BUFFER (8192 BYTES OF CHUNK)
    WavType_Data_t* buff_current = GetCurrentBuffer( wavFileHead );


    printf("buff_current->buffer            ::        %p \n", buff_current->buffer);
    printf("sizeof(*buff_current)           ::        %d \n", sizeof(*buff_current) );
    printf("buff_current->bufferLength      ::        %d \n", buff_current->bufferLength);



    // -----------------------------------------------------
    // FOR DEBUG
    // -----------------------------------------------------
    // < PRINT OUT HEX DECIMAL FROM BINARY-READ FILE !!!! >
    // https://stackoverflow.com/questions/49242874/how-to-print-contents-of-buffer-in-c

    // for (int i=0; i < buff_current->bufferLength; i++) {
    //     printf("%02x ", buff_current->buffer[i]);
    //     if ((i+1)%16 == 0) printf("\n");
    // }


    // ------------------
    // LOOP OR NOT
    // TODO :: CURRENTLY THIS WILL RUN FOREVER !

    if( playMode == PLAY_TO_SPECIFIED_LOOP ) {
        bool loopFlag_a = true;

        while(loopFlag_a) {
            printf("@@@@  PLAYING WAVE FILE TO SPECIFED LOCATION WE DEFINED AND LOOP !! \n");

            buff_current = ResetBuffer( wavFileHead );
            for(int j=0; j < length; j++) {

                printf("----- PLAYING    %d \n", j); 
                buff_current = GetNextBuffer( wavFileHead );
                i2s_write(I2S_NUM, buff_current->buffer, buff_current->bufferLength, &bytes_written, portMAX_DELAY);


                // ---------------------------------------------
                // CHECKING MESSAGE FROM PNGSLIDE QUEUE
                if( *s_queue_hnd != 0 ) {
                    //printf("s_queue_hnd IS OK  !\n");

                    if( xQueueReceive( *s_queue_hnd, msgPngSlide, ( TickType_t ) 0 )) {
                        printf("RECEIVED FROM PNGSLIDE !!!!  ---   %s \n", msgPngSlide );
                        //ESP_LOGI(TAG, "RECEIVED FROM PNGSLIDE !!!!  ---   %s \n", s_msg_from_pngSlide->msg );

                        // STORE NEW FILENAME TO HANDLER !!!!
                        strcpy(s_hnd.current_fileName, msgPngSlide);

                        // FLAG SETTING FOR EXITING WHILE LOOP
                        loopFlag_a = false;

                        // EXITING FOR LOOP
                        break;
                    } 

                } else {

                    ESP_LOGI(TAG, "i2sSound_Task() QUEUE ERROR");

                }
            }   // FOR LOOP
        }  // WHILE LOOP
        
    } else if( playMode == PLAY_TO_END_LOOP ) { 
        bool loopFlag_b = true;

        while(loopFlag_b) {

            // ----------------------------------------------------------------------
            printf("@@@@  PLAYING WAVE FILE TO END OF FILE AND LOOP !! \n");
            buff_current = ResetBuffer( wavFileHead );

            int newLength = wavFileHead->data_size / buff_current->bufferLength;
            printf("@@@@  newLength   ::    %d  \n", newLength);


            // TODO :: DEAL WITH THIS -2 !
            // DECREASED 2 CHUNK OF SAMPLES BECAUSE IT GOES OVER THE BOUNDARY !!!
            for(int j=0; j < newLength-2; j++) {
                //printf("----- PLAYING    %d \n", j); 
                buff_current = GetNextBuffer( wavFileHead );
                i2s_write(I2S_NUM, buff_current->buffer, buff_current->bufferLength, &bytes_written, portMAX_DELAY);
                //printf("----- bytes_written  Buffer index ::  %d ,  WRITTEN BYTES ::   %d \n", j, bytes_written); 

                // ---------------------------------------------
                // CHECKING MESSAGE FROM PNGSLIDE QUEUE
                if( *s_queue_hnd != 0 ) {
                    //printf("s_queue_hnd IS OK  !\n");

                    if( xQueueReceive( *s_queue_hnd, msgPngSlide, ( TickType_t ) 0 )) {
                        printf("RECEIVED FROM PNGSLIDE !!!!  ---   %s \n", msgPngSlide );
                        //ESP_LOGI(TAG, "RECEIVED FROM PNGSLIDE !!!!  ---   %s \n", s_msg_from_pngSlide->msg );

                        // STORE NEW FILENAME TO HANDLER !!!!
                        strcpy(s_hnd.current_fileName, msgPngSlide);

                        // FLAG SETTING FOR EXITING WHILE LOOP
                        loopFlag_b = false;

                        // EXITING FOR LOOP
                        break;
                    } 

                } else {

                    ESP_LOGI(TAG, "i2sSound_Task() QUEUE ERROR");

                }

            } // FOR LOOP

        } // WHILE LOOP


    }


    printf("@@@@  JUST BEFORE i2s_stop(I2S_NUM_0); !! \n");
    printf("@@@@  WE ARE GOING OUT playSamples() FUNCTION !! \n");



    // -------------------------
    // PLAYER < STOP >
    i2s_stop(I2S_NUM_0);

    // FREE CURRENT BUFFER
    free(buff_current);
}







static void i2sSound_PlayWaveFile(char* fileNm, int length, i2sSound_Mode_t playMode, char* msgFromPngSlide) {

    // SETTING PATH (SDCARD)
    char* wavPath = "/sdcard/wav/";
    char* wavFileName= fileNm;

    // ALLOCATINH MEMORY FOR PATH
    char* wavFileFullPath;
    wavFileFullPath = malloc(sizeof(char) * 256);
    sprintf(wavFileFullPath, "%s%s", wavPath, wavFileName);

    printf("wavFileFullPath IS   ::    %s \n", wavFileFullPath);


    // SETTING FILE OBJECT
    // WE USED 'BINARY' SETTING

    FILE* wavFileCurrent      = fopen(wavFileFullPath, "rb");
    

    // WE FREE THE MEMORY FOR PATH
    free(wavFileFullPath);

    // ERROR CHECKING FOR FILE OBJECT
    if (wavFileCurrent == NULL) {

        printf("^^^^^^^^^^^ Cannot open file \n");

    } else {

        printf("=========== File Opened properly\n");  

    }
  

    // OUR TYPE FOR GETTING INFORMATION OF WAV FILE WE WANT TO IMPORT


    //WavType_t wavFileHeader;


    InitWavStructFromFile(wavFileCurrent, &s_hnd.wavFileHeader); 

    // PRINT OUT THE INFORMATION (FOR DEBUG PURPOSE)
    DumpWavStruct(&s_hnd.wavFileHeader);


    // PLAY FILE
    // ** THIS BLOCKS THE PROCESS
    playSamples(&s_hnd.wavFileHeader, length, playMode, msgFromPngSlide);


    // CLOSING
    printf("------  MUSIC STOPPED TO PLAY !!!! \n");

    fclose(wavFileCurrent);

    printf("------  MUSIC FILE CLOSED !!!! \n");


    //vTaskDelay(3000 / portTICK_PERIOD_MS);

}







void i2sSound_Init(QueueHandle_t* queHnd) {

    s_queue_hnd = queHnd;



    //for 36Khz sample rates, we create 100Hz sine wave, every cycle need 36000/100 = 360 samples (4-bytes or 8-bytes each sample)
    //depend on bits_per_sample
    //using 6 buffers, we need 60-samples per buffer
    //if 2-channels, 16-bit each channel, total buffer is 360*4 = 1440 bytes
    //if 2-channels, 24/32-bit each channel, total buffer is 360*8 = 2880 bytes


    // GOAL   :: 100 Hz SINE WAVE
    // USING  :: 36000 Hz SAMPLE RATE SETTING (QUANTIZED 36000 TIMES PER 1 SECOND)
    //
    // --------------------------------------------------------------------------------------
    // IMAGE
    // 
    // ||||||||||||||||||||||||||||||||||  ...     36000 Hz      < OUR SAMPLE RATE >
    // |          |            |           ...     100 Hz        < SINE WAVE CYCLE >
    //
    // < 1 Cycle  >
    //     vvvvv
    // <360 SAMPLES>  NEEDED
    //
    // --------------------------------------------------------------------------------------
    //  
    // THEN, WE USE DMA_BUFFER AREA, 
    // 
    // SIZE OF SINGLE BUFFER :: 60 
    //           x
    // COUNT OF BUFFERS      :: 6
    //           ||
    //                       :: 360 !   FOR < 360 SAMPLES > WE ARE NEEDED
    // 
    //



    // < ABOUT DMA SETTINGS -- VERY INFORMATIVE!!! >
    // https://www.atomic14.com/2021/04/20/esp32-i2s-dma-buf-len-buf-count.html



    i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,
        .sample_rate = 8000,                                    // MAX98537A CAN SAMPLE AROUND 8kHz to 96kHz
        //.sample_rate = 44100,
        //.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .bits_per_sample = 16,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_MSB,
        //.communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
        //.dma_buf_count = 6,
        //.dma_buf_len = 60,
        .dma_buf_count = 32*2,
        .dma_buf_len = 64*2,
        .use_apll = false,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1                                //Interrupt level 1
    };


    i2s_pin_config_t pin_config = {
        .mck_io_num = I2S_PIN_NO_CHANGE,
        .bck_io_num = I2S_BCK_IO,
        .ws_io_num = I2S_WS_IO,
        .data_out_num = I2S_DO_IO,
        .data_in_num = I2S_DI_IO                                               //Not used
    };


    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);



    // SETTING UP FOR VOLUMN
    // SETTING UP GPIO etc.
    i2sSound_Setup_Volumn();

    // ----------------
    // OPENING MUSIC 
    // TODO :: SELECT RIGHT ONE !!!!
    strcpy(s_hnd.current_fileName, "1.wav");
    printf("checkPlayChanged()  --  s_hnd.current_fileName ::   %s   ::   %p   \n ", s_hnd.current_fileName, &s_hnd.current_fileName);


    // MESSAGE FOR RECEIVING FROM PNGSLIDE
    char msg_from_pngSlide[20];


    // POTENTIOMETER TASK
    xTaskCreatePinnedToCore(i2sSound_Task_Volumn, "i2sSound_Task_Volumn", 2048, NULL, 5, NULL, 1);
    

    // START SOUND TASK

    // ----------------------------------------------------------
    // TASK HANDLER, POINTER OF MESSAGE OBJECT IS CRITICAL !!!!
    xTaskCreatePinnedToCore(i2sSound_Task, "i2sSound_Task", 2048, &msg_from_pngSlide, 5, &s_taskhnd_i2sSound, 1);
        

}









// void isr_button_pressed(void *args)
// {
//   int btn_state = gpio_get_level(BUTTON_GPIO_VOL_DECREASE);

//   printf("BUTTON STATE ::   %d \n", btn_state );

//   //gpio_set_level(LED_GPIO,btn_state);


// }




void i2sSound_Setup_Volumn() {


    // esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    
    // ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));

    // ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11));



    // //Configure button
    // gpio_config_t btn_config;
    // btn_config.intr_type = GPIO_INTR_ANYEDGE;                   //Enable interrupt on both rising and falling edges
    // btn_config.mode = GPIO_MODE_INPUT;                          //Set as Input
    // btn_config.pin_bit_mask = (1 << BUTTON_GPIO);               //Bitmask
    // btn_config.pull_up_en = GPIO_PULLUP_DISABLE;                //Disable pullup
    // btn_config.pull_down_en = GPIO_PULLDOWN_ENABLE;             //Enable pulldown
    // gpio_config(&btn_config);
    // printf("Button configured\n");

    // //Configure LED
    // //gpio_pad_select_gpio(LED_GPIO);                   //Set pin as GPIO
    // // gpio_pad_select_gpio(LED_GPIO);                   //Set pin as GPIO
    // // gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);   //Set as Output
    // // printf("LED configured\n");

    // //Configure interrupt and add handler
    // gpio_install_isr_service(0);                      //Start Interrupt Service Routine service
    // gpio_isr_handler_add(BUTTON_GPIO, isr_button_pressed, NULL); //Add handler of interrupt
    // printf("Interrupt configured\n");



    //gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_set_direction(BUTTON_GPIO_VOL_INCREASE, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_GPIO_VOL_DECREASE, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_GPIO_RESET, GPIO_MODE_INPUT);

}







void i2sSound_Task_Volumn(void* pvParameters) {
	
	//uint32_t voltage;

	// uint32_t reading;


	while (1) {

        // reading = adc1_get_raw(ADC1_CHANNEL_6);
        // // voltage = esp_adc_cal_raw_to_voltage(reading, &adc1_chars);

        // ESP_LOGI(TAG, "ADC1_CHANNEL_6 RAW SIGNAL : %d ", reading);

        // // < DOUBLE TYPE IN C AND CASTING >
        // // https://www.tutorialspoint.com/cprogramming/c_type_casting.htm
        // volumn_read = (double) reading / 4095;
        // ESP_LOGI(TAG, "ADC1_CHANNEL_6 VOLUMN FLOAT : %f ", volumn_read);



        // printf("--------------------------\n");
        // printf("BUTTON_GPIO_VOL_INCREASE  ::   %d \n", gpio_get_level(BUTTON_GPIO_VOL_INCREASE));
        // printf("BUTTON_GPIO_VOL_DECREASE  ::   %d \n", gpio_get_level(BUTTON_GPIO_VOL_DECREASE));
        // printf("BUTTON_GPIO_RESET  ::   %d \n", gpio_get_level(BUTTON_GPIO_RESET));


        if (gpio_get_level(BUTTON_GPIO_VOL_DECREASE) == 1)
        {  
            printf("BUTTON A PRESSED ! \n");
            // volumn_read -= 0.025f;
            // if(volumn_read < 0.0f) volumn_read = 0.0f;

            // printf("volumn_read  ::  %f \n", volumn_read);
            // //gpio_set_level(LED_PIN, 1);   


        } 
        else if(gpio_get_level(BUTTON_GPIO_VOL_INCREASE) == 1)
        {
            printf("BUTTON B PRESSED ! \n");
            // volumn_read += 0.025f;
            // printf("volumn_read  ::  %f \n", volumn_read);
            // //gpio_set_level(LED_PIN, 0);   


        }
        else if(gpio_get_level(BUTTON_GPIO_RESET) == 1)
        {
            printf("RESET ! \n");
            esp_restart();

        }

        vTaskDelay(pdMS_TO_TICKS(100));

    }

}



// < CONVERT BINARY TO DECIMAL >
// https://www.javatpoint.com/binary-to-decimal-number-in-c
// ****** THIS FUNCTION TREATS 'NORMAL' BINARY NUMBER !!!!
//        SO IT IS ALIGNED AS 'BIG ENDIAN' ORDER !!!!
int convertBinaryToDecimal(uint16_t binary) {


    int decimal_num = 0, base = 1, rem;  


    while ( binary > 0)  
    {  
        rem         = binary % 10;                                  /* divide the binary number by 10 and store the remainder in rem variable. */  
        decimal_num = decimal_num + rem * base;  
        binary      = binary / 10;                                  // divide the number with quotient  
        base        = base * 2;  
    }  



    return decimal_num;

}


// < CONVERT DECIMAL TO BINARY >
// https://www.javatpoint.com/binary-to-decimal-number-in-c
// ****** THIS FUNCTION TREATS 'NORMAL' BINARY NUMBER !!!!
//        SO IT IS ALIGNED AS 'BIG ENDIAN' ORDER !!!!
uint16_t* convertDecimalToBinary(int decimal, uint16_t* resultBin) {


    // array to store binary number
    char binaryNm[16];

    // counter for binary array
    int i = 0;
    while (decimal > 0) {
        // storing remainder in binary array

        // REMAINDER
        binaryNm[i] = (char) (decimal % 2);         // CALCULATION IS FILLING FROM 0 DEGREE TO 10, 100, 1000...
                                                    // LIKE 10011    ->     { 1, 1, 0, 0, 1 }
        // QUOTIENT                                 //                        ~~~~~~~~~~~~~
        decimal = decimal / 2;                      //                              |
                                                    //                              |
        // NEXT CALCULATION                         //                              |
        i++;                                        //                              |
    }                                               //                              |
                                                    //                              |   
                                                    //                              |
                                                    //                              /
    // printing binary array in < REVERSE ORDER >             <<<----------------- /      ** WHY WE ARE DOING THIS
    int incIdx = 0;
    for (int j = i - 1; j >= 0; j--) {
        
        printf("%c", binaryNm[j]);                                      

        resultBin[incIdx] = (int) binaryNm[j];
        incIdx++;
    }


    return resultBin;

}



uint16_t convertBigEndianToLittle(uint16_t littleEndInput) {



    // ----------------------------------------------------------
    // < INVERT AGAIN > 
    uint16_t binA,binB;
    uint16_t result;

    binA = (littleEndInput & 0xff  ) << 8;
    binB = (littleEndInput & 0xff00) >> 8;

    result = binA | binB;


    return result;

}



uint16_t convertLittleEndianToBig(uint16_t bigEndInput) {

    // 1. CONVERT LITTLE ENDIAN BINARY
    // https://stackoverflow.com/questions/19275955/convert-little-endian-to-big-endian
    // CAN I USE THIS ???  __builtin_bswap32()
    //
    //
    uint16_t invertedResult = 0;

    // --------------------------------------------------
    // THERE ARE 2 BYTES, SO WE WILL DIVIDE BY 2
    //
    // BB AA          -->         AA BB
    // -----                      -----
    // (1-SAMPLE)
    //
    // 
    // 1. MASKING
    // 
    // SO, IN ORDER TO PICK UP WE WANT TO SHIFT,
    // WE USE "MASK"
    //
    // BY MULTIPLYING "FF", "FF 00", "FF 00 00"...
    //
    // ex) 
    //
    // BB AA   &   FF         =>     00 AA                 <AND> BOOL CALCULATION   WE WILL STORE TO bin0
    // BB AA   &   FF 00      =>     BB 00                                          WE WILL STORE TO bin1
    //
    //
    // 2. THEN SHIFT BYTE ORDER
    // 
    // 00 AA  << 8        =          AA 00   
    //        ~~~~
    // 8 bit
    //    8bit
    //
    // BB 00  >> 8        =          00 BB
    //        ~~~~
    //
    //
    // 3. THEN, JUST ADD TOGETHER
    // 
    //               AA 00
    //            +  00 BB
    //            ----------
    //               AA BB
    //               *****
    //                 |
    //  <<<<<<   FINAL RESULT !!!!    >>>>>>
    // 
    uint16_t bin0,bin1;

    bin0 = (bigEndInput & 0xff  ) << 8;
    bin1 = (bigEndInput & 0xff00) >> 8;

    invertedResult = bin0 | bin1;



    return invertedResult;

}



void i2sSound_Task(void *pvParameters) {

    char* msg_pngSlide = (char*) pvParameters; 


    while (1) {


        // -------------------------------------------------------------------
        printf("---- MUSIC PLAY  --  TASK  --  s_current_fileName  ::   %s \n", s_hnd.current_fileName);
        i2sSound_PlayWaveFile(s_hnd.current_fileName, 30, PLAY_TO_END_LOOP, msg_pngSlide);
        
        printf("---- MUSIC PLAY  --  TASK  --  EXITED THEN THIS WILL LOOP  IMMEDIATLEY !!! \n");

        vTaskDelay(1);


    }

}






