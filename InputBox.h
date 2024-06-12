// InputBox.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#define INPUT_BOX_WINDOW_CLASS_NAME												"Main InputBox Window Class"

#define INPUT_BOX_WINDOW_CLASS_STYLE											0
#define INPUT_BOX_WINDOW_CLASS_ICON												LoadIcon( NULL, IDI_APPLICATION )
#define INPUT_BOX_WINDOW_CLASS_CURSOR											LoadCursor( NULL, IDC_ARROW )
#define INPUT_BOX_WINDOW_CLASS_BACKGROUND										( HBRUSH )( COLOR_WINDOW + 1 )
#define INPUT_BOX_WINDOW_CLASS_MENU_NAME											NULL

#define INPUT_BOX_WINDOW_EXTENDED_STYLE											WS_EX_CLIENTEDGE
#define INPUT_BOX_WINDOW_DEFAULT_TITLE											"InputBox"
#define INPUT_BOX_WINDOW_STYLE													WS_OVERLAPPEDWINDOW

#define UNABLE_TO_CREATE_INPUT_BOX_WINDOW_ERROR_MESSAGE							"Unable to create input box window"
#define UNABLE_TO_REGISTER_INPUT_BOX_WINDOW_CLASS_ERROR_MESSAGE					"Unable to register input box window class"

BOOL InputBox(HWND hWndParent, LPTSTR lpszInputText, LPCTSTR lpszTitle = INPUT_BOX_WINDOW_DEFAULT_TITLE );
