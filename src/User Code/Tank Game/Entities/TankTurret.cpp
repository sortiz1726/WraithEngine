#include "TankTurret.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "vmath.h"
#include "TankHull.h"
#include "MathTools.h"

TankTurret::TankTurret()
	: _pTankTurretGraphicsObject(nullptr),
	_localPosition(Vect(0.0f, 0.0f, 0.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localScale(Vect(1.0f, 1.0f, 1.0f))
{
	initializeTankTurretGraphicsObject();
}

void TankTurret::initializeTankTurretGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pTankTurretModel = ModelManager::GetModel("TankTurret");
	ShaderObject* pTankTurretShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pTankTurretTexture = TextureManager::GetTexture("TankTexture");

	_pTankTurretGraphicsObject = new GraphicsObject_TextureLight(pTankTurretModel, pTankTurretShader, pTankTurretTexture, lightColor, lightPosition);

	Matrix world = getLocalWorldMatrix();
	_pTankTurretGraphicsObject->SetWorld(world);
}

TankTurret::~TankTurret()
{
	delete _pTankTurretGraphicsObject;
}

#pragma region Actions

void TankTurret::turn(float turnValue)
{
	float turnOffset = turnValue * vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds();
	Matrix rotationOffset = Matrix(ROT_AXIS_ANGLE, Vect(0.0f, 1.0f, 0.0f), turnOffset);
	_localRotation *= rotationOffset;
}

void TankTurret::turnTo(const Vect& target)
{
	Vect localTarget = target * getWorldMatrix().getInv();
	_localRotation *= computeRotationMatrixTowards(localTarget);
}

void TankTurret::draw(Camera* pCamera)
{
	//updateWorldMatrix();
	_pTankTurretGraphicsObject->Render(pCamera);
}

// ---> Action Helpers
void TankTurret::updateWorldMatrix()
{
	Matrix world = getWorldMatrix();
	_pTankTurretGraphicsObject->SetWorld(world);
}

Matrix TankTurret::computeRotationMatrixTowards(const Vect& position) const
{
	Vect localFoward = computeLocal(Vect(0.0f, 0.0f, 1.0f));
	Vect localUp = computeLocal(Vect(0.0f, 1.0f, 0.0f));

	Vect directionToTarget = computeDirectionTo(position);
	float rotationAngle = computeRotationAngle(localFoward, directionToTarget);
	Vect rotationAxis = localFoward.cross(directionToTarget);
	if (rotationAxis.magSqr() == 0.0f)
	{
		rotationAxis = localUp;
	}

	return Matrix(ROT_AXIS_ANGLE, rotationAxis, rotationAngle);
}

Vect TankTurret::computeDirectionTo(const Vect& position) const
{
	Vect localUp = computeLocal(Vect(0.0f, 1.0f, 0.0f));
	Vect directionToTarget = position - this->getLocalPosition();
	directionToTarget -= (directionToTarget.dot(localUp)) * localUp;
	directionToTarget = directionToTarget.getNorm();
	return directionToTarget;
}

float TankTurret::computeRotationAngle(const Vect& localFoward, const Vect& directionToTarget) const
{
	float rotationAngle = computeAngleBetween(localFoward, directionToTarget);
	float rotationDuringFrame = vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds();
	rotationAngle = (rotationAngle > rotationDuringFrame) ? rotationDuringFrame : rotationAngle;
	return rotationAngle;
}

float TankTurret::computeAngleBetween(const Vect& vectorA, const Vect& vectorB) const
{
	float dotProduct = MathTools::Clamp(vectorA.dot(vectorB), -1.0f, 1.0f);
	return acos(dotProduct);
}

Vect TankTurret::computeLocal(const Vect& vector) const
{
	return  vector * getLocalRotationMatrix();
}

#pragma endregion

#pragma region Setters and Getters

// ---> Properties
void TankTurret::setTurnSpeed(float turnSpeed)
{
	_turnSpeed = turnSpeed;
}

void TankTurret::attachToTankHull(TankHull* pTankBody)
{
	_pTankHull = pTankBody;
}

// ---> World
Matrix TankTurret::getWorldMatrix() const
{
	return getLocalWorldMatrix() * _pTankHull->getWorldMatrix();
}

Matrix TankTurret::getLocalWorldMatrix() const
{
	return getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
}

// --> Position
void TankTurret::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect TankTurret::getLocalPosition() const
{
	return _localPosition;
}

Matrix TankTurret::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}

// --> Rotation
void TankTurret::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, localRotation.Y());
}

Matrix TankTurret::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

Matrix TankTurret::getWorldRotationMatrix()
{
	return getLocalRotationMatrix() * _pTankHull->getLocalRotationMatrix();
}

// --> Scale
void TankTurret::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect TankTurret::getLocalScale() const
{
	return _localScale;
}

Matrix TankTurret::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale);
}

#pragma endregion