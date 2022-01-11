#include "Wall.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Visualizer.h"
#include "Colors.h"
#include "Tank.h"
#include "vmath.h"

#include <string>
#include <vector>

const float Wall::adjustedScale = 1.0f;

Wall::Wall()
	: _pWallGraphicsObject(nullptr),
	_localScale(Vect(1.0f, 1.0f, 1.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localPosition(Vect(0.0f, 0.0f, 0.0f))
{
	InitiailizeWallGraphicsObject();
}

void Wall::InitiailizeWallGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pWallModel = ModelManager::GetModel("Wall");
	ShaderObject* pWallShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pWallTexture = TextureManager::GetTexture("StackedBrickTexture");

	_pWallGraphicsObject = new GraphicsObject_TextureLight(pWallModel, pWallShader, pWallTexture, lightColor, lightPosition);


	//Texture* pStackedBrickTexture = TextureManager::GetTexture("StackedBrickTexture");
	//Texture* pRoofTexture = TextureManager::GetTexture("RoofTexture");
	//Texture* pCabinTexture = TextureManager::GetTexture("CabinTexture");
	//Texture* pChimmneyTexture = TextureManager::GetTexture("ChimneyTexture");

	//_pWallGraphicsObject = new GraphicsObject_TextureLight(pWallModel, pWallShader, pStackedBrickTexture, pStackedBrickTexture, pStackedBrickTexture, pStackedBrickTexture, lightColor, lightPosition);
	
	setColliderModel(_pWallGraphicsObject->getModel(), VolumeType::OBB);
}

Wall::~Wall()
{
	delete _pWallGraphicsObject;
}

void Wall::initialize(const Vect& position, float rotationY, float uniformScale)
{
	initialize(position, Vect(0.0f, rotationY, 0.0f), Vect(uniformScale, uniformScale, uniformScale));
}

void Wall::initialize(const Vect& position, const Vect& rotation, const Vect& scale)
{
	setLocalPosition(position);
	setLocalRotation(rotation);
	setLocalScale(scale);
	
	Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	_pWallGraphicsObject->SetWorld(world);
	setCollidableGroup<Wall>();
	updateCollisionData(_pWallGraphicsObject->getWorld());

	submitDrawRegistration();
	submitCollisionRegistration();
}

#pragma region GameObject Properties

void Wall::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pWallGraphicsObject->Render(pCamera);

	//if (_hasCollidedDebug)
	//{
	//	Visualizer::ShowCollisionVolume(getCollisionVolume(), Colors::Red);
	//}
	//else
	//{
	//	Visualizer::ShowCollisionVolume(getCollisionVolume(), Colors::Blue);
	//}

	_hasCollidedDebug = false;
}

void Wall::collision(Tank* pTank)
{
	_hasCollidedDebug = true;
	Vect offset = pTank->getVelocity() * TimeManager::GetElaspedFrameTimeInSeconds();
	pTank->setTankPosition(pTank->getTankPosition() - offset * 5.0f);
}

void Wall::collision(Bullet*)
{
	_hasCollidedDebug = true;
}

#pragma endregion

#pragma region Setters/Getters

// --> Scale
void Wall::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect Wall::getLocalScale() const
{
	return _localScale;
}

Matrix Wall::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale * Wall::adjustedScale);
}

// --> Rotation
void Wall::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, vmath::radians(localRotation.Y()));
}

Matrix Wall::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// --> Position
void Wall::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect Wall::getLocalPosition() const
{
	return _localPosition;
}

Matrix Wall::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}
#pragma endregion
