#include "Wraith.h"
#include "AzulCore.h"

#include "ModelManagerAttorney.h"
#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "ImageManagerAttorney.h"
#include "SpriteFontManagerAttorney.h"
#include "TerrainObjectManagerAttorney.h"
#include "OctreeModelManager.h"

#include "SceneManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "ScreenLogAttorney.h"

Wraith* Wraith::pGameInstance = nullptr;

Wraith& Wraith::GetInstance()
{
	if (Wraith::pGameInstance == nullptr)
	{
		Wraith::pGameInstance = new Wraith();
	}
	assert(pGameInstance != nullptr);
	return *pGameInstance;
}

Wraith::Wraith()
{}

void Wraith::Delete()
{
	delete Wraith::pGameInstance;
	Wraith::pGameInstance = nullptr;
}

//-----------------------------------------------------------------------------
// Internal workings of Wraith Engine 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Wraith::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Wraith::Initialize()
{
	this->gameInitialize();
}

//-----------------------------------------------------------------------------
// Wraith::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Wraith::LoadContent()
{
	Wraith::PrintTitleMessage("Loading Content");
	//---------------------------------------------------------------------------------------------------------
	// Load game resources
	//---------------------------------------------------------------------------------------------------------
	this->loadResources();

	//---------------------------------------------------------------------------------------------------------
	// Initialize Start Scene
	//---------------------------------------------------------------------------------------------------------
	SceneManagerAttorney::InitalizationAccess::InitializeStartScene();

	Trace::out("\n");
}

//-----------------------------------------------------------------------------
// Wraith::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Wraith::Update()
{
	TimeManagerAttorney::TimeAccess::SetCurrentTimeStamp(this->GetTimeInSeconds());
	SceneManagerAttorney::GameLoopAccess::Update();
}

//-----------------------------------------------------------------------------
// Wraith::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Wraith::Draw()
{
	VisualizerAttorney::RenderAccess::VisualizeAll();
	SceneManagerAttorney::GameLoopAccess::Draw();
	ScreenLogAttorney::RenderAccess::Render();
}

//-----------------------------------------------------------------------------
// Wraith::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Wraith::UnLoadContent()
{
	Wraith::PrintTitleMessage("Unloading Content");
	// general clean up.

	// Asset  clean up
	ShaderManagerAttorney::DeleteAccess::Delete();
	ModelManagerAttorney::DeleteAccess::Delete();
	TextureManagerAttorney::DeleteAccess::Delete();
	ImageManagerAttorney::DeleteAccess::Delete();
	SpriteFontManagerAttorney::DeleteAccess::Delete();
	TerrainObjectManagerAttorney::DeleteAccess::Delete();
	OctreeModelManager::Delete();

	// Scene clean up
	SceneManagerAttorney::DeleteAccess::Delete();

	TimeManagerAttorney::DeleteAccess::Delete();
	VisualizerAttorney::DeleteAccess::Delete();
	ScreenLogAttorney::DeleteAccess::Delete();

	this->gameEnd();
	Trace::out("\n");
}

// Personal Printing function 
void Wraith::PrintTitleMessage(const std::string& message)
{
	int targetMessageWidth = 50;

	int dashLength = (targetMessageWidth - message.length()) / 2;

	std::string dashedString(dashLength, '-');
	dashedString.at(0) = ' '; dashedString.at(dashedString.length() - 1) = ' ';
	
	Trace::out("Wraith:%s%s%s\n", dashedString.c_str(), message.c_str(), dashedString.c_str());
}
