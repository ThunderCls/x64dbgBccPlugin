#include "plugin.h"
#include <windows.h>

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