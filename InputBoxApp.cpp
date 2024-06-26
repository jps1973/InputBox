// InputBoxApp.cpp

#include "InputBoxApp.h"

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPTSTR, int )
{
	// Allocate string memory
	LPTSTR lpszInputText = new char[ STRING_LENGTH ];

	// Initialise input text
	lstrcpy( lpszInputText, "I need input" );

	// Get input
	if( InputBox( NULL, lpszInputText, "Please Input Some Text" ) )
	{
		// Successfully got input

		// Display input text
		MessageBox( NULL, lpszInputText, "Updated", MB_OK );

	} // End of successfully got input
	else
	{
		// Unable to get input

		// Display input text
		MessageBox( NULL, lpszInputText, "Not updated", MB_OK );

	} // End of unable to get input

	// Free string memory
	delete [] lpszInputText;

	return 0;

} // End of function WinMain
