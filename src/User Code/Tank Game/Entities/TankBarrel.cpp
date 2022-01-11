#include "TankBarrel.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "vmath.h"
#include "TankTurret.h"

TankBarrel::TankBarrel()
	: _pTankBarrelGraphicsObject(nullptr),
	_localPosition(Vect(0.0f, 0.0f, 0.0f)),
	_localRotation(Vect(0.0f, 0.0f, 0.0f)),
	_localScale(Vect(1.0f, 1.0f, 1.0f))
{
	// Create Graphics Object
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pTankBarrelModel = ModelManager::GetModel("TankBarrel");
	ShaderObject* pTankBarrelShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pTankBarrelTexture = TextureManager::GetTexture("TankTexture");

	_pTankBarrelGraphicsObject = new GraphicsObject_TextureLight(pTankBarrelModel, pTankBarrelShader, pTankBarrelTexture, lightColor, lightPosition);

	Matrix world = getLocalWorldMatrix();
	_pTankBarrelGraphicsObject->SetWorld(world);
}

TankBarrel::~TankBarrel()
{
	delete _pTankBarrelGraphicsObject;
}

#pragma region Actions
//-----------------------------------------------------------------------------------------------------------------------------
// Actions
//-----------------------------------------------------------------------------------------------------------------------------
void TankBarrel::draw(Camera* pCamera)
{
	//updateWorldMatrix();
	_pTankBarrelGraphicsObject->Render(pCamera);
}

Vect TankBarrel::computeLocal(const Vect& vector)
{
	return  vector * getLocalRotationMatrix();
}

Matrix TankBarrel::getLocalWorldMatrix() const
{
	return getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
}

Matrix TankBarrel::getWorldMatrix() const
{
	return getLocalWorldMatrix() * _pTankTurret->getWorldMatrix();
}

void TankBarrel::updateWorldMatrix()
{
	Matrix world = getWorldMatrix();
	//world *= _pTankTurret->getBarrelOffsetMatrix();
	_pTankBarrelGraphicsObject->SetWorld(world);
}
#pragma endregion

#pragma region Setters and Getters

//-----------------------------------------------------------------------------------------------------------------------------
// Setters/Getters
//-----------------------------------------------------------------------------------------------------------------------------

// ---> Properties
void TankBarrel::setElevationSpeed(float elevationSpeed)
{
	_elevationSpeed = elevationSpeed;
}

void TankBarrel::attachToTankTurret(TankTurret* pTankTurret)
{
	_pTankTurret = pTankTurret;
}

void TankBarrel::setBulletSpawnOffset(const Vect& bulletSpawnOffset)
{
	_bulletSpawnOffset = bulletSpawnOffset;
}

Vect TankBarrel::getBulletSpawnOffset() const
{
	return _bulletSpawnOffset;
}

Vect TankBarrel::getBulletSpawnLocation()
{
	return _bulletSpawnOffset * getWorldMatrix();
}

Matrix TankBarrel::getWorldRotationMatrix() const
{
	return getLocalRotationMatrix() * _pTankTurret->getWorldRotationMatrix();
}

// --> Position
void TankBarrel::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect TankBarrel::getLocalPosition() const
{
	return _localPosition;
}

Matrix TankBarrel::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}

// --> Rotation
void TankBarrel::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(localRotation);
}

Vect TankBarrel::getLocalRotation() const
{
	return _localRotation;
}

Matrix TankBarrel::getLocalRotationMatrix() const
{
	return Matrix(RotType::ROT_Y, vmath::radians(_localRotation.Y()));
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// --> Scale
void TankBarrel::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect TankBarrel::getLocalScale() const
{
	return _localScale;
}

Matrix TankBarrel::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale);
}
#pragma endregion
