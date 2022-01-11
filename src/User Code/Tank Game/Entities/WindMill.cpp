#include "WindMill.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Visualizer.h"
#include "Colors.h"
#include "MathTools.h"
#include "vmath.h"

const float WindMill::adjustedScale = 0.7f;

WindMill::WindMill()
	: _pWindMillGraphicsObject(nullptr),
	_localScale(Vect(1.0f, 1.0f, 1.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localPosition(Vect(0.0f, 0.0f, 0.0f)),
	_renderLevel(0)
{
	InitiailizeWindMillGraphicsObject();
	setColliderModel(_pWindMillGraphicsObject->getModel(), VolumeHierarchyType::OCTREE, 5);
}

void WindMill::InitiailizeWindMillGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pWindMillModel = ModelManager::GetModel("WindMill");
	ShaderObject* pWindMillShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pWindMillTexture = TextureManager::GetTexture("WindMillTexture");

	_pWindMillGraphicsObject = new GraphicsObject_TextureLight(pWindMillModel, pWindMillShader, pWindMillTexture, lightColor, lightPosition);
}

WindMill::~WindMill()
{
	delete _pWindMillGraphicsObject;
}

void WindMill::initialize(const Vect& position, float rotationY, float uniformScale)
{
	initialize(position, Vect(0.0f, rotationY, 0.0f), Vect(uniformScale, uniformScale, uniformScale));
}

void WindMill::initialize(const Vect& position, const Vect& rotation, const Vect& scale)
{
	setLocalPosition(position);
	setLocalRotation(rotation);
	setLocalScale(scale);
	
	Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	_pWindMillGraphicsObject->SetWorld(world);
	setCollidableGroup<WindMill>();
	updateCollisionData(_pWindMillGraphicsObject->getWorld());

	submitDrawRegistration();
	submitCollisionRegistration();

	//submitKeyRegistration(AZUL_KEY::KEY_1, InputEvent::KEY_PRESS);
	//submitKeyRegistration(AZUL_KEY::KEY_2, InputEvent::KEY_PRESS);
}

#pragma region GameObject Properites

void WindMill::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pWindMillGraphicsObject->Render(pCamera);

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

void WindMill::keyPressed(AZUL_KEY key)
{
	if (key == AZUL_KEY::KEY_1) _renderLevel -= 1;
	if (key == AZUL_KEY::KEY_2) _renderLevel += 1;
	_renderLevel = MathTools::Clamp(_renderLevel, 0, getCollisionVolume().getMaxDepth());
}

void WindMill::collision(Tank*)
{
	_hasCollidedDebug = true;
}

void WindMill::collision(Bullet*)
{
	_hasCollidedDebug = true;
}

#pragma endregion

#pragma region Setters/Getters

// --> Scale
void WindMill::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect WindMill::getLocalScale() const
{
	return _localScale;
}

Matrix WindMill::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale * WindMill::adjustedScale);
}

// --> Rotation
void WindMill::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, vmath::radians(localRotation.Y()));
}

Matrix WindMill::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// --> Position
void WindMill::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect WindMill::getLocalPosition() const
{
	return _localPosition;
}

Matrix WindMill::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}
#pragma endregion
