// InputBox.cpp

#include "InputBox.h"

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

BOOL InputBox(HWND hWndParent, LPTSTR lpszInputText, LPCTSTR lpszTitle )
{
	BOOL bResult = FALSE;

	WNDCLASSEX wcInputBox;
	HINSTANCE hInstance;

	// Get instance
	hInstance = GetModuleHandle( NULL );

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

		// Create input box window
		hWndInputBox = CreateWindowEx( INPUT_BOX_WINDOW_EXTENDED_STYLE, INPUT_BOX_WINDOW_CLASS_NAME, lpszTitle, INPUT_BOX_WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT,  CW_USEDEFAULT, CW_USEDEFAULT, hWndParent, NULL, hInstance, NULL );

		// Ensure that input box window was created
		if( hWndInputBox )
		{
			// Successfully created input box window
			MSG msg;

			// Clear message structure
			ZeroMemory( &msg, sizeof( msg ) );

			// Show input box window
			ShowWindow( hWndInputBox, SW_SHOW );

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
			MessageBox( NULL, UNABLE_TO_CREATE_INPUT_BOX_WINDOW_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to create input box window

	} // End of successfully registered input box window class
	else
	{
		// Unable to register input box window class

		// Display error message
		MessageBox( NULL, UNABLE_TO_REGISTER_INPUT_BOX_WINDOW_CLASS_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to register input box window class

	return bResult;

} // End of function InputBox
