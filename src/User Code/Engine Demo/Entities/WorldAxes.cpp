#include "WorldAxes.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"

WorldAxes::WorldAxes()
	: _pGraphicsObject_Axes(nullptr)
{
	//-----------------------------------------------------------------------------------------------------------------------------
	// World Axes
	//-----------------------------------------------------------------------------------------------------------------------------
	
	// Load Assets
	Model* pAxesModel = ModelManager::GetModel("Axis");
	ShaderObject* pColorNoTextureShader = ShaderManager::GetShader("colorNoTexture");

	// Create Graphics Object
	_pGraphicsObject_Axes = new GraphicsObject_ColorNoTexture(pAxesModel, pColorNoTextureShader);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Register to Current Scene
	//-----------------------------------------------------------------------------------------------------------------------------
	submitDrawRegistration();
}

WorldAxes::~WorldAxes()
{
	//Trace::out("\n-----------------------------------------\n");
	//Trace::out("WorldAxes: Destructor Called\n");
	delete _pGraphicsObject_Axes;
}

void WorldAxes::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pGraphicsObject_Axes->Render(pCamera);
}