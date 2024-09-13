// InputBoxApp.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define INPUT_BOX_WINDOW_CLASS_NAME												"Main InputBox Window Class"

#define INPUT_BOX_WINDOW_CLASS_STYLE											0
#define INPUT_BOX_WINDOW_CLASS_ICON												LoadIcon( NULL, IDI_APPLICATION )
#define INPUT_BOX_WINDOW_CLASS_CURSOR											LoadCursor( NULL, IDC_ARROW )
#define INPUT_BOX_WINDOW_CLASS_BACKGROUND										( HBRUSH )( COLOR_WINDOW + 1 )
#define INPUT_BOX_WINDOW_CLASS_MENU_NAME										NULL

#define INPUT_BOX_WINDOW_EXTENDED_STYLE											WS_EX_CLIENTEDGE
#define INPUT_BOX_WINDOW_STYLE													WS_OVERLAPPEDWINDOW

#define INPUT_BOX_WINDOW_WIDTH													500
#define INPUT_BOX_WINDOW_HEIGHT													200
#define INPUT_BOX_WINDOW_BORDER_SIZE											8

#define INPUT_BOX_EDIT_WINDOW_CLASS_NAME										WC_EDIT
#define INPUT_BOX_EDIT_WINDOW_EXTENDED_STYLE									0
#define INPUT_BOX_EDIT_WINDOW_STYLE												( WS_CHILD | WS_VISIBLE | WS_BORDER )
#define INPUT_BOX_EDIT_WINDOW_HEIGHT											20

#define INPUT_BOX_BUTTON_WINDOW_CLASS_NAME										WC_BUTTON
#define INPUT_BOX_BUTTON_WINDOW_EXTENDED_STYLE									0
#define INPUT_BOX_BUTTON_WINDOW_TITLE											"InputBox"
#define INPUT_BOX_BUTTON_WINDOW_STYLE											( WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT | BS_VCENTER )
#define INPUT_BOX_BUTTON_WINDOW_WIDTH											50
#define INPUT_BOX_BUTTON_WINDOW_HEIGHT											25

#define INPUT_BOX_WINDOW_UNABLE_TO_CREATE_ERROR_MESSAGE							"Unable to create main window"
#define INPUT_BOX_WINDOW_UNABLE_TO_REGISTER_CLASS_ERROR_MESSAGE					"Unable to register main window class"

BOOL InputBox( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszTitle, LPTSTR lpszInputText );
