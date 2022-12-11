/*
 * MIT License
 *                    pngSlide
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



/*
	PngSlide
	by Gounbeee (2022)
	
	BASED ON :
	1. Pngle (for png decoding)
	2. ILI9341 LIBRARY (for LCD control)
	
	LICENSE :
	<  >
	

	ABSTRACT :
	1. CREATING SLIDE WITH PNG IMAGE
	2. TIMING CONTROL OF SINGLE FRAME
	3. NOT CREATING FAST EFFECIENT PLAYBACK FOR MOVIE FILE


	NAME CONVENTIONS :
	1.  CAMEL STYLE (aaBbbbCccc)
	2.  ALL CAPITAL 							: MACRO || ENUM
	3.  START WITH CAPITAL && ENDED WITH _t 	: TYPE
	4.  START WITH CAPITAL && FUNCTION       	: API FUNCTION
	5.  START WITH !CAPITAL && FUNCTION      	: LOCAL FUNCTION
	6.  g  										: GLOBAL
	7.  p  										: POINTER
	8.  pp 										: POINTER TO POINTER
	9.  h  										: HANDLER
	10. 


	STUDY NOTES : 
	1. THERE ARE NOTES & TUTORIAL CODES USING
	"#if 0" MACROS


*/



#ifndef __PNGSLIDE_H__
#define __PNGSLIDE_H__

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

#include "driver/gpio.h"

#include "ili9340.h"
#include "fontx.h"

#include "decode_png.h"

#include <esp_heap_caps.h>

#include "pngle.h"
#include "i2sSound.h"



#define MAXSLIDENUM			8000
#define MAXFILENUM 			30
#define MAXFILENAMELENGTH 	100
#define MAXIMGGROUPCOUNT    50
#define MAX_CHAR_OF_INDEX	5			// RANGE TO 00000 ~ 99999	


#define	INTERVAL		400
#define WAIT	vTaskDelay(INTERVAL)				// SHORTCUT FOR DELAYING RTOS'S TASK

#define PAGE_CSV_FILENAME "pg.csv"


// FOR PNGLE DEBUG
// #define PNGLE_DEBUG








enum FPS{
	FPS_3  = 3320,
	FPS_6  = 1660,
	FPS_12 = 830,
	FPS_24 = 415,
	FPS_33 = 330,
	FPS_50 = 200
};


typedef enum {

	PNGLE_ANIM_STATE_STOPPED,
	PNGLE_ANIM_STATE_PLAYING,

} pngleAnim_state_t;



typedef struct {

	int* indexArray;
	int  size;

} StrSpilt_t;



// < FUNCTION IN STRUCT >
// https://stackoverflow.com/questions/17052443/c-function-inside-struct
typedef struct {

	int grpIndex;
	int imgCount;
	char** imgGroup;

	void (*InitList) ();
	void (*SetSingleImage) (const char*, int ind);
	int  (*GetGrpImgCount) ();
	void (*CloseList) ();

} ImgList_t;




// -------------------------------------------
// ANIMATION FOR "SINGLE" GROUP OF IMAGE
struct pngleAnim {

	pngle_t* pngle;								// pngle OBJECT FOR USING PNG IMAGE				
	FILE* fileCurrent;							// CURRENT FILE WE ARE PLAYING

	int imageCounts;							// IMAGE COUNTS OF SINGLE SCENE
	int currentFrame;							// CURRENT FRAME NUMBER WHILE PLAYBACK
	char *fileList[MAXFILENUM];					// FILE LIST FOR SINGLE GROUP
												// THIS APP MANAGES MULTIPLE GROUPS



	// ** CURRENTLY NOT USING
	pngleAnim_state_t currentState;				// TODO :: NOT USING NOW
	int imgCount;
	ImgList_t imgList;							// IMAGE LIST OF THIS GROUP OF IMAGE

};
typedef struct pngleAnim pngleAnim_t;



// -------------------------------------------
// MANAGING ENTIRE GROUPS OF IMAGE
typedef struct {

	TFT_t dev;
	pngleAnim_t hPngAnim;

	int currentGroupIndex;


} PngSlide_t;






// -----------------------------------------------------
// FUNCTION DECLARATIONS


// PUBLIC FUNCTIONS
//PngSlide_t*		PngSlideStart(int groupIndexToPlay);
PngSlide_t* 	PngSlideStart(PngSlide_t* pngSlideInstance, int groupIndexToPlay, QueueHandle_t* queHnd);
//void 			PngSlideAddImgGroup(const char** imgList);
pngle_t* 		PngSlidePlayCurrentFrame(TFT_t * dev,  pngle_t* pngle, int canvWidth, int canvHeight);
void 			PngSlide_Task_Play(void *pvParameters);
void 			PngSlide_Task_Play_Start(PngSlide_t* pngSlide, int scale, int priority, int cpuCoreInd);


// PRIVATE FUNCTIONS
void 			engineInit(PngSlide_t* pngSlide);
pngle_t* 		playFrame(TFT_t * dev,  pngle_t* pngle, int canvWidth, int canvHeight);
int 			protectSize( int length , char * channel);
pngle_t* 		readyNewBuffer(FILE* file, pngle_t* target);
int 			readyNextImgFile(pngleAnim_t* pngleAnim, int newFnum);
FILE* 			getNextImage(pngleAnim_t* hPngAnim);
int 			getFileListCount(char **fList, int sceneNum);




// HELPER FUNCTIONS
int 			calcSizeCharArray(const char** arr); 
void			makeFileNameList(char** target, int groupIndex);
int 			getFileListGrpIndex(const char * dirpath);
int 			getSeperatorCount(char* inputChr, const char* seperator);
void			getSplitIndex(int* output, int outputSize, char* inputChr, const char* seperator);
int				getSplittedWordByIndex(char* inputChr, const char* seperator, int seperatorCnt);
int				getImageGroupIndexFromFile(char* _fileName, char* _seperator);



// NOT USING
//void 			resetSequence(pngleAnim_t* _pngleAnim);
//bool 			PngSlideClose(pngleAnim_t* pngleAnim, int canvWidth, int canvHeight);
//int  			GetGrpImgCount();
//void 			resetFileList(char** fList);
// void 			SetSingleImage(const char* inputImg, int ind);
// void 			CloseList();

// FOR FUNCTION POINTERS FOR ImgList_t TYPE
//void            InitList();




#endif // END OF __PNGSLIDE_H__
