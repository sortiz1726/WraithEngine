#include "WorldPlane.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"

WorldPlane::WorldPlane()
	: _pGraphicsObject_Plane(nullptr)
{
	//-----------------------------------------------------------------------------------------------------------------------------
	// World Plane
	//-----------------------------------------------------------------------------------------------------------------------------
	// Load Assets
	Model* pPlaneModel = ModelManager::GetModel("Plane");
	ShaderObject* pTextureShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pPlaneTexture = TextureManager::GetTexture("GridTexture");

	// Create Graphics Object
	_pGraphicsObject_Plane = new GraphicsObject_TextureFlat(pPlaneModel, pTextureShader, pPlaneTexture);

	// Compute World Matrix
	Matrix 	world = Matrix(SCALE, 200, 200, 200);

	// Set World
	_pGraphicsObject_Plane->SetWorld(world);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Register to Current Scene
	//-----------------------------------------------------------------------------------------------------------------------------
	submitDrawRegistration();
}

WorldPlane::~WorldPlane()
{
	//Trace::out("\n-----------------------------------------\n");
	//Trace::out("WorldPlane: Destructor Called\n");
	delete _pGraphicsObject_Plane;
}

void WorldPlane::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pGraphicsObject_Plane->Render(pCamera);
}