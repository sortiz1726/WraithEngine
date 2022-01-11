#include "TankHull.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "vmath.h"
#include "MathTools.h"
#include "Colors.h"

TankHull::TankHull()
	: _pTankHullGraphicsObject(nullptr),
	_localPosition(Vect(0.0f, 0.0f, 0.0f)),
	_rotationAxis(Matrix(IDENTITY)),
	_localRotation(Matrix(IDENTITY)),
	_localScale(Vect(1.0f, 1.0f, 1.0f))
{
	initializeTankHullGraphicsObject();
}

void TankHull::initializeTankHullGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pTankHullModel = ModelManager::GetModel("TankBody");
	ShaderObject* pTankHullShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pTankHullTexture = TextureManager::GetTexture("TankTexture");

	_pTankHullGraphicsObject = new GraphicsObject_TextureLight(pTankHullModel, pTankHullShader, pTankHullTexture, lightColor, lightPosition);
	
	//Vect color = Colors::Green;
	//pGO = new GraphicsObject_WireframeConstantColor(pTankHullModel, ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::CONSTANT_COLOR), color);
	//Matrix world = getLocalWorldMatrix();
	//_pTankHullGraphicsObject->SetWorld(world);
}

TankHull::~TankHull()
{
	delete _pTankHullGraphicsObject;
}

#pragma region Actions
//-----------------------------------------------------------------------------------------------------------------------------
// Actions
//-----------------------------------------------------------------------------------------------------------------------------
void TankHull::move(const Vect& direction)
{
	Vect localDirection = computeLocal(direction);
	Vect moveOffset = localDirection * _moveSpeed * TimeManager::GetElaspedFrameTimeInSeconds() * _localScale[x];
	_localPosition += moveOffset;
}

void TankHull::turn(float turnValue)
{
	float turnOffset = turnValue * vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds();
	Matrix rotationOffset = Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, Vect(0.0f, 1.0f, 0.0f), turnOffset);
	_localRotation *= rotationOffset;
}

void TankHull::turnTo(const Vect& target)
{
	_localRotation *= computeRotationMatrixTowards(target);
}

void TankHull::draw(Camera* pCamera)
{
	//updateWorldMatrix();
	_pTankHullGraphicsObject->Render(pCamera);
}

// ---> Action helpers
void TankHull::updateWorldMatrix()
{
	Matrix world = getWorldMatrix();
	_pTankHullGraphicsObject->SetWorld(world);
	//pGO->SetWorld(world);
}

Matrix TankHull::computeRotationMatrixTowards(const Vect& position) const
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

Vect TankHull::computeDirectionTo(const Vect& position) const
{
	Vect localUp = computeLocal(Vect(0.0f, 1.0f, 0.0f));
	Vect directionToTarget = position - this->getLocalPosition();
	directionToTarget -= (directionToTarget.dot(localUp)) * localUp;
	directionToTarget = directionToTarget.getNorm();
	return directionToTarget;
}

float TankHull::computeRotationAngle(const Vect& localFoward, const Vect& directionToTarget) const
{
	float rotationAngle = computeAngleBetween(localFoward, directionToTarget);
	float rotationDuringFrame = vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds();
	rotationAngle = (rotationAngle > rotationDuringFrame) ? rotationDuringFrame : rotationAngle;
	return rotationAngle;
}

float TankHull::computeAngleBetween(const Vect& vectorA, const Vect& vectorB) const
{
	float dotProduct = MathTools::Clamp(vectorA.dot(vectorB), -1.0f, 1.0f);
	return acos(dotProduct);
}

Vect TankHull::computeLocal(const Vect& vector) const
{
	return  vector * getLocalRotationMatrix();
}

#pragma endregion

#pragma region Setters and Getters

// ---> Properties
void TankHull::setMoveSpeed(float moveSpeed)
{
	_moveSpeed = moveSpeed;
}

void TankHull::setTurnSpeed(float turnSpeed)
{
	_turnSpeed = turnSpeed;
}

// ---> World
Matrix TankHull::getWorldMatrix() const
{
	return getLocalWorldMatrix();
}

Matrix TankHull::getLocalWorldMatrix() const
{
	return getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
}

// ---> Position
void TankHull::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect TankHull::getLocalPosition() const
{
	return _localPosition;
}

Matrix TankHull::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}

// ---> Rotation
void TankHull::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, localRotation[y]);
}

void TankHull::setUpAxis(const Vect& axis)
{
	Vect localUp = Vect(0.0f, 1.0f, 0.0f);

	float rotationAngle = computeAngleBetween(localUp, axis);
	Vect rotationAxis = localUp.cross(axis);
	if (rotationAxis.magSqr() == 0.0f)
	{
		rotationAxis = localUp;
	}

	_rotationAxis = Matrix(ROT_AXIS_ANGLE, rotationAxis, rotationAngle);
}

Matrix TankHull::getLocalRotationMatrix() const
{
	return _localRotation * _rotationAxis;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// ---> Scale
void TankHull::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect TankHull::getLocalScale() const
{
	return _localScale;
}

Matrix TankHull::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale);
}

Model* TankHull::getModel() const
{
	return _pTankHullGraphicsObject->getModel();
	//return ModelManager::GetModel("TankBodyHitBox");
}

#pragma endregion