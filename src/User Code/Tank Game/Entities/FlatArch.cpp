#include "FlatArch.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Visualizer.h"
#include "Colors.h"
#include "vmath.h"

FlatArch::FlatArch()
	: _pFlatArchGraphicsObject(nullptr),
	_localScale(Vect(1.0f, 1.0f, 1.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localPosition(Vect(0.0f, 0.0f, 0.0f))
{
	InitiailizeFlatArchGraphicsObject();
}

void FlatArch::InitiailizeFlatArchGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pFlatArchModel = ModelManager::GetModel("FlatArch");
	ShaderObject* pFlatArchShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pFlatArchTexture = TextureManager::GetTexture("StackedBrickTexture");

	_pFlatArchGraphicsObject = new GraphicsObject_TextureLight(pFlatArchModel, pFlatArchShader, pFlatArchTexture, lightColor, lightPosition);

	setColliderModel(_pFlatArchGraphicsObject->getModel(), VolumeHierarchyType::OCTREE, 5);
}

FlatArch::~FlatArch()
{
	delete _pFlatArchGraphicsObject;
}

void FlatArch::initialize(const Vect& position, float rotationY, float uniformScale)
{
	initialize(position, Vect(0.0f, rotationY, 0.0f), Vect(uniformScale, uniformScale, uniformScale));
}

void FlatArch::initialize(const Vect& position, const Vect& rotation, const Vect& scale)
{
	setLocalPosition(position);
	setLocalRotation(rotation);
	setLocalScale(scale);

	Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	_pFlatArchGraphicsObject->SetWorld(world);
	setCollidableGroup<FlatArch>();
	updateCollisionData(_pFlatArchGraphicsObject->getWorld());

	submitDrawRegistration();
	submitCollisionRegistration();
}

#pragma region GameObject Properties

void FlatArch::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pFlatArchGraphicsObject->Render(pCamera);

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

void FlatArch::collision(Tank*)
{
	_hasCollidedDebug = true;
}

void FlatArch::collision(Bullet*)
{
	_hasCollidedDebug = true;
}

#pragma endregion

#pragma region Setters/Getters

// --> Scale
void FlatArch::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect FlatArch::getLocalScale() const
{
	return _localScale;
}

Matrix FlatArch::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale);
}

// --> Rotation
void FlatArch::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, vmath::radians(localRotation.Y()));
}

Matrix FlatArch::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// --> Position
void FlatArch::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect FlatArch::getLocalPosition() const
{
	return _localPosition;
}

Matrix FlatArch::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}
#pragma endregion