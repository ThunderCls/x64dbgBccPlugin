//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you

#pragma hdrstop
#pragma argsused

#include <vcl.h>
#include <windows.h>
#include "pluginmain.h"
#include "plugin.h"

// Variables
const char *szInfo = "BCC Plugin Sample";

int pluginHandle;
HWND hwndDlg;
int hMenu;
int hMenuDisasm;
int hMenuDump;
int hMenuStack;

/*====================================================================================
pluginit - Called by debugger when plugin.dp32 is loaded - needs to be EXPORTED

Arguments: initStruct - a pointer to a PLUG_INITSTRUCT structure

Notes:     you must fill in the pluginVersion, sdkVersion and pluginName members.
The pluginHandle is obtained from the same structure - it may be needed in
other function calls.

you can call your own setup routine from within this function to setup
menus and commands, and pass the initStruct parameter to this function.

--------------------------------------------------------------------------------------*/
PLUG_EXPORT bool __cdecl pluginit(PLUG_INITSTRUCT* initStruct)
{
    initStruct->pluginVersion = PLUGIN_VERSION;
    initStruct->sdkVersion = PLUG_SDKVERSION;
	strcpy(initStruct->pluginName, PLUGIN_NAME);
	pluginHandle = initStruct->pluginHandle;
    return pluginInit(initStruct);
}

/*====================================================================================
plugstop - Called by debugger when the plugin.dp32 is unloaded - needs to be EXPORTED

Arguments: none

Notes:     perform cleanup operations here, clearing menus and other housekeeping

--------------------------------------------------------------------------------------*/
PLUG_EXPORT bool __cdecl plugstop()
{
	return pluginStop();
}

/*====================================================================================
plugsetup - Called by debugger to initialize your plugins setup - needs to be EXPORTED

Arguments: setupStruct - a pointer to a PLUG_SETUPSTRUCT structure

Notes:     setupStruct contains useful handles for use within x64_dbg, mainly Qt
menu handles (which are not supported with win32 api) and the main window
handle with this information you can add your own menus and menu items
to an existing menu, or one of the predefined supported right click
context menus: hMenuDisam, hMenuDump & hMenuStack

plugsetup is called after pluginit.
--------------------------------------------------------------------------------------*/
PLUG_EXPORT void __cdecl plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
    hwndDlg = setupStruct->hwndDlg;
    hMenu = setupStruct->hMenu;
    hMenuDisasm = setupStruct->hMenuDisasm;
    hMenuDump = setupStruct->hMenuDump;
	hMenuStack = setupStruct->hMenuStack;

	GuiAddLogMessage(szInfo); // Add some info of the plugin to the log

	pluginSetup();
}

/*====================================================================================
CBINITDEBUG - Called by debugger when a program is debugged - needs to be EXPORTED

Arguments: cbType
cbInfo - a pointer to a PLUG_CB_INITDEBUG structure.
The szFileName item contains name of file being debugged.

--------------------------------------------------------------------------------------*/
PLUG_EXPORT void __cdecl CBINITDEBUG(CBTYPE cbType, PLUG_CB_INITDEBUG* info)
{
    _plugin_logprintf("[" PLUGIN_NAME "] Debugging of %s started!\n", info->szFileName);
}

PLUG_EXPORT void __cdecl CBSTOPDEBUG(CBTYPE cbType, PLUG_CB_STOPDEBUG* info)
{
    _plugin_logputs("[" PLUGIN_NAME "] Debugging stopped!");
}

PLUG_EXPORT void __cdecl CBEXCEPTION(CBTYPE cbType, PLUG_CB_EXCEPTION* info)
{
    _plugin_logprintf("[" PLUGIN_NAME "] ExceptionRecord.ExceptionCode: %08X\n", info->Exception->ExceptionRecord.ExceptionCode);
}

PLUG_EXPORT void __cdecl CBDEBUGEVENT(CBTYPE cbType, PLUG_CB_DEBUGEVENT* info)
{
    if(info->DebugEvent->dwDebugEventCode == EXCEPTION_DEBUG_EVENT)
    {
        _plugin_logprintf("[" PLUGIN_NAME "] DebugEvent->EXCEPTION_DEBUG_EVENT->%.8X\n", info->DebugEvent->u.Exception.ExceptionRecord.ExceptionCode);
    }
}
/*====================================================================================
CBSYSTEMBREAKPOINT - Called by debugger at system breakpoint - needs to be EXPORTED

Arguments: cbType
cbInfo - a pointer to a PLUG_CB_SYSTEMBREAKPOINT structure

--------------------------------------------------------------------------------------*/
PLUG_EXPORT void __cdecl CBSYSTEMBREAKPOINT(CBTYPE cbType, PLUG_CB_SYSTEMBREAKPOINT* cbInfo)
{
	_plugin_logputs("[" PLUGIN_NAME "] System breakpoint!");
}


/*====================================================================================
CBMENUENTRY - Called by debugger when a menu item is clicked - needs to be EXPORTED

Arguments: cbType
cbInfo - a pointer to a PLUG_CB_MENUENTRY structure. The hEntry contains
the resource id of menu item identifiers

Notes:     hEntry can be used to determine if the user has clicked on your plugins
menu item(s) and to do something in response to it.

--------------------------------------------------------------------------------------*/
PLUG_EXPORT void __cdecl CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
    switch(info->hEntry)
    {
    case MENU_TEST:
		DbgCmdExec("TestCommand");
		break;
		case MENU_ABOUT:
		MessageBox(hwndDlg, L"------------------------------------------------------\n"
							L"\t             [ BCC Plugin v1 ]\n"
							L"   Template for Borland C++ plugin development\n"
							L"                 Coded By: ThunderCls - 2016\n"
							L"               http://reversec0de.wordpress.com"
							L"\n------------------------------------------------------",
							L"About...", MB_ICONINFORMATION);
		break;
    default:
		break;
    }
}

/*====================================================================================
Main entry function for a DLL file  - required.
--------------------------------------------------------------------------------------*/
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}

