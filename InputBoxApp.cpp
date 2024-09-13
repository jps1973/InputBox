// InputBoxApp.cpp

#include "InputBoxApp.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int )
{
	MSG msg;


	// Clear message structure
	ZeroMemory( &msg, sizeof( msg ) );

	// Allocate string memory
	LPTSTR lpszInputText = new char[ STRING_LENGTH ];
	
	// Show input box
	if( InputBox( NULL, hInstance, "Input Some Text", lpszInputText ) )
	{
		// Successfully shown input box

		// Display input text
		MessageBox( NULL, lpszInputText, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

	} // End of successfully shown input box

	// Free string memory
	delete [] lpszInputText;

	return msg.wParam;

} // End of function WinMain
