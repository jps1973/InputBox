// InputBoxDialog.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#include "InputBoxResource.h"

INT_PTR CALLBACK InputBoxDialogProcedure( HWND hWndDialog, UINT uMessage, WPARAM wParam, LPARAM lParam );

BOOL InputBoxDialogShow( HWND hWndParent, HINSTANCE hInstance, LPTSTR lpszInputText, LPCTSTR lpszPrompt );
