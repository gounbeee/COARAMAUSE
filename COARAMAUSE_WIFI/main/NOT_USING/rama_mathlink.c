

#include "rama_mathlink.h"


// -----------------------------------------------------------------
// rama_mathlink_t IS A 'RELATIONSHIP' DATA OF MATHEMATICAL INFORMATION
// SO, BELOW IS ALL LINK-DATA OF INFORMATION 
// AND IT HAS THE LIMITATION WE CAN MAKE THAT IS 256 COUNTS
//
static rama_mathlink_t* g_rama_allMathLinks[RAMA_ALL_MATHLINSKS_MAX];


// -----------------------------------------------------------------
// CURRENTLY SELECTED UNIT(DEVICE) INDEX AND OTHERS
static rama_units_t* g_rama_currentUnits;


// -------------------------------------------------------------------------
// BELOW COULD BE THE RESULT AFTER WE CALCULATED MAIN + OTHER'S SCENE NUMBER
static rama_unitAndScene_t* g_rama_unitSceneResult;



void rama_init() {

	// INITIALIZING g_rama_allMathLinks
	int debug_mem = 0;
	
	for( int i=0; i < RAMA_ALL_MATHLINSKS_MAX; i++) {

		g_rama_allMathLinks[i] = (rama_mathlink_t*)malloc(sizeof(rama_mathlink_t));
		debug_mem += sizeof(*g_rama_allMathLinks[i]);

	}
	
	printf(" _+_+  sizeof(rama_mathlink_t) IS  --->>   %i   \r\n",  sizeof(rama_mathlink_t));				// SHOULD BE '40'
	printf(" _+_+  g_rama_allMathLinks IS CREATED !! sizeof(g_rama_allMathLinks[ ALL ACCUMULATED ]) IS  --->>   %i   \r\n", debug_mem);


	// CREATING 
	//g_rama_unitSceneResult = (rama_unitAndScene_t*)malloc(sizeof(rama_unitAndScene_t));





}




void rama_deinit() {


	for( int i=0; i < RAMA_ALL_MATHLINSKS_MAX; i++) {

		free(g_rama_allMathLinks[i]);
	}

	printf(" _+_+  g_rama_allMathLinks IS FREED !! sizeof(g_rama_allMathLinks) IS  --->>   %i   \r\n",  sizeof(g_rama_allMathLinks));

}




