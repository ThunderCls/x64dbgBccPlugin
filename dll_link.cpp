#include "dll_link.h"
#include <windows.h>

//---------------------------------------------------------------------------

void GetDllFunctions()
{
//	*(FARPROC*)&DebugSetBreakpoint = GetProcAddress(GetModuleHandle(x32dbg_module),
//																	"?SetBreakpoint@Debug@Script@@YA_NK@Z");
//	*(FARPROC*)&DebugDeleteBreakpoint = GetProcAddress(GetModuleHandle(x32dbg_module),
//																	"?DeleteBreakpoint@Debug@Script@@YA_NK@Z");
	DebugSetBreakpoint = (_DebugSetBreakpoint)GetProcAddress(GetModuleHandle(x32dbg_module),
																			 "?SetBreakpoint@Debug@Script@@YA_NK@Z");
	DebugDeleteBreakpoint = (_DebugDeleteBreakpoint)GetProcAddress(GetModuleHandle(x32dbg_module),
																				   "?DeleteBreakpoint@Debug@Script@@YA_NK@Z");
}

