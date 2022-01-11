#include "OtherCollisionCar.h"

// include Resource Managers header files
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

// include Scene Manager and Scene header files
#include "SceneManager.h"
#include "Scene.h"

// include Visualizer and Color header files
#include "Visualizer.h"
#include "Colors.h"

OtherCollisionCar::OtherCollisionCar()
{
	// Get Resources from Managers using user defined keys.
	Model* pCarModel = ModelManager::GetModel("Car");
	// Shader Manager takes in keys and enums for shaders. (Enums are for preloaded shaders)
	ShaderObject* pCarShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pCarTexture = TextureManager::GetTexture("OtherCarTexture");

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
	setCollidableGroup<OtherCollisionCar>();
	// IMPORTANT: set the model for the collider
	setColliderModel(_pCarGraphicsObject->getModel(), VolumeType::BSPHERE);
	submitCollisionRegistration();

	// NOTE: if the object is not going to move after being created
	// then one call to updateCollisionData is good enough
	updateCollisionData(_pCarGraphicsObject->getWorld());
}

OtherCollisionCar::~OtherCollisionCar()
{
	delete _pCarGraphicsObject;
}

void OtherCollisionCar::collision(CollisionCar*) // Collision call back for CollisionCar
{
	Trace::out("OtherCollisionCar: collided with CollisionCar\n");
	// when it has collided do something, in this set _hasCollidedDebug = true.
	// NOTE: this is used for visualizing the collision model for debug purposes
	_hasCollidedDebug = true;
}

void OtherCollisionCar::draw()
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
