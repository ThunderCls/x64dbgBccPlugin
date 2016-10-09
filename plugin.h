#pragma once
#include "pluginmain.h"

//---------------------------------------------------------------------------

// variables
enum
{
	MENU_TEST,
	MENU_SETBP,
	MENU_DELBP,
	MENU_ABOUT,
};

//functions
bool pluginInit(PLUG_INITSTRUCT* initStruct);
bool pluginStop();
void pluginSetup();
