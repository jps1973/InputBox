// InputBox.cpp

#include "InputBox.h"

// Global variables
static HWND g_hWndTitle;
static HWND g_hWndEdit;
static HWND g_hWndOkButton;
static HWND g_hWndCancelButton;
static LPTSTR g_lpszInputText;
static LPTSTR g_lpszTitle;

BOOL InputBoxWindowMove( HWND hWndInputBox, int nLeft, int nTop )
{
	BOOL bResult = FALSE;

	int nDesktopWindowWidth;
	int nDesktopWindowHeight;
	int nMaximumLeft;
	int nMaximumTop;
	RECT rcWorkArea;

	// Get work area size
	SystemParametersInfo( SPI_GETWORKAREA, 0, &rcWorkArea, 0 );

	// Calculate desktop window size
	nDesktopWindowWidth		= ( rcWorkArea.right - rcWorkArea.left );
	nDesktopWindowHeight	= ( rcWorkArea.bottom - rcWorkArea.top );

	// Calculate maximum window position
	nMaximumLeft	= ( nDesktopWindowWidth - INPUT_BOX_WINDOW_WIDTH );
	nMaximumTop		= ( nDesktopWindowHeight - INPUT_BOX_WINDOW_HEIGHT );

	// Limit window position to fit on screen
	nLeft	= ( ( nLeft < 0 ) ? 0 : nLeft );
	nTop	= ( ( nTop < 0 ) ? 0 : nTop );
	nLeft	= ( ( nLeft > nMaximumLeft ) ? nMaximumLeft : nLeft );
	nTop	= ( ( nTop > nMaximumTop ) ? nMaximumTop : nTop );

	// Move window
	bResult = SetWindowPos( hWndInputBox, NULL, nLeft, nTop, 0, 0, ( SWP_NOSIZE | SWP_NOOWNERZORDER ) );

	// Save window position
	RegistrySetValue( INPUT_BOX_REGISTRY_TOP_LEVEL_KEY, INPUT_BOX_REGISTRY_SUB_KEY, INPUT_BOX_REGISTRY_LEFT_VALUE_NAME, nLeft );
	RegistrySetValue( INPUT_BOX_REGISTRY_TOP_LEVEL_KEY, INPUT_BOX_REGISTRY_SUB_KEY, INPUT_BOX_REGISTRY_TOP_VALUE_NAME, nTop );

	return bResult;

} // End of function InputBoxWindowMove

