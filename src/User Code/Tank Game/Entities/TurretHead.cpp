#include "TurretHead.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "vmath.h"
#include "TurretBase.h"
#include "MathTools.h"
#include "ScreenLog.h"

TurretHead::TurretHead()
	: _pTurretHeadGraphicsObject(nullptr),
	_localPosition(Vect(0.0f, 0.0f, 0.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localScale(Vect(1.0f, 1.0f, 1.0f))
{
	initializeTurretHeadGraphicsObject();
}

void TurretHead::initializeTurretHeadGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pTurretHeadModel = ModelManager::GetModel("TurretHead");
	ShaderObject* pTurretHeadShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pTurretHeadTexture = TextureManager::GetTexture("TurretTexture");

	_pTurretHeadGraphicsObject = new GraphicsObject_TextureLight(pTurretHeadModel, pTurretHeadShader, pTurretHeadTexture, lightColor, lightPosition);

	Matrix world = getLocalWorldMatrix();
	_pTurretHeadGraphicsObject->SetWorld(world);
}

TurretHead::~TurretHead()
{
	delete _pTurretHeadGraphicsObject;
}

#pragma region Actions

void TurretHead::turn(float turnValue)
{
	float turnOffset = turnValue * vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds();
	Matrix rotationOffset = Matrix(ROT_AXIS_ANGLE, Vect(0.0f, 1.0f, 0.0f), turnOffset);
	_localRotation *= rotationOffset;
}

void TurretHead::turnTo(const Vect& target)
{
	Vect localTarget = target * getWorldMatrix().getInv();
	_localRotation *= computeRotationMatrixTowards(localTarget);
}

void TurretHead::draw(Camera* pCamera)
{
	//updateWorldMatrix();
	_pTurretHeadGraphicsObject->Render(pCamera);
}

// ---> Action Helpers
void TurretHead::updateWorldMatrix()
{
	Matrix world = getWorldMatrix();
	_pTurretHeadGraphicsObject->SetWorld(world);
}

Matrix TurretHead::computeRotationMatrixTowards(const Vect& position) const
{
	Vect localFoward = Vect(0.0f, 0.0f, 1.0f);
	Vect localUp = Vect(0.0f, 1.0f, 0.0f);

	Vect directionToTarget = computeDirectionTo(position);
	float rotationAngle = computeRotationAngle(localFoward, directionToTarget);
	Vect rotationAxis = localFoward.cross(directionToTarget);
	if (rotationAxis.magSqr() == 0.0f)
	{
		rotationAxis = localUp;
	}

	return Matrix(ROT_AXIS_ANGLE, rotationAxis, rotationAngle);
}

Vect TurretHead::computeDirectionTo(const Vect& position) const
{
	Vect localUp = computeLocal(Vect(0.0f, 1.0f, 0.0f));
	Vect directionToTarget = position - this->getLocalPosition();
	directionToTarget -= (directionToTarget.dot(localUp)) * localUp;
	directionToTarget = directionToTarget.getNorm();
	return directionToTarget;
}

float TurretHead::computeRotationAngle(const Vect& localFoward, const Vect& directionToTarget) const
{
	float rotationAngle = computeAngleBetween(localFoward, directionToTarget);
	float rotationDuringFrame = vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds();
	rotationAngle = (rotationAngle > rotationDuringFrame) ? rotationDuringFrame : rotationAngle;
	return rotationAngle;
}

float TurretHead::computeAngleBetween(const Vect& vectorA, const Vect& vectorB) const
{
	float dotProduct = MathTools::Clamp(vectorA.dot(vectorB), -1.0f, 1.0f);
	return acos(dotProduct);
}

Vect TurretHead::computeLocal(const Vect& vector) const
{
	return  vector * getLocalRotationMatrix();
}

#pragma endregion

#pragma region Setters and Getters

// ---> Properties
void TurretHead::setTurnSpeed(float turnSpeed)
{
	_turnSpeed = turnSpeed;
}

void TurretHead::attachToTurretBase(TurretBase* pTurretBase)
{
	_pTurretBase = pTurretBase;
}

void TurretHead::setBulletSpawnOffset(const Vect& bulletSpawnOffset)
{
	_bulletSpawnOffset = bulletSpawnOffset;
}

Vect TurretHead::getBulletSpawnOffset() const
{
	return _bulletSpawnOffset;
}

Vect TurretHead::getBulletSpawnLocation()
{
	return _bulletSpawnOffset * getWorldMatrix();
}

// ---> World
Matrix TurretHead::getWorldMatrix() const
{
	return getLocalWorldMatrix() * _pTurretBase->getWorldMatrix();
}

Matrix TurretHead::getLocalWorldMatrix() const
{
	return getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
}

// --> Position
void TurretHead::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect TurretHead::getLocalPosition() const
{
	//ScreenLog::Add("TurretHead: local position (%3.1f, %3.1f, %3.1f)", _localPosition[x], _localPosition[y], _localPosition[z]);
	return _localPosition;
}

Matrix TurretHead::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}

// --> Rotation
void TurretHead::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, localRotation.Y());
}

Matrix TurretHead::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

Matrix TurretHead::getWorldRotationMatrix()
{
	return getLocalRotationMatrix() * _pTurretBase->getLocalRotationMatrix();
}

// --> Scale
void TurretHead::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect TurretHead::getLocalScale() const
{
	return _localScale;
}

Matrix TurretHead::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale);
}

#pragma endregion