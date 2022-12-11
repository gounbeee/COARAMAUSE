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




#include <string.h>
#include <stdio.h>


#include "wavType.h"


// ---------------------
// < PARSING WAV FILE >
// http://truelogic.org/wordpress/2015/09/04/parsing-a-wav-file-in-c/
// https://topic.alibabacloud.com/a/c-language-parsing-wav-audio-files_1_31_30000716.html
// http://www.cs.columbia.edu/~hgs/research/projects/rtsp_cinema/rtspd-1.0-20000514/rtspd/wav.c

// < VALIDATION IS CRITICAL !!!! >
// https://stackoverflow.com/questions/33885897/working-with-fread-and-fseek




	//TODO   https://stackoverflow.com/questions/63747291/reading-a-wav-file-returns-0-bytes







// < GETTING SAMPLE >
// BECAUSE We ARE USING STEREO-SAMPLE,
// SO " FF FF " " EE EE "
//      LEFT      RIGHT
//      1  2      3  4      (byte)
//      ---------------
//            |
//         1  SAMPLE
//
// SO, 16 bit DATA CAN COVER "SINGLE CHANNEL" OF 1 SAMPLE DATA
//static uint16_t* s_buff_wav_t_data;				



static WavType_Data_t* s_sample_export;




void InitWavStructFromFile(FILE* wavFile, WavType_t* wavTypeHnd) {



    if (wavFile == NULL) {

        printf("^^^^^^^^^^^ Cannot open file \n");
        
        //vTaskDelay(10000 / portTICK_PERIOD_MS);
    }


    // When fgets actually reads input from the user, it will read up to size - 1 characters 
    // and then place the null terminator after the last character it read. fgets will read input 
    // until it either has no more room to store the data or until the user hits enter. 
    // Notice that fgets may fill up the entire space allocated for str, but it will never 
    // return a non-null terminated string to you.

  
  	// SETTING SEARCHING CURSOR
  	char buff_wav_t_riff_id[WAV_T_RIFF_ID_SIZE];
    fseek(wavFile, 		WAV_T_RIFF_ID,   									SEEK_SET);
    fgets(buff_wav_t_riff_id, 		WAV_T_RIFF_ID_SIZE+1, 					wavFile);
    sprintf(wavTypeHnd->riff_id, "%s", buff_wav_t_riff_id);


    // ----------------------------------------------
    // < GETTING INTEGER VALUE FROM FILE READING >
    // https://fresh2refresh.com/c-programming/c-file-handling/getw-putw-functions-c/
    // 
    fseek(wavFile, 		WAV_T_RIFF_SIZE, 									SEEK_SET);
    wavTypeHnd->riff_size = getw(wavFile);


    char buff_wav_t_riff_format[WAV_T_RIFF_FORMAT_SIZE];
    fseek(wavFile, 		WAV_T_RIFF_FORMAT, 									SEEK_SET);
    fgets(buff_wav_t_riff_format, 		WAV_T_RIFF_FORMAT_SIZE+1, 				wavFile);
    sprintf(wavTypeHnd->riff_format, "%s", buff_wav_t_riff_format);


    char buff_wav_t_format_id[WAV_T_FORMAT_ID_SIZE];
    fseek(wavFile, 		WAV_T_FORMAT_ID, 									SEEK_SET);
    fgets(buff_wav_t_format_id, 		WAV_T_FORMAT_ID_SIZE+1, 					wavFile);
    sprintf(wavTypeHnd->format_id, "%s", buff_wav_t_format_id);


    fseek(wavFile, 		WAV_T_FORMAT_CHUNKSIZE, 									SEEK_SET);
    wavTypeHnd->format_chunksize = getw(wavFile);


    fseek(wavFile, 		WAV_T_FORMAT_TYPE, 									SEEK_SET);
    wavTypeHnd->format_type = getw(wavFile);


    fseek(wavFile, 		WAV_T_FORMAT_CHANNELS, 										SEEK_SET);
    wavTypeHnd->format_channels = getw(wavFile);


    fseek(wavFile, 		WAV_T_FORMAT_SAMPLERATE, 										SEEK_SET);
    wavTypeHnd->format_samplerate = getw(wavFile);


    fseek(wavFile, 		WAV_T_FORMAT_BYTERATE, 										SEEK_SET);
    wavTypeHnd->format_byterate = getw(wavFile);


    fseek(wavFile, 		WAV_T_FORMAT_BLOCKALIGN, 										SEEK_SET);
    wavTypeHnd->format_blockalign = getw(wavFile);


    fseek(wavFile, 		WAV_T_FORMAT_BITSPERSAMPLE, 										SEEK_SET);
    wavTypeHnd->format_bitspersample = getw(wavFile);


    char buff_wav_t_data_id[WAV_T_DATA_ID_SIZE];
    fseek(wavFile, 		WAV_T_DATA_ID, 										SEEK_SET);
    fgets(buff_wav_t_data_id, 		WAV_T_DATA_ID_SIZE+1, 					wavFile);
    sprintf(wavTypeHnd->data_id, "%s", buff_wav_t_data_id);



    fseek(wavFile, 		WAV_T_DATA_DATASIZE, 										SEEK_SET);
    wavTypeHnd->data_size = getw(wavFile);


    // STORING WAVE FILE POINTER
    wavTypeHnd->fileStruct = wavFile;


    // INITIALIZE CURSOR FOR PLAYBACK
    // UNSIGNED LONG INTEGER TYPE
    wavTypeHnd->playCursor = 0;




    s_sample_export = calloc(1, sizeof(WavType_Data_t));



}




