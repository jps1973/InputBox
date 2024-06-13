// InputBox.h

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
#define INPUT_BOX_WINDOW_CLASS_MENU_NAME											NULL

#define INPUT_BOX_WINDOW_EXTENDED_STYLE											WS_EX_CLIENTEDGE
#define INPUT_BOX_WINDOW_DEFAULT_TITLE											"Input Box"
#define INPUT_BOX_WINDOW_STYLE													WS_OVERLAPPEDWINDOW

#define INPUT_BOX_WINDOW_SEPARATOR_SIZE											10

#define INPUT_BOX_WINDOW_WIDTH													570
#define INPUT_BOX_WINDOW_HEIGHT													400

#define INPUT_BOX_EDIT_WINDOW_CLASS_NAME										WC_EDIT
#define INPUT_BOX_EDIT_WINDOW_EXTENDED_STYLE									0
#define INPUT_BOX_EDIT_WINDOW_STYLE												( WS_CHILD | WS_VISIBLE | WS_BORDER )

#define INPUT_BOX_BUTTON_WINDOW_CLASS_NAME										WC_BUTTON
#define INPUT_BOX_BUTTON_WINDOW_EXTENDED_STYLE									0
#define INPUT_BOX_BUTTON_WINDOW_STYLE											( WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER )

#define INPUT_BOX_BUTTON_WINDOW_WIDTH											50
#define INPUT_BOX_BUTTON_WINDOW_HEIGHT											25

#define INPUT_BOX_OK_BUTTON_WINDOW_TEXT											"OK"
#define INPUT_BOX_CANCEL_BUTTON_WINDOW_TEXT										"Cancel"

#define INPUT_BOX_OK_BUTTON_WINDOW_ID											WM_USER
#define INPUT_BOX_CANCEL_BUTTON_WINDOW_ID										( WM_USER + 1 )

#define UNABLE_TO_CREATE_INPUT_BOX_WINDOW_ERROR_MESSAGE							"Unable to create input box window"
#define UNABLE_TO_REGISTER_INPUT_BOX_WINDOW_CLASS_ERROR_MESSAGE					"Unable to register input box window class"

BOOL InputBox( HWND hWndParent, LPTSTR lpszInputText, LPCTSTR lpszTitle = INPUT_BOX_WINDOW_DEFAULT_TITLE );
