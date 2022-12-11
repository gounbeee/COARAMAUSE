#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"
#include "esp_heap_caps.h"
#include "esp_vfs_fat.h"


#include "sdmmc_cmd.h"


// < pngleAnim STRUCT >
// BY GOUNBEEE 2022
// 
// :: BELOW STRUCT IS WRAPPING pngle THEN EXTENDS ANIMATION FUNCTIONALITIES
// 
#include "pngSlide.h"

#include "driver/gpio.h"

#include "uart_slave_lcd.h"


//#include <esp_heap_trace.h>
#include <esp_heap_caps.h>




// #define NUM_RECORDS 100
// static heap_trace_record_t trace_record[NUM_RECORDS]; // This buffer must be in internal RAM


// --------------------------------------------------------------------------------------
// < FOR JTAG GDB DEBUGGING >

// xtensa-esp32-elf-gdb -x gdbinit build/13_LCD_PNG_VIEWER_8MB.elf
// xtensa-esp32-elf-gdb -x gdbinit build/13_LCD_PNG_VIEWER_16MB.elf
// openocd -f board/esp32-wrover-kit-3.3v.cfg




// --------------------------------------------------------------------------------------
// FOR DEBUG USING ESP-PROG JTAG

// https://www.digikey.jp/en/maker/projects/esp32-thing-plus-hookup-guide/bfaaff41d67c4f9b9062db5d5e9adf8a
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/jtag-debugging/configure-other-jtag.html
// https://docs.espressif.com/projects/espressif-esp-iot-solution/en/latest/hw-reference/ESP-Prog_guide.html
// https://www.codetd.com/ja/article/12080360

// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/jtag-debugging/using-debugger.html


// ESP32 Devkitc v4
// https://www.youtube.com/watch?v=s7_h3aFueWo




#define PIN_NUM_SD_CS   21
#define MOUNT_POINT "/sdcard"
#define SPI_DMA_CHAN    1





#if 0
// ** SIZE IS CURRENTLY SETTED IN sdkconfig.h IN Build/config FOLDER ! **
// #define IMAGEWIDTH		240
// #define IMAGEHEIGHT 	320
#endif




PngSlide_t pngSlideInstance;





// --------------------------------------------------
// GLOBAL VARIABLES

static const char *TAG = "MAIN_APP";

static sdmmc_card_t *card;

static PngSlide_t* pngSlide;


// ------------------------------------------------------------------------------------------



static void SPIFFS_Directory(char * path) {
	DIR* dir = opendir(path);
	assert(dir != NULL);
	while (true) {
		struct dirent*pe = readdir(dir);
		if (!pe) break;
		ESP_LOGI(__FUNCTION__,"d_name=%s d_ino=%d d_type=%x", pe->d_name,pe->d_ino, pe->d_type);
	}
	closedir(dir);
}







