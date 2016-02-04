// Professional Skills Assignment.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;

//Provided here for the extern in 'Globals.h'
I3DEngine* gEngine = 0;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* gEngine = New3DEngine( kTLX );
	gEngine->StartWindowed();

	// Add default folder for meshes and other media
	gEngine->AddMediaFolder( ".\\Media" );

	/**** Set up your scene here ****/


	// The main game loop, repeat until engine is stopped
	while (gEngine->IsRunning())
	{
		// Draw the scene
		gEngine->DrawScene();

		/**** Update your scene each frame here ****/

	}

	// Delete the 3D engine now we are finished with it
	gEngine->Delete();
}
