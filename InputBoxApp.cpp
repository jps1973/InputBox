// InputBoxApp.cpp

#include "InputBoxApp.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int )
{
	// Allocate string memory
	LPTSTR lpszInputText = new char[ STRING_LENGTH + sizeof( char ) ];

	// Initialise input text
	lstrcpy( lpszInputText, "Input Text" );

	// Input some text
	if( InputBoxDialogShow( NULL, hInstance, lpszInputText, "Input some text" ) )
	{
		// Successfully input some text

		// Display text
		MessageBox( NULL, lpszInputText, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

	} // End of successfully input some text
	else
	{
		// Unable to input some text

		// Display text
		MessageBox( NULL, "No Input", INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

	} // End of unable to input input some text

	// Free string memory
	delete [] lpszInputText;

	return 0;

} // End of function WinMain
