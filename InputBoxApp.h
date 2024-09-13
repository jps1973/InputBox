// InputBoxApp.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#include "InputBox.h"

#define INPUT_BOX_WINDOW_CLASS_NAME												"Main InputBox Window Class"

#define INPUT_BOX_WINDOW_CLASS_STYLE											0
#define INPUT_BOX_WINDOW_CLASS_ICON												LoadIcon( NULL, IDI_APPLICATION )
#define INPUT_BOX_WINDOW_CLASS_CURSOR											LoadCursor( NULL, IDC_ARROW )
#define INPUT_BOX_WINDOW_CLASS_BACKGROUND										( HBRUSH )( COLOR_WINDOW + 1 )
#define INPUT_BOX_WINDOW_CLASS_MENU_NAME										NULL

#define INPUT_BOX_WINDOW_EXTENDED_STYLE											WS_EX_CLIENTEDGE
#define INPUT_BOX_WINDOW_TITLE													"InputBox"
#define INPUT_BOX_WINDOW_STYLE													WS_OVERLAPPEDWINDOW

#define INPUT_BOX_WINDOW_MINIMUM_WIDTH											500
#define INPUT_BOX_WINDOW_MINIMUM_HEIGHT											400

#define STRING_LENGTH															2048

#define ABOUT_MESSAGE_CAPTION													"About"
#define INFORMATION_MESSAGE_CAPTION												"Information"
#define ERROR_MESSAGE_CAPTION													"Error"
#define WARNING_MESSAGE_CAPTION													"Warning"

#define UNABLE_TO_CREATE_INPUT_BOX_WINDOW_ERROR_MESSAGE							"Unable to create main window"
#define UNABLE_TO_REGISTER_INPUT_BOX_WINDOW_CLASS_ERROR_MESSAGE					"Unable to register main window class"
