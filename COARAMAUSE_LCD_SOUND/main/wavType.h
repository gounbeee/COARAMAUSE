/*
 * MIT License
 *                    wavType
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





#ifndef __WAVTYPE_H__
#define __WAVTYPE_H__


#include <stdbool.h>





// BYTE OFFSET OF WAV FILE
#define WAV_T_RIFF_ID 						0
#define WAV_T_RIFF_SIZE 					4
#define WAV_T_RIFF_FORMAT 					8
#define WAV_T_FORMAT_ID 					12
#define WAV_T_FORMAT_CHUNKSIZE 				16
#define WAV_T_FORMAT_TYPE					20
#define WAV_T_FORMAT_CHANNELS 				22
#define WAV_T_FORMAT_SAMPLERATE 			24
#define WAV_T_FORMAT_BYTERATE 				28
#define WAV_T_FORMAT_BLOCKALIGN 			32
#define WAV_T_FORMAT_BITSPERSAMPLE 			34
#define WAV_T_DATA_ID 						36
#define WAV_T_DATA_DATASIZE 				40
#define WAV_T_DATA_BLOCK					44


// DATA SIZE
#define WAV_T_RIFF_ID_SIZE 					4
#define WAV_T_RIFF_SIZE_SIZE				4
#define WAV_T_RIFF_FORMAT_SIZE				4
#define WAV_T_FORMAT_ID_SIZE 				4
#define WAV_T_FORMAT_CHUNKSIZE_SIZE 		4
#define WAV_T_FORMAT_TYPE_SIZE 				2
#define WAV_T_FORMAT_CHANNELS_SIZE 			2
#define WAV_T_FORMAT_SAMPLERATE_SIZE 		4
#define WAV_T_FORMAT_BYTERATE_SIZE 			4
#define WAV_T_FORMAT_BLOCKALIGN_SIZE 		2
#define WAV_T_FORMAT_BITSPERSAMPLE_SIZE 	2
#define WAV_T_DATA_ID_SIZE 					4
#define WAV_T_DATA_DATASIZE_SIZE 			4




//#define WAV_T_DATA_MAXIMUM_SIZE 		104857600 			// 100 MB IS LIMIT



#define BUFFER_SAMPLE_LENGTH 				8192				// 256 SAMPLES FOR SINGLE CHANNEL SAMPLE, 128 SAMPLES FOR STEREO CHANNEL




// < FORMAT OF WAV FILE >
// https://www.youtube.com/watch?v=cnBDMpMSeQI&t=72s
// https://docs.fileformat.com/audio/wav/
// https://en.wikipedia.org/wiki/WAV

typedef struct {

	char			riff_id[WAV_T_RIFF_ID_SIZE];				// Marks the file as a riff file. Characters are each 1 byte long.   // “RIFF”
	int 			riff_size;									// Size of the overall file - 8 bytes, in bytes (32-bit integer). Typically, you’d fill this in after creation.  // File size (integer)
	char 			riff_format[WAV_T_RIFF_FORMAT_SIZE];		// File Type Header. For our purposes, it always equals “WAVE”.      // “WAVE”
	char 			format_id[WAV_T_FORMAT_ID_SIZE];			// Format chunk marker. Includes trailing null	                     //  “fmt "
	int 			format_chunksize;							// Length of format data as listed above  						     // 16
	short			format_type;								// Type of format (1 is PCM) - 2 byte integer  						 //  1
	short			format_channels;							// Number of Channels - 2 byte integer								 //  2
	unsigned int  	format_samplerate;							// Sample Rate - 32 byte integer. Common values are 44100 (CD), 48000 (DAT). Sample Rate = Number of Samples per second, or Hertz.  //  44100
	unsigned int 	format_byterate;							// (Sample Rate * BitsPerSample * Channels) / 8.  					 //  176400
	short 		 	format_blockalign;							// (BitsPerSample * Channels) / 8.1 - 8 bit mono2 - 8 bit stereo/16 bit mono4 - 16 bit stereo  //  4
	short			format_bitspersample;						// Bits per sample  												 //  16
	char  			data_id[WAV_T_DATA_ID_SIZE];				// “data” chunk header. Marks the beginning of the data section.  	 // “data”
	unsigned int   	data_size;									// Size of the data section.  										 // IT DEPENDS.

																// ****  Sample values are given above for a 16-bit stereo source.  ****


	FILE* 			fileStruct;									// FILE POINTER
    size_t          readStatus;

	unsigned long 	playCursor;									// INCREMENTAL VALUE TO INDICATE THE LOCATION WHERE WE ARE PLAYING



} WavType_t;



typedef struct {


	uint16_t		buffer[BUFFER_SAMPLE_LENGTH];
	int  			bufferLength;


} WavType_Data_t;






void InitWavStructFromFile(FILE* wavFile, WavType_t* wavTypeHnd);
void DumpWavStruct(WavType_t* wavTypeHnd );
WavType_Data_t* GetCurrentBuffer(WavType_t* wavTypeHnd);
WavType_Data_t* GetNextBuffer(WavType_t* wavTypeHnd);
WavType_Data_t* ResetBuffer(WavType_t* wavTypeHnd);
bool IsEndOfFile(WavType_t* wavTypeHnd);
size_t GetFreadReturned(WavType_t* wavTypeHnd);






#endif