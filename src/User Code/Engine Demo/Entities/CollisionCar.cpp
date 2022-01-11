#include "CollisionCar.h"

// include Resource Managers header files
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

// include Scene Manager and Scene header files
#include "SceneManager.h"
#include "Scene.h"

#include "Visualizer.h"
#include "Colors.h"

CollisionCar::CollisionCar()
{
	// Get Resources from Managers using user defined keys.
	Model* pCarModel = ModelManager::GetModel("Car");
	// Shader Manager takes in keys and enums for shaders. (Enums are for preloaded shaders)
	ShaderObject* pCarShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pCarTexture = TextureManager::GetTexture("CarTexture");

	// Initialize a Graphics Object 
	_pCarGraphicsObject = new GraphicsObject_TextureFlat(pCarModel, pCarShader, pCarTexture);

	// Initialize world matrix.
	Matrix scale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix rotation = Matrix(IDENTITY);
	Matrix translation = Matrix(TRANS, 0.0f, 0.0f, 0.0f);

	Matrix world = scale * rotation * translation;

	_pCarGraphicsObject->SetWorld(world);

	// Submit Registrations
	submitUpdateRegistration();
	submitDrawRegistration();

	// Register for collisions
	setCollidableGroup<CollisionCar>();
	// IMPORTANT: set the model for the collider
	setColliderModel(_pCarGraphicsObject->getModel(), VolumeType::BSPHERE);
	submitCollisionRegistration();
}

CollisionCar::~CollisionCar()
{
	delete _pCarGraphicsObject;
}

void CollisionCar::collision(OtherCollisionCar*) // Collision call back for OtherCollisionCar
{
	Trace::out("CollisionCar: collided with OtherCollisionCar\n");
	// when it has collided do something, in this set _hasCollidedDebug = true.
	// NOTE: this is used for visualizing the collision model for debug purposes
	_hasCollidedDebug = true;
}

void CollisionCar::update()
{
	// IMPORTANT: Since we are changing the world matrix
	// we must called updateCollisionData() to update collision data
	// AFTER we change the world matrix

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

	// NOW update collision data
	updateCollisionData(_pCarGraphicsObject->getWorld());
}

void CollisionCar::draw()
{
	// Get Camera for drawing graphics object
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();

	// Then for every graphics object call render and pass in the camera
	_pCarGraphicsObject->Render(pCamera);

	// NOTE: For visualizing the collider model and for
	// a quick test for a collision we call on Visualizer to render a sphere
	
	if (_hasCollidedDebug)
	{
		Visualizer::ShowCollisionVolume(getCollisionVolume(), Colors::Red);
	}
	else
	{
		Visualizer::ShowCollisionVolume(getCollisionVolume(), Colors::Blue);
	}

	_hasCollidedDebug = false;
}
