#include "Cottage.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Visualizer.h"
#include "Colors.h"
#include "vmath.h"

const float Cottage::adjustedScale = 0.5f;

Cottage::Cottage()
	: _pCottageGraphicsObject(nullptr),
	_localScale(Vect(1.0f, 1.0f, 1.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localPosition(Vect(0.0f, 0.0f, 0.0f))
{
	InitiailizeCottageGraphicsObject();
}

void Cottage::InitiailizeCottageGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pCottageModel = ModelManager::GetModel("Cottage1");
	ShaderObject* pCottageShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pCottageTexture = TextureManager::GetTexture("Cottage1Texture");

	_pCottageGraphicsObject = new GraphicsObject_TextureLight(pCottageModel, pCottageShader, pCottageTexture, lightColor, lightPosition);

	setColliderModel(_pCottageGraphicsObject->getModel(), VolumeType::OBB);

	//Texture* pBrickWallTexture = TextureManager::GetTexture("BrickWallTexture");
	//Texture* pRoofTexture = TextureManager::GetTexture("RoofTexture");
	//Texture* pCabinTexture = TextureManager::GetTexture("CabinTexture");
	//Texture* pChimmneyTexture = TextureManager::GetTexture("ChimneyTexture");

	//_pCottageGraphicsObject = new GraphicsObject_TextureLight(pCottageModel, pCottageShader, pBrickWallTexture, pRoofTexture, pCabinTexture, pChimmneyTexture, lightColor, lightPosition);
}

Cottage::~Cottage()
{
	delete _pCottageGraphicsObject;
}

void Cottage::initialize(const Vect& position, float rotationY, float uniformScale)
{
	initialize(position, Vect(0.0f, rotationY, 0.0f), Vect(uniformScale, uniformScale, uniformScale));
}

void Cottage::initialize(const Vect& position, const Vect& rotation, const Vect& scale)
{
	setLocalPosition(position);
	setLocalRotation(rotation);
	setLocalScale(scale);
	
	Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	_pCottageGraphicsObject->SetWorld(world);
	setCollidableGroup<Cottage>();
	updateCollisionData(_pCottageGraphicsObject->getWorld());

	submitDrawRegistration();
	submitCollisionRegistration();
}

#pragma region GameObject Properties

void Cottage::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pCottageGraphicsObject->Render(pCamera);

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

void Cottage::collision(Tank*)
{
	_hasCollidedDebug = true;
}

void Cottage::collision(Bullet*)
{
	_hasCollidedDebug = true;
}

#pragma endregion

#pragma region Setters/Getters

// --> Scale
void Cottage::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect Cottage::getLocalScale() const
{
	return _localScale;
}

Matrix Cottage::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale * Cottage::adjustedScale);
}

// --> Rotation
void Cottage::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, vmath::radians(localRotation.Y()));
}

Matrix Cottage::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// --> Position
void Cottage::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect Cottage::getLocalPosition() const
{
	return _localPosition;
}

Matrix Cottage::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}
#pragma endregion