void app_main(void) {

	//ESP_ERROR_CHECK( heap_trace_init_standalone(trace_record, NUM_RECORDS) );



    // ===========================================================================




    esp_err_t ret_sd;


    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
#ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
#else
        .format_if_mount_failed = false,
#endif // EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .max_files = 16,
        .allocation_unit_size = 16 * 1024
    };



    const char mount_point[] = MOUNT_POINT;
    ESP_LOGI(TAG, "Initializing SD card");


    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.
    ESP_LOGI(TAG, "Using SPI peripheral");

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = CONFIG_MOSI_GPIO,
        .miso_io_num = CONFIG_MISO_GPIO,
        .sclk_io_num = CONFIG_SCLK_GPIO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };


    ret_sd = spi_bus_initialize(host.slot, &bus_cfg, SPI_DMA_CHAN);
    if (ret_sd != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize bus.");
        return;
    }


    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_SD_CS;
    slot_config.host_id = host.slot;


    ESP_LOGI(TAG, "Mounting filesystem");
    ret_sd = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret_sd != ESP_OK) {
        if (ret_sd == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret_sd));
        }
        return;
    }
    ESP_LOGI(TAG, "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);









    // ===========================================================================



    // Use POSIX and C standard library functions to work with files.



    // // // First create a file.
    // const char *file_hello = MOUNT_POINT"/hello.txt";

    // ESP_LOGI(TAG, "Opening file %s", file_hello);
    // FILE *f = fopen(file_hello, "w");
    // if (f == NULL) {
    //     ESP_LOGE(TAG, "Failed to open file for writing");
    //     return;
    // }
    // fprintf(f, "Hello %s!\n", card->cid.name);
    // fclose(f);
    // ESP_LOGI(TAG, "File written");

    // const char *file_foo = MOUNT_POINT"/foo.txt";

    // // Check if destination file exists before renaming
    // struct stat st;
    // if (stat(file_foo, &st) == 0) {
    //     // Delete it if it exists
    //     unlink(file_foo);
    // }

    // // Rename original file
    // ESP_LOGI(TAG, "Renaming file %s to %s", file_hello, file_foo);
    // if (rename(file_hello, file_foo) != 0) {
    //     ESP_LOGE(TAG, "Rename failed");
    //     return;
    // }

    // // Open renamed file for reading
    // ESP_LOGI(TAG, "Reading file %s", file_foo);
    // f = fopen(file_foo, "r");
    // if (f == NULL) {
    //     ESP_LOGE(TAG, "Failed to open file for reading");
    //     return;
    // }

    // // Read a line from file
    // char line[64];
    // fgets(line, sizeof(line), f);
    // fclose(f);

    // // Strip newline
    // char *pos = strchr(line, '\n');
    // if (pos) {
    //     *pos = '\0';
    // }
    // ESP_LOGI(TAG, "Read from file: '%s'", line);





    // // All done, unmount partition and disable SPI peripheral
    // esp_vfs_fat_sdcard_unmount(mount_point, card);
    // ESP_LOGI(TAG, "Card unmounted");

    // //deinitialize the bus after all devices are removed
    // spi_bus_free(host.slot);






    // --------------------------------------------------------




	ESP_LOGI(TAG, "Initializing SPIFFS");

	esp_vfs_spiffs_conf_t conf = {
		.base_path = "/spiffs",
		.partition_label = NULL,
		.max_files = 16,
		.format_if_mount_failed =true
	};

	// Use settings defined above toinitialize and mount SPIFFS filesystem.
	// Note: esp_vfs_spiffs_register is anall-in-one convenience function.
	esp_err_t ret = esp_vfs_spiffs_register(&conf);

	if (ret != ESP_OK) {
		if (ret == ESP_FAIL) {
			ESP_LOGE(TAG, "Failed to mount or format filesystem");
		} else if (ret == ESP_ERR_NOT_FOUND) {
			ESP_LOGE(TAG, "Failed to find SPIFFS partition");
		} else {
			ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)",esp_err_to_name(ret));
		}
		return;
	}

	size_t total = 0, used = 0;
	ret = esp_spiffs_info(NULL, &total,&used);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG,"Failed to get SPIFFS partition information (%s)",esp_err_to_name(ret));
	} else {
		ESP_LOGI(TAG,"Partition size: total: %d, used: %d", total, used);
	}

	SPIFFS_Directory("/spiffs/");


    // -----------------------------------
    // INITIALIZING PNGSLIDE
    ESP_LOGI(TAG, "-----------------------------");
    ESP_LOGI(TAG, "-----------------------------");
    ESP_LOGI(TAG, "Initializing PNGSLIDE");


    //vTaskDelay( 1000 / portTICK_PERIOD_MS);








    pngSlide = PngSlideStart(0);


    // -----------------------------------
    // INITIALIZING UART
    ESP_LOGI(TAG, "-----------------------------");
    ESP_LOGI(TAG, "-----------------------------");
    ESP_LOGI(TAG, "Initializing UART");

    uartInit();
    uartRxInit();


	
	// -----------------------------------
	// TASK DESIGN
    
    uart_lcd_task_start(NULL, 2, 2, tskNO_AFFINITY);

    // =====================================================
    // < STACK SIZE IS CRITICAL !!!! >
    // :: WHEN YOU CANNOT GET PROPER MULTITASKING WITHOUT A REASON,
    //    YOU SHOULD CHECK THE SIZE OF STACK 
    //    WHEN I DECREASED 'scale' PARAMETER 16 TO 8, WE GOT
    //    MULTITASKING
	PngSlide_Task_Play_Start(pngSlide, 8, 2, tskNO_AFFINITY);


}



