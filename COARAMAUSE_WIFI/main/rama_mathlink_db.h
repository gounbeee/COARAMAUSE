

#ifndef RAMA_MATHLINK_DB
#define RAMA_MATHLINK_DB



#include <stddef.h>
#include <stdio.h>
#include "common_settings.h"



// THIS FILE IS DATABASE OF TABLE
// WHICH REPRESENTS THE RELATIONSHIPS BETWEEN MATHEMATICAL INFORMATION

#define RAMA_ALL_MATHLINSKS_MAX 256
#define RAMA_OTHERUNITS_MAX_IN_SINGLELINK OTHERUNITS_MAX_IN_SINGLELINK


// --------------------------------------
// < DEFINING  MULTI-DIMENSIONAL ARRAY >
// https://www.programiz.com/c-programming/c-multi-dimensional-arrays#:~:text=In%20C%20programming%2C%20you%20can,x%5B3%5D%5B4%5D%3B
extern const int g_rama_allMathRelations[ RAMA_ALL_MATHLINSKS_MAX ][ RAMA_OTHERUNITS_MAX_IN_SINGLELINK ] = {
	// SUBJECT INDEX 0
	{13, 12, 23, 14, 5, 6, 47, 18, 39},
	// SUBJECT INDEX 1
	{2, 3, 24, 5, 46, 7, 48, 9, 1},
	// SUBJECT INDEX 2
	{32, 24, 5, 6, 7, 38, 9, 14, 2}

	// ... TO 256 SUBJECTS

};





#endif