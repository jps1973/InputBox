// InputBoxDialog.cpp

#include "InputBoxDialog.h"

// Global variables
static LPTSTR g_lpszInputText;
static LPTSTR g_lpszPrompt;

INT_PTR CALLBACK InputBoxDialogProcedure( HWND hWndDialog, UINT uMessage, WPARAM wParam, LPARAM )
{
	BOOL bResult = FALSE;

	// Select message
	switch( uMessage )
	{
		case WM_INITDIALOG:
		{
			// An init dialog message

			// Update dialog items
			SetDlgItemText( hWndDialog, IDC_INPUT_BOX_EDIT,		g_lpszInputText );
			SetDlgItemText( hWndDialog, IDC_INPUT_BOX_PROMPT,	g_lpszPrompt );

			// Select input text
			SendDlgItemMessage( hWndDialog, IDC_INPUT_BOX_EDIT, EM_SETSEL, ( WPARAM )0, ( LPARAM )-1 );

			// Update return value
			bResult = TRUE;

			// Break out of switch
			break;

		} // End of an init dialog message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case IDOK:
				{
					// An ok command

					// Update global input text
					GetDlgItemText( hWndDialog, IDC_INPUT_BOX_EDIT, g_lpszInputText, STRING_LENGTH );

					// Update return value
					bResult = TRUE;

					// End dialog with ok
					EndDialog( hWndDialog, IDOK );

					// Break out of switch
					break;

				} // End of an ok command
				case IDCANCEL:
				{
					// A cancel command

					// Update return value
					bResult = TRUE;

					// End dialog with cancel
					EndDialog( hWndDialog, IDCANCEL );

					// Break out of switch
					break;

				} // End of a cancel command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of an init dialog message
		default:
		{
			// Default message

			// Break out of switch
			break;

		} // End of default message

		return FALSE;

	}; // End of selection for message

	return bResult;

} // End of function InputBoxDialogProcedure

BOOL InputBoxDialogShow( HWND hWndParent, HINSTANCE hInstance, LPTSTR lpszInputText, LPCTSTR lpszPrompt )
{
	BOOL bResult = FALSE;

	// Allocate global memory
	g_lpszInputText	= new char[ STRING_LENGTH + sizeof( char ) ];
	g_lpszPrompt	= new char[ STRING_LENGTH + sizeof( char ) ];

	// Store global strings
	lstrcpy( g_lpszInputText,	lpszInputText );
	lstrcpy( g_lpszPrompt,		lpszPrompt );

	// Show input box dialog
	if( DialogBox( hInstance, MAKEINTRESOURCE( IDD_INPUT_BOX ), hWndParent, InputBoxDialogProcedure ) == IDOK )
	{
		// Successfully input some text

		// Update input text parameter
		lstrcpy( lpszInputText, g_lpszInputText );

		// Update return value
		bResult = TRUE;

	} // End of successfully input some text

	// Free global memory
	delete [] g_lpszInputText;
	delete [] g_lpszPrompt;

	return bResult;

} // End of function InputBoxDialogShow
