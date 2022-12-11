#ifndef RAMA_MATHLINK_H
#define RAMA_MATHLINK_H




#include <stddef.h>
#include <stdio.h>
#include "rama_mathlink_db.h"








// ---------------------------------------------------
// CURRENT CENTER UNIT AND OTHER UNIT'S "INDEX" NUMBER
// **** THIS IS THE [INDEX NUMBER] OF UNIT ****
//
// ex> IF WE CHOOSE INDEX [2] AS A ACCESS POINT,
//     OTHERS COULD BE [ 0,1,2,4,5,6,7,8,9 ]
//
typedef struct rama_units {

	int mainUnitNum;
	int otherUnitNums[RAMA_OTHERUNITS_MAX_IN_SINGLELINK];

} rama_units_t;



// -------------------------------------------------------------------
// TYPE FOR BANDING SINGLE UNIT'S NUMBER AND ANIMTION SCENE TO DISPLAY
// THIS IS FOR RESULT BEFORE SEND TO THE OTHER MODULE
//
// ex> unitNumber  :: INDEX NUMBER OF DEVICE UNIT
//     sceneNumber :: SCENE NUMBER OF ANIMATION SCENE TO DISPLAY
//
typedef struct rama_unitAndScene {

	int unitNumber;
	int sceneNumber;

} rama_unitAndScene_t;





// -------------------------------------------------------------------
// LINK DATA OF MATH INFORMATION
//
//
// ex> mainSceneNumber  :: MAIN ANIMATION SCENE NUMBER WHICH CAN BE "SUBJECT" LIKE 1, 2, OR 384...
//     otherSceneNums   :: LINKED SCENE NUMBER OF ANIMATION LIKE [3, 56, 77, 22, 45, 87, 24, 5, 33] **** 9 ELEMENTS **** 
//															      1  2   3   4   5   6   7   8  9th
//
typedef struct rama_mathlink {
	// MAIN MATH INFORMATION
	int mainSceneNumber;

	// LINKED INFORMATION FROM ABOVE
	int otherSceneNums[RAMA_OTHERUNITS_MAX_IN_SINGLELINK];

} rama_mathlink_t;







void rama_init();

// void rama_setLinkMain(rama_link_t* link, int num);
// void rama_setLinkOthers(rama_link_t* link, int[] links);

// rama_link_t* rama_getLink(int mainUnitNum);



void rama_deinit();











#endif