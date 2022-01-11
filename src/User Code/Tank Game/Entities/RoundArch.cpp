#include "RoundArch.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Visualizer.h"
#include "Colors.h"
#include "MathTools.h"
#include "vmath.h"
#include "TimeManager.h"

RoundArch::RoundArch()
	: _pRoundArchGraphicsObject(nullptr),
	_localScale(Vect(1.0f, 1.0f, 1.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localPosition(Vect(0.0f, 0.0f, 0.0f)),
	_renderLevel(0),
	_canMove(false),
	_canDrawDebug(false)
{
	InitiailizeRoundArchGraphicsObject();
}

void RoundArch::InitiailizeRoundArchGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pRoundArchModel = ModelManager::GetModel("RoundArch");
	ShaderObject* pRoundArchShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pRoundArchTexture = TextureManager::GetTexture("StackedBrickTexture");

	_pRoundArchGraphicsObject = new GraphicsObject_TextureLight(pRoundArchModel, pRoundArchShader, pRoundArchTexture, lightColor, lightPosition);

	setColliderModel(_pRoundArchGraphicsObject->getModel(), VolumeHierarchyType::OCTREE, 5);
}

RoundArch::~RoundArch()
{
	delete _pRoundArchGraphicsObject;
}

void RoundArch::initialize(const Vect& position, float rotationY, float uniformScale)
{
	initialize(position, Vect(0.0f, rotationY, 0.0f), Vect(uniformScale, uniformScale, uniformScale));
}

void RoundArch::initialize(const Vect& position, const Vect& rotation, const Vect& scale)
{
	setLocalPosition(position);
	setLocalRotation(rotation);
	setLocalScale(scale);

	Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	_pRoundArchGraphicsObject->SetWorld(world);
	setCollidableGroup<RoundArch>();
	updateCollisionData(_pRoundArchGraphicsObject->getWorld());

	submitDrawRegistration();
	submitCollisionRegistration();

	//submitKeyRegistration(AZUL_KEY::KEY_1, InputEvent::KEY_PRESS);
	//submitKeyRegistration(AZUL_KEY::KEY_2, InputEvent::KEY_PRESS);
	//submitKeyRegistration(AZUL_KEY::KEY_3, InputEvent::KEY_PRESS);

}

#pragma region GameObject Properties

void RoundArch::draw()
{
	//if (_canMove)
	//{
	//	if (Keyboard::GetKeyState(AZUL_KEY::KEY_9))
	//	{
	//		_localPosition[z] += TimeManager::GetElaspedFrameTimeInSeconds() * 10.0f;
	//		Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	//		_pRoundArchGraphicsObject->SetWorld(world);
	//		updateCollisionData(_pRoundArchGraphicsObject->getWorld());
	//	}
	//	if (Keyboard::GetKeyState(AZUL_KEY::KEY_0))
	//	{
	//		_localPosition[z] -= TimeManager::GetElaspedFrameTimeInSeconds() * 10.0f;
	//		Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	//		_pRoundArchGraphicsObject->SetWorld(world);
	//		updateCollisionData(_pRoundArchGraphicsObject->getWorld());
	//	}

	//	if (Keyboard::GetKeyState(AZUL_KEY::KEY_8))
	//	{
	//		_localPosition[y] += TimeManager::GetElaspedFrameTimeInSeconds() * 10.0f;
	//		Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	//		_pRoundArchGraphicsObject->SetWorld(world);
	//		updateCollisionData(_pRoundArchGraphicsObject->getWorld());
	//	}

	//	if (Keyboard::GetKeyState(AZUL_KEY::KEY_7))
	//	{
	//		_localPosition[y] -= TimeManager::GetElaspedFrameTimeInSeconds() * 10.0f;
	//		Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	//		_pRoundArchGraphicsObject->SetWorld(world);
	//		updateCollisionData(_pRoundArchGraphicsObject->getWorld());
	//	}
	//}


	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pRoundArchGraphicsObject->Render(pCamera);

	//if (_canDrawDebug)
	//{
	//	if (_hasCollidedDebug)
	//	{
	//		Visualizer::ShowCollisionVolume(getCollisionVolume(), Colors::Red, _renderLevel);
	//	}
	//	else
	//	{
	//		Visualizer::ShowCollisionVolume(getCollisionVolume(), Colors::Blue, _renderLevel);
	//	}
	//}

	_hasCollidedDebug = false;
}

void RoundArch::keyPressed(AZUL_KEY key)
{
	if (key == AZUL_KEY::KEY_1) _renderLevel -= 1;
	if (key == AZUL_KEY::KEY_2) _renderLevel += 1;
	_renderLevel = MathTools::Clamp(_renderLevel, 0, getCollisionVolume().getMaxDepth());

	if (key == AZUL_KEY::KEY_3)
	{
		_canDrawDebug = !_canDrawDebug;
	}

}

void RoundArch::collision(Tank*)
{
	_hasCollidedDebug = true;
}

void RoundArch::collision(Bullet*)
{
	_hasCollidedDebug = true;
}

void RoundArch::collision(RoundArch*)
{
	_hasCollidedDebug = true;
}

#pragma endregion

#pragma region Setters/Getters

// --> Scale
void RoundArch::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect RoundArch::getLocalScale() const
{
	return _localScale;
}

Matrix RoundArch::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale);
}

// --> Rotation
void RoundArch::setLocalRotation(const Vect& localRotation)
{
	//_localRotation.set(ROT_Y, vmath::radians(localRotation.Y()));
	_localRotation = Matrix(ROT_X, vmath::radians(localRotation[x])) * Matrix(ROT_Y, vmath::radians(localRotation[y])) * Matrix(ROT_X, vmath::radians(localRotation[z]));
}

Matrix RoundArch::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// --> Position
void RoundArch::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect RoundArch::getLocalPosition() const
{
	return _localPosition;
}

Matrix RoundArch::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}
#pragma endregion