WavType_Data_t* ResetBuffer(WavType_t* wavTypeHnd) {
	// RESET CURSOR
	wavTypeHnd->playCursor = 0;

    return GetCurrentBuffer(wavTypeHnd);

}



WavType_Data_t* GetNextBuffer(WavType_t* wavTypeHnd) {

	// CURSOR WILL JUMP TO NEXT POSITION AMOUNT OF < BUFFER_SAMPLE_LENGTH >
	wavTypeHnd->playCursor += BUFFER_SAMPLE_LENGTH;

	return GetCurrentBuffer(wavTypeHnd);

}


bool IsEndOfFile(WavType_t* wavTypeHnd) {

    bool result = false;

    if (wavTypeHnd->readStatus == EOF) {        

        if (feof(wavTypeHnd->fileStruct)) {                                                 
           printf("FILE ENDED !!!! \n");                                              
           result = true;             

        } else {            

           printf("FILE COULD NOT ENDED !!!! \n");                                               
           result = false;
        }
    }


    return result;


}


size_t GetFreadReturned(WavType_t* wavTypeHnd) {

    return wavTypeHnd->readStatus;

}


WavType_Data_t* GetCurrentBuffer(WavType_t* wavTypeHnd) {
	

    // WE CAN USE fseek AND fread !!!!
    fseek(wavTypeHnd->fileStruct, 
    	WAV_T_DATA_BLOCK + wavTypeHnd->playCursor, 					// ADDING CURSOR LOCATION
    	SEEK_SET);


	//size_t ret_code = fread(s_buff_wav_t_data, 		sizeof(*s_buff_wav_t_data),        BUFFER_SAMPLE_LENGTH, 					wavTypeHnd->fileStruct);

	
	wavTypeHnd->readStatus = fread(s_sample_export->buffer,
		sizeof(uint16_t),
		BUFFER_SAMPLE_LENGTH,
		wavTypeHnd->fileStruct);


	//printf("****  ret_code:     %d \n", ret_code);



	if(wavTypeHnd->readStatus == BUFFER_SAMPLE_LENGTH) {

        //printf("****  Array read successfully, FIRST  5  of contents: ");

        //for(int n = 0; n < 5; n++) printf("%02x ", s_sample_export->buffer[n]);
        //for(int n = 0; n < 5; ++n) printf("%02x ", s_buff_wav_t_data[n]);
        //printf("\n");


    	s_sample_export->bufferLength = BUFFER_SAMPLE_LENGTH;


    } else { // error handling

       if (feof(wavTypeHnd->fileStruct))
           printf("*----------  Error reading wavFile: unexpected end of file\n");
       else if (ferror(wavTypeHnd->fileStruct)) {
           perror("*----------  Error reading wavFile");
       }


       s_sample_export->bufferLength = -1;

    }




	// FOR DEBUG
	//
	// -----------------------------------------------------
	// < PRINT OUT HEX DECIMAL FROM BINARY-READ FILE !!!! >
	// https://stackoverflow.com/questions/49242874/how-to-print-contents-of-buffer-in-c

	// for (int i=0; i < 512; i++) {
	//     printf("%02x ", s_buff_wav_t_data[i]);

	//     if ((i+1)%16 == 0) printf("\n");

	// }

	// WILL PRINT LIKE BELOWS...
	// 52 49 46 46 1e 00 09 00 57 41 56 45 66 6d 74 20 
	// 10 00 00 00 01 00 01 00 44 ac 00 00 88 58 01 00 
	// 02 00 10 00 64 61 74 61 fa ff 08 00 00 00 00 00 


	return s_sample_export;

}




void DumpWavStruct(WavType_t* wavTypeHnd ) {

	printf("wavTypeHnd->riff_id 						==  %s \n"		, wavTypeHnd->riff_id				);    		
	printf("wavTypeHnd->riff_size 						==  %d \n"		, wavTypeHnd->riff_size   			);    
	printf("wavTypeHnd->riff_format 					==  %s \n"  	, wavTypeHnd->riff_format			);    	
	printf("wavTypeHnd->format_id 						==  %s \n"		, wavTypeHnd->format_id				);    
	printf("wavTypeHnd->format_chunksize 						==  %d \n"		, wavTypeHnd->format_chunksize    	);    
	printf("wavTypeHnd->format_type 					==  %d \n"		, wavTypeHnd->format_type 			);    
	printf("wavTypeHnd->format_channels 						==  %d \n"		, wavTypeHnd->format_channels 		);    
	printf("wavTypeHnd->format_samplerate 						==  %u \n"		, wavTypeHnd->format_samplerate 	);    	
	printf("wavTypeHnd->format_byterate 						==  %u \n"		, wavTypeHnd->format_byterate 		);    
	printf("wavTypeHnd->format_blockalign 						==  %d \n"		, wavTypeHnd->format_blockalign 	);    
	printf("wavTypeHnd->format_bitspersample 					==  %d \n"		, wavTypeHnd->format_bitspersample	);    
	printf("wavTypeHnd->data_id 						==  %s \n"		, wavTypeHnd->data_id 				);    
	printf("wavTypeHnd->data_size 						==  %u \n"		, wavTypeHnd->data_size 			);    	
	//printf("wavTypeHnd->data 			 				==  %s \n"		, wavTypeHnd->data 			);    	

	printf("sizeof -- 	wavTypeHnd->riff_id	    		 		==  %d bytes \n"		, sizeof( wavTypeHnd->riff_id				) );    		
	printf("sizeof -- 	wavTypeHnd->riff_size   		 		==  %d bytes \n"		, sizeof( wavTypeHnd->riff_size   			) );    
	printf("sizeof -- 	wavTypeHnd->riff_format			 		==  %d bytes \n"  	, sizeof( wavTypeHnd->riff_format			) );    	
	printf("sizeof -- 	wavTypeHnd->format_id			 		==  %d bytes \n"		, sizeof( wavTypeHnd->format_id				) );    
	printf("sizeof -- 	wavTypeHnd->format_chunksize     				==  %d bytes \n"		, sizeof( wavTypeHnd->format_chunksize    	) );    
	printf("sizeof -- 	wavTypeHnd->format_type 		 		==  %d bytes \n"		, sizeof( wavTypeHnd->format_type 			) );    
	printf("sizeof -- 	wavTypeHnd->format_channels 	 				==  %d bytes \n"		, sizeof( wavTypeHnd->format_channels 		) );    
	printf("sizeof -- 	wavTypeHnd->format_samplerate 	 				==  %d bytes \n"		, sizeof( wavTypeHnd->format_samplerate 	) );    	
	printf("sizeof -- 	wavTypeHnd->format_byterate 	 				==  %d bytes \n"		, sizeof( wavTypeHnd->format_byterate 		) );    
	printf("sizeof -- 	wavTypeHnd->format_blockalign 	 				==  %d bytes \n"		, sizeof( wavTypeHnd->format_blockalign 	) );    
	printf("sizeof -- 	wavTypeHnd->format_bitspersample 				==  %d bytes \n"		, sizeof( wavTypeHnd->format_bitspersample	) );    
	printf("sizeof -- 	wavTypeHnd->data_id 			 		==  %d bytes \n"		, sizeof( wavTypeHnd->data_id 				) );    
	printf("sizeof -- 	wavTypeHnd->data_size 			 		==  %d bytes \n"		, sizeof( wavTypeHnd->data_size 			) );    


}



