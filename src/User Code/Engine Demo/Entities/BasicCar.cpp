#include "BasicCar.h"

// include Resource Managers header files
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

// include Scene Manager and Scene header files
#include "SceneManager.h"
#include "Scene.h"

BasicCar::BasicCar()
{
	// Get Resources from Managers using user defined keys.
	Model* pBasicCarModel = ModelManager::GetModel("Car");
	// Shader Manager takes in keys and enums for shaders. (Enums are for preloaded shaders)
	ShaderObject* pBasicCarShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pBasicCarTexture = TextureManager::GetTexture("CarTexture");

	// Initialize a Graphics Object 
	_pCarGraphicsObject = new GraphicsObject_TextureFlat(pBasicCarModel, pBasicCarShader, pBasicCarTexture);

	// Initialize world matrix.
	Matrix scale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix rotation = Matrix(IDENTITY);
	Matrix translation = Matrix(TRANS, 0.0f, 0.0f, 0.0f);

	Matrix world = scale * rotation * translation;

	_pCarGraphicsObject->SetWorld(world);

	// Submit Registrations for update and draw
	submitUpdateRegistration();
	submitDrawRegistration();
}

BasicCar::~BasicCar()
{
	delete _pCarGraphicsObject;
}

void BasicCar::update()
{
	Matrix world = _pCarGraphicsObject->getWorld();

	// Moving using Keyboard to test key states.
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		// move foward
		world *= Matrix(TRANS, 0.0f, 0.0f, 1.0f);
	}
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		// move backwards
		world *= Matrix(TRANS, 0.0f, 0.0f, -1.0f);
	}
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		// move right
		world *= Matrix(TRANS, -1.0f, 0.0f, 0.0f);
	}
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		// move left
		world *= Matrix(TRANS, 1.0f, 0.0f, 0.0f);
	}

	_pCarGraphicsObject->SetWorld(world);
}

void BasicCar::draw()
{
	// Get Camera for drawing graphics object
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();

	// Then for every graphics object call render and pass in the camera
	_pCarGraphicsObject->Render(pCamera);
}
