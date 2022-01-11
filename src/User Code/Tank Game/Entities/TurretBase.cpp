#include "TurretBase.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "vmath.h"
#include "MathTools.h"
#include "Colors.h"

TurretBase::TurretBase()
	: _pTurretBaseGraphicsObject(nullptr),
	_localPosition(Vect(0.0f, 0.0f, 0.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localScale(Vect(1.0f, 1.0f, 1.0f))
{
	initializeTurretBaseGraphicsObject();
}

void TurretBase::initializeTurretBaseGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pTurretBaseModel = ModelManager::GetModel("TurretBase");
	ShaderObject* pTurretBaseShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pTurretBaseTexture = TextureManager::GetTexture("TurretTexture");

	_pTurretBaseGraphicsObject = new GraphicsObject_TextureLight(pTurretBaseModel, pTurretBaseShader, pTurretBaseTexture, lightColor, lightPosition);

	//Vect color = Colors::Green;
	//pGO = new GraphicsObject_WireframeConstantColor(pTurretBaseModel, ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::CONSTANT_COLOR), color);
	//Matrix world = getLocalWorldMatrix();
	//_pTurretBaseGraphicsObject->SetWorld(world);
}

TurretBase::~TurretBase()
{
	delete _pTurretBaseGraphicsObject;
}

#pragma region Actions
//-----------------------------------------------------------------------------------------------------------------------------
// Actions
//-----------------------------------------------------------------------------------------------------------------------------
void TurretBase::draw(Camera* pCamera)
{
	//updateWorldMatrix();
	_pTurretBaseGraphicsObject->Render(pCamera);
}

// ---> Action helpers
void TurretBase::updateWorldMatrix()
{
	Matrix world = getWorldMatrix();
	_pTurretBaseGraphicsObject->SetWorld(world);
	//pGO->SetWorld(world);
}

#pragma endregion

#pragma region Setters and Getters

// ---> World
Matrix TurretBase::getWorldMatrix() const
{
	return getLocalWorldMatrix();
}

Matrix TurretBase::getLocalWorldMatrix() const
{
	return getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
}

// ---> Position
void TurretBase::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect TurretBase::getLocalPosition() const
{
	return _localPosition;
}

Matrix TurretBase::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}

// ---> Rotation
void TurretBase::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, localRotation.Y());
}

Matrix TurretBase::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// ---> Scale
void TurretBase::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect TurretBase::getLocalScale() const
{
	return _localScale;
}

Matrix TurretBase::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale);
}

Model* TurretBase::getModel() const
{
	return _pTurretBaseGraphicsObject->getModel();
	//return ModelManager::GetModel("TankBodyHitBox");
}

#pragma endregion