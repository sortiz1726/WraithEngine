#include "Wraith.h"

// -----------------------------------------------------------------------------
// To be defined by user (Specific to each game)
// -----------------------------------------------------------------------------
void Wraith::gameInitialize()
{
	Wraith::PrintTitleMessage("Game Initializing");
	// Wraith Window Device setup
	Wraith::SetWindowName("Wraith Engine");
	Wraith::SetWindowWidthAndHeight(800, 600);
	Wraith::SetBackgroundColor(0.4f, 0.4f, 0.8f, 1.0f);

	// Use this area, for one time non-graphic creation

	Trace::out("\n");
}