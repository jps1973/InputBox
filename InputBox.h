// InputBox.h

#pragma once

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#include "Registry.h"

#define INPUT_BOX_WINDOW_CLASS_NAME												"Main InputBox Window Class"

#define INPUT_BOX_WINDOW_CLASS_STYLE											0
#define INPUT_BOX_WINDOW_CLASS_ICON												LoadIcon( NULL, IDI_APPLICATION )
#define INPUT_BOX_WINDOW_CLASS_CURSOR											LoadCursor( NULL, IDC_ARROW )
#define INPUT_BOX_WINDOW_CLASS_BACKGROUND_COLOR									COLOR_WINDOW
#define INPUT_BOX_WINDOW_CLASS_BACKGROUND										( HBRUSH )( INPUT_BOX_WINDOW_CLASS_BACKGROUND_COLOR + 1 )
#define INPUT_BOX_WINDOW_CLASS_MENU_NAME											NULL

#define INPUT_BOX_WINDOW_EXTENDED_STYLE											( WS_EX_TOOLWINDOW | WS_EX_TOPMOST )
#define INPUT_BOX_WINDOW_DEFAULT_TITLE											"Input Box"
#define INPUT_BOX_WINDOW_STYLE													( WS_POPUP | WS_BORDER )

#define INPUT_BOX_WINDOW_SEPARATOR_SIZE											10

#define INPUT_BOX_WINDOW_DEFAULT_LEFT											100
#define INPUT_BOX_WINDOW_DEFAULT_TOP											100

// Note that input box window width and height are defined further down,
// as these are calculated from some of the following values

#define INPUT_BOX_TITLE_WINDOW_CLASS_NAME										WC_STATIC
#define INPUT_BOX_TITLE_WINDOW_EXTENDED_STYLE									0
#define INPUT_BOX_TITLE_WINDOW_STYLE											( WS_CHILD | WS_VISIBLE )
#define INPUT_BOX_TITLE_WINDOW_HEIGHT											13

#define INPUT_BOX_EDIT_WINDOW_CLASS_NAME										WC_EDIT
#define INPUT_BOX_EDIT_WINDOW_EXTENDED_STYLE									0
#define INPUT_BOX_EDIT_WINDOW_STYLE												( WS_CHILD | WS_VISIBLE | WS_BORDER )
#define INPUT_BOX_EDIT_WINDOW_HEIGHT											20

#define INPUT_BOX_BUTTON_WINDOW_CLASS_NAME										WC_BUTTON
#define INPUT_BOX_BUTTON_WINDOW_EXTENDED_STYLE									0
#define INPUT_BOX_BUTTON_WINDOW_STYLE											( WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER )

#define INPUT_BOX_BUTTON_WINDOW_WIDTH											50
#define INPUT_BOX_BUTTON_WINDOW_HEIGHT											20

#define INPUT_BOX_OK_BUTTON_WINDOW_TEXT											"OK"
#define INPUT_BOX_CANCEL_BUTTON_WINDOW_TEXT										"Cancel"

#define INPUT_BOX_OK_BUTTON_WINDOW_ID											WM_USER
#define INPUT_BOX_CANCEL_BUTTON_WINDOW_ID										( WM_USER + 1 )

#define INPUT_BOX_REGISTRY_TOP_LEVEL_KEY										HKEY_CURRENT_USER
#define INPUT_BOX_REGISTRY_SUB_KEY												"Software\\Jim Smith\\InputBox"
#define INPUT_BOX_REGISTRY_LEFT_VALUE_NAME										"Left"
#define INPUT_BOX_REGISTRY_TOP_VALUE_NAME										"Top"

#define INPUT_BOX_WINDOW_WIDTH													300
#define INPUT_BOX_WINDOW_HEIGHT													( WINDOW_BORDER_HEIGHT + INPUT_BOX_WINDOW_SEPARATOR_SIZE + INPUT_BOX_TITLE_WINDOW_HEIGHT + INPUT_BOX_WINDOW_SEPARATOR_SIZE + INPUT_BOX_EDIT_WINDOW_HEIGHT + INPUT_BOX_WINDOW_SEPARATOR_SIZE + INPUT_BOX_BUTTON_WINDOW_HEIGHT + INPUT_BOX_WINDOW_SEPARATOR_SIZE + WINDOW_BORDER_HEIGHT )

#define UNABLE_TO_CREATE_INPUT_BOX_WINDOW_ERROR_MESSAGE							"Unable to create input box window"
#define UNABLE_TO_REGISTER_INPUT_BOX_WINDOW_CLASS_ERROR_MESSAGE					"Unable to register input box window class"

BOOL InputBox( HWND hWndParent, LPTSTR lpszInputText, LPCTSTR lpszTitle = INPUT_BOX_WINDOW_DEFAULT_TITLE );
