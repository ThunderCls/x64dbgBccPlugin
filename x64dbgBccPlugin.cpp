#include "plugin.h"
#include "dll_link.h"
#include <vcl.h>

//---------------------------------------------------------------------------
/* global functions pointers */
//---------------------------------------------------------------------------
_DebugSetBreakpoint DebugSetBreakpoint;
_DebugDeleteBreakpoint DebugDeleteBreakpoint;
//---------------------------------------------------------------------------

bool cbTestCommand(int argc, char* argv[])
{
	_plugin_logputs("[" PLUGIN_NAME "] Test command!");
	char line[GUI_MAX_LINE_SIZE] = "";
	if(!GuiGetLineWindow("test", line))
		_plugin_logputs("[" PLUGIN_NAME "] Cancel pressed!");
	else
		_plugin_logprintf("[" PLUGIN_NAME "] Line: \"%s\"\n", line);

	return true;
}
//---------------------------------------------------------------------------

bool cbTestSetBreakpoints(int argc, char* argv[])
{
	// Populate function pointers from x32dbg.dll
	GetDllFunctions();

	_plugin_logputs("[" PLUGIN_NAME "] Set Breakpoint test command!");
	char line[GUI_MAX_LINE_SIZE] = "";
	if(!GuiGetLineWindow("test", line))
		_plugin_logputs("[" PLUGIN_NAME "] Cancel pressed!");
	else
	{
		if(DebugSetBreakpoint)
		{
			// Call the function through the function pointer
			DebugSetBreakpoint(StrToInt("0x" + String(line)));
			_plugin_logputs("[" PLUGIN_NAME "] BP setted successfully!");
		}
		else
		{
			_plugin_logputs("[" PLUGIN_NAME "] Error loading DLL function!");
		}
	}
}
//---------------------------------------------------------------------------

bool cbTestDelBreakpoints(int argc, char* argv[])
{
	// Populate function pointers from x32dbg.dll
	GetDllFunctions();

	_plugin_logputs("[" PLUGIN_NAME "] Delete Breakpoint test command!");
	char line[GUI_MAX_LINE_SIZE] = "";
	if(!GuiGetLineWindow("test", line))
		_plugin_logputs("[" PLUGIN_NAME "] Cancel pressed!");
	else
	{
		if(DebugDeleteBreakpoint)
		{
			// Call the function through the function pointer
			DebugDeleteBreakpoint(StrToInt("0x" + String(line)));
			_plugin_logputs("[" PLUGIN_NAME "] BP deleted successfully!");
		}
		else
		{
			_plugin_logputs("[" PLUGIN_NAME "] Error loading DLL function!");
		}
	}
}
//---------------------------------------------------------------------------
