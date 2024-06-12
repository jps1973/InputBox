// InputBoxApp.cpp

#include "InputBoxApp.h"

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPTSTR, int )
{
	// Allocate string memory
	LPTSTR lpszInputText = new char[ STRING_LENGTH ];

	// Initialise input text
	lstrcpy( lpszInputText, "I need input" );

	// Get input
	if( InputBox( NULL, lpszInputText ) )
	{
		// Successfully got input
	} // End of successfully got input

	// Free string memory
	delete [] lpszInputText;

	return 0;

} // End of function WinMain
