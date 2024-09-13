// InputBoxApp.cpp

#include "InputBox.h"

// Global variables
static HWND g_hWndEdit;
static HWND g_hWndGoButton;
static HWND g_hWndCancelButton;
static HINSTANCE g_hInstance;
static LPTSTR g_lpszInputText;

// Input box window procedure
LRESULT CALLBACK InputBoxWndProc( HWND hWndInputBox, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message
			int nEditWindowWidth;

			// Calculate edit window size
			nEditWindowWidth = ( INPUT_BOX_WINDOW_WIDTH - ( INPUT_BOX_WINDOW_BORDER_SIZE + INPUT_BOX_WINDOW_BORDER_SIZE ) );

			// Create edit window
			g_hWndEdit = CreateWindowEx( INPUT_BOX_EDIT_WINDOW_EXTENDED_STYLE, INPUT_BOX_EDIT_WINDOW_CLASS_NAME, g_lpszInputText, INPUT_BOX_EDIT_WINDOW_STYLE, INPUT_BOX_WINDOW_BORDER_SIZE, INPUT_BOX_WINDOW_BORDER_SIZE, nEditWindowWidth, INPUT_BOX_EDIT_WINDOW_HEIGHT, hWndInputBox, ( HMENU )NULL, g_hInstance, NULL );
			
			// Ensure that edit window was created
			if( g_hWndEdit )
			{
				// Successfully created edit window
				HFONT hFont;

				// Get font
				hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

				// Set edit window font
				SendMessage( g_hWndEdit, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

			} // End of successfully created edit window

			// Break out of switch
			break;

		} // End of a create message
		case WM_ACTIVATE:
		{
			// An activate message

			// Break out of switch
			break;

		} // End of an activate message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				default:
				{
					// Default command

					// Source window is ( HWND )lParam

					// Call default procedure
					lr = DefWindowProc( hWndInputBox, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of a command message
		case WM_CLOSE:
		{
			// A close message

			// Destroy input box window
			DestroyWindow( hWndInputBox );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lr = DefWindowProc( hWndInputBox, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function InputBoxWndProc

BOOL InputBox( HWND hWndParent, HINSTANCE hInstance, LPCTSTR lpszTitle, LPTSTR lpszInputText )
{
	BOOL bResult = FALSE;

	WNDCLASSEX wcInputBox;

	// Clear input box window class structure
	ZeroMemory( &wcInputBox, sizeof( wcInputBox ) );

	// Initialise input box window class structure
	wcInputBox.cbSize			= sizeof( WNDCLASSEX );
	wcInputBox.lpfnWndProc		= InputBoxWndProc;
	wcInputBox.hInstance		= hInstance;
	wcInputBox.lpszClassName	= INPUT_BOX_WINDOW_CLASS_NAME;
	wcInputBox.style			= INPUT_BOX_WINDOW_CLASS_STYLE;
	wcInputBox.hIcon			= INPUT_BOX_WINDOW_CLASS_ICON;
	wcInputBox.hCursor			= INPUT_BOX_WINDOW_CLASS_CURSOR;
	wcInputBox.hbrBackground	= INPUT_BOX_WINDOW_CLASS_BACKGROUND;
	wcInputBox.lpszMenuName		= INPUT_BOX_WINDOW_CLASS_MENU_NAME;
	wcInputBox.hIconSm			= INPUT_BOX_WINDOW_CLASS_ICON;

	// Register input box window class
	if( RegisterClassEx( &wcInputBox ) )
	{
		// Successfully registered input box window class
		HWND hWndInputBox;

		// Allocate global memory
		g_lpszInputText = new char[ STRING_LENGTH ];

		// Store initial input text
		lstrcpy( g_lpszInputText, lpszInputText );

		// Update global instance handle
		g_hInstance = hInstance;

		// Create input box window
		hWndInputBox = CreateWindowEx( INPUT_BOX_WINDOW_EXTENDED_STYLE, INPUT_BOX_WINDOW_CLASS_NAME, lpszTitle, INPUT_BOX_WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT,  INPUT_BOX_WINDOW_WIDTH, INPUT_BOX_WINDOW_HEIGHT, hWndParent, NULL, hInstance, NULL );

		// Ensure that input box window was created
		if( hWndInputBox )
		{
			// Successfully created input box window
			MSG msg;

			// Show input box window
			ShowWindow( hWndInputBox, SW_SHOWNORMAL );

			// Update input box window
			UpdateWindow( hWndInputBox );

			// Message loop
			while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
			{
				// Translate message
				TranslateMessage( &msg );

				// Dispatch message
				DispatchMessage( &msg );

			}; // End of message loop

		} // End of successfully created input box window
		else
		{
			// Unable to create input box window

			// Display error message
			MessageBox( NULL, INPUT_BOX_WINDOW_UNABLE_TO_CREATE_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to create input box window

		// Free global memory
		delete [] g_lpszInputText;

	} // End of successfully registered input box window class
	else
	{
		// Unable to register input box window class

		// Display error message
		MessageBox( NULL, INPUT_BOX_WINDOW_UNABLE_TO_REGISTER_CLASS_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to register input box window class

	return bResult;

} // End of function InputBox