// Input box window procedure
LRESULT CALLBACK InputBoxWndProc( HWND hWndInputBox, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	static int s_nClickX;
	static int s_nClickY;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message
			HINSTANCE hInstance;
			int nTitleWindowWidth;
			int nEditWindowWidth;

			// Get instance
			hInstance = ( ( LPCREATESTRUCT )lParam )->hInstance;

			// Calculate title window width
			nTitleWindowWidth = ( INPUT_BOX_WINDOW_WIDTH - ( INPUT_BOX_WINDOW_SEPARATOR_SIZE + INPUT_BOX_WINDOW_SEPARATOR_SIZE ) );

			// Create title window
			g_hWndTitle = CreateWindowEx( INPUT_BOX_TITLE_WINDOW_EXTENDED_STYLE, INPUT_BOX_TITLE_WINDOW_CLASS_NAME, g_lpszTitle, INPUT_BOX_TITLE_WINDOW_STYLE, INPUT_BOX_WINDOW_SEPARATOR_SIZE, INPUT_BOX_WINDOW_SEPARATOR_SIZE, nTitleWindowWidth, INPUT_BOX_TITLE_WINDOW_HEIGHT, hWndInputBox, ( HMENU )NULL, hInstance, NULL );

			// Ensure that title window was created
			if( g_hWndTitle )
			{
				// Successfully created title window
				HFONT hFont;
				int nEditWindowHeight;
				int nEditWindowLeft;
				int nEditWindowTop;

				// Get font
				hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

				// Set title window font
				SendMessage( g_hWndTitle, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

				// Calculate edit window size
				nEditWindowWidth	= ( INPUT_BOX_WINDOW_WIDTH - ( WINDOW_BORDER_WIDTH + INPUT_BOX_WINDOW_SEPARATOR_SIZE + INPUT_BOX_WINDOW_SEPARATOR_SIZE + WINDOW_BORDER_WIDTH ) );
				nEditWindowHeight	= INPUT_BOX_EDIT_WINDOW_HEIGHT;

				// Calculate edit window position
				nEditWindowLeft		= INPUT_BOX_WINDOW_SEPARATOR_SIZE;
				nEditWindowTop		= ( INPUT_BOX_WINDOW_SEPARATOR_SIZE + INPUT_BOX_TITLE_WINDOW_HEIGHT + INPUT_BOX_WINDOW_SEPARATOR_SIZE );

				// Create edit window
				g_hWndEdit = CreateWindowEx( INPUT_BOX_EDIT_WINDOW_EXTENDED_STYLE, INPUT_BOX_EDIT_WINDOW_CLASS_NAME, g_lpszInputText, INPUT_BOX_EDIT_WINDOW_STYLE, nEditWindowLeft, nEditWindowTop, nEditWindowWidth, nEditWindowHeight, hWndInputBox, ( HMENU )NULL, hInstance, NULL );

				// Ensure that edit window was created
				if( g_hWndEdit )
				{
					// Successfully created edit window
					int nOkButtonWindowLeft;
					int nButtonWindowTop;

					// Set edit window font
					SendMessage( g_hWndEdit, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

					// Calculate ok button window position
					nOkButtonWindowLeft	= ( ( nEditWindowLeft + nEditWindowWidth ) - ( INPUT_BOX_BUTTON_WINDOW_WIDTH + INPUT_BOX_WINDOW_SEPARATOR_SIZE + INPUT_BOX_BUTTON_WINDOW_WIDTH ) );
					nButtonWindowTop	= ( nEditWindowTop + INPUT_BOX_EDIT_WINDOW_HEIGHT + INPUT_BOX_WINDOW_SEPARATOR_SIZE );

					// Create ok button window
					g_hWndOkButton = CreateWindowEx( INPUT_BOX_BUTTON_WINDOW_EXTENDED_STYLE, INPUT_BOX_BUTTON_WINDOW_CLASS_NAME, INPUT_BOX_OK_BUTTON_WINDOW_TEXT, INPUT_BOX_BUTTON_WINDOW_STYLE, nOkButtonWindowLeft, nButtonWindowTop, INPUT_BOX_BUTTON_WINDOW_WIDTH, INPUT_BOX_BUTTON_WINDOW_HEIGHT, hWndInputBox, ( HMENU )INPUT_BOX_OK_BUTTON_WINDOW_ID, hInstance, NULL );

					// Ensure that ok button window was created
					if( g_hWndOkButton )
					{
						// Successfully created ok button window
						int nCancelButtonWindowLeft;

						// Set ok button window font
						SendMessage( g_hWndOkButton, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

						// Calculate cancel button window position
						nCancelButtonWindowLeft	= ( nOkButtonWindowLeft + INPUT_BOX_BUTTON_WINDOW_WIDTH + INPUT_BOX_WINDOW_SEPARATOR_SIZE );

						// Create cancel button window
						g_hWndCancelButton = CreateWindowEx( INPUT_BOX_BUTTON_WINDOW_EXTENDED_STYLE, INPUT_BOX_BUTTON_WINDOW_CLASS_NAME, INPUT_BOX_CANCEL_BUTTON_WINDOW_TEXT, INPUT_BOX_BUTTON_WINDOW_STYLE, nCancelButtonWindowLeft, nButtonWindowTop, INPUT_BOX_BUTTON_WINDOW_WIDTH, INPUT_BOX_BUTTON_WINDOW_HEIGHT, hWndInputBox, ( HMENU )INPUT_BOX_CANCEL_BUTTON_WINDOW_ID, hInstance, NULL );

						// Ensure that cancel button window was created
						if( g_hWndCancelButton )
						{
							// Successfully created cancel button window

							// Set cancel button window font
							SendMessage( g_hWndCancelButton, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

							// Select edit text
							SendMessage( g_hWndEdit, EM_SETSEL, ( WPARAM )0, ( LPARAM )-1 );

							// Focus on edit window
							SetFocus( g_hWndEdit );

						} // End of successfully created cancel button window

					} // End of successfully created ok button window

				} // End of successfully created edit window

			} // End of successfully created title window

			// Break out of switch
			break;

		} // End of a create message
		case WM_ACTIVATE:
		{
			// An activate message

			// Focus on edit window
			SetFocus( g_hWndEdit );

			// Break out of switch
			break;

		} // End of an activate message
		case WM_LBUTTONDOWN:
		{
			// A left mouse button down message

			// Set mouse capture to input box window
			SetCapture( hWndInputBox );

			// Store static variables
			s_nClickX = GET_X_LPARAM( lParam );
			s_nClickY = GET_Y_LPARAM( lParam );

			// Break out of switch
			break;

		} // End of a left mouse button down message
		case WM_LBUTTONUP:
		{
			// A left mouse button up message

			// Release mouse capture
			ReleaseCapture();

			// Break out of switch
			break;

		} // End of a left mouse button up message
		case WM_MOUSEMOVE:
		{
			// A mouse move message

			// See if input box window has mouse capture
			if( GetCapture() == hWndInputBox )
			{
				// Input box window has mouse capture
				RECT rc;
				int nMouseX;
				int nMouseY;
				int nWindowX;
				int nWindowY;

				// Get window position
				GetWindowRect( hWndInputBox, &rc );

				// Store mouse position
				nMouseX = GET_X_LPARAM( lParam );
				nMouseY = GET_Y_LPARAM( lParam );

				// Calculate window position
				nWindowX = ( ( rc.left + nMouseX ) - s_nClickX );
				nWindowY = ( ( rc.top + nMouseY ) - s_nClickY );

				// Move input box window
				InputBoxWindowMove( hWndInputBox, nWindowX, nWindowY );

			} // End of input box window has mouse capture
			else
			{
				// Input box window does not have mouse capture

				// Call default procedure
				lr = DefWindowProc( hWndInputBox, uMessage, wParam, lParam );

			} // End of input box window does not have mouse capture

			// Break out of switch
			break;

		} // End of a mouse move message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case INPUT_BOX_OK_BUTTON_WINDOW_ID:
				{
					// Ok button has been pressed

					// Update global input text
					SendMessage( g_hWndEdit, WM_GETTEXT, ( WPARAM )STRING_LENGTH, ( LPARAM )g_lpszInputText );

					// Destroy input box window
					DestroyWindow( hWndInputBox );

					// Break out of switch
					break;

				} // End of ok button has been pressed
				case INPUT_BOX_CANCEL_BUTTON_WINDOW_ID:
				{
					// Cancel button has been pressed

					// Destroy input box window
					DestroyWindow( hWndInputBox );

					// Break out of switch
					break;

				} // End of cancel button has been pressed
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
		case WM_CTLCOLORSTATIC:
		{
			// A control color static message

			// See if message is from title window
			if( ( HWND )lParam == g_hWndTitle )
			{
				// Message is from title window
				HDC hdcTitle;

				// Get hdc
				hdcTitle = ( HDC )wParam;

				// Set title to transparent
				SetBkMode( hdcTitle, TRANSPARENT );

				// Update return value
				lr = ( LRESULT )CreateSolidBrush( GetSysColor( INPUT_BOX_WINDOW_CLASS_BACKGROUND_COLOR ) );

			} // End of message is from title window
			else
			{
				// Message is not from title window

				// Call default window procedure
				lr = DefWindowProc( hWndInputBox, uMessage, wParam, lParam );

			} // End of message is not from title window

			// Break out of switch
			break;

		} // End of a control color static message
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

BOOL InputBox( HWND hWndParent, LPTSTR lpszInputText, LPCTSTR lpszTitle )
{
	BOOL bResult = FALSE;

	WNDCLASSEX wcInputBox;
	HINSTANCE hInstance;

	// Allocate global memory
	g_lpszInputText	= new char[ STRING_LENGTH ];
	g_lpszTitle		= new char[ STRING_LENGTH ];

	// Initialise global strings
	lstrcpy( g_lpszInputText,	lpszInputText );
	lstrcpy( g_lpszTitle,		lpszTitle );

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
		hWndInputBox = CreateWindowEx( INPUT_BOX_WINDOW_EXTENDED_STYLE, INPUT_BOX_WINDOW_CLASS_NAME, lpszTitle, INPUT_BOX_WINDOW_STYLE, INPUT_BOX_WINDOW_DEFAULT_LEFT, INPUT_BOX_WINDOW_DEFAULT_TOP, INPUT_BOX_WINDOW_WIDTH, INPUT_BOX_WINDOW_HEIGHT, hWndParent, NULL, hInstance, NULL );

		// Ensure that input box window was created
		if( hWndInputBox )
		{
			// Successfully created input box window
			MSG msg;
			int nLeft;
			int nTop;

			// Get initial window position
			nLeft	= RegistryGetValue( INPUT_BOX_REGISTRY_TOP_LEVEL_KEY, INPUT_BOX_REGISTRY_SUB_KEY, INPUT_BOX_REGISTRY_LEFT_VALUE_NAME, INPUT_BOX_WINDOW_DEFAULT_LEFT );
			nTop	= RegistryGetValue( INPUT_BOX_REGISTRY_TOP_LEVEL_KEY, INPUT_BOX_REGISTRY_SUB_KEY, INPUT_BOX_REGISTRY_TOP_VALUE_NAME, INPUT_BOX_WINDOW_DEFAULT_TOP );

			// Move window
			InputBoxWindowMove( hWndInputBox, nLeft, nTop );

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

			// See if input text has changed
			if( lstrcmpi( lpszInputText, g_lpszInputText ) != 0 )
			{
				// Input text has changed

				// Update supplied input text variable
				lstrcpy( lpszInputText, g_lpszInputText );

				// Update return value
				bResult = TRUE;

			} // End of input text has changed

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

	// Free global memory
	delete [] g_lpszInputText;
	delete [] g_lpszTitle;

	return bResult;

} // End of function InputBox
