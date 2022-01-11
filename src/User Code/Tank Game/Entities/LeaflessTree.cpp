#include "LeaflessTree.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Visualizer.h"
#include "Colors.h"
#include "vmath.h"

const float LeaflessTree::adjustedScale = 0.5f;

LeaflessTree::LeaflessTree()
	: _pLeaflessTreeGraphicsObject(nullptr),
	_localScale(Vect(1.0f, 1.0f, 1.0f)),
	_localRotation(Matrix(IDENTITY)),
	_localPosition(Vect(0.0f, 0.0f, 0.0f))
{
	InitiailizeLeaflessTreeGraphicsObject();
	setColliderModel(_pLeaflessTreeGraphicsObject->getModel(), VolumeHierarchyType::OCTREE, 5);
}

void LeaflessTree::InitiailizeLeaflessTreeGraphicsObject()
{
	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	Model* pLeaflessTreeModel = ModelManager::GetModel("Tree");
	ShaderObject* pLeaflessTreeShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pLeaflessTreeTexture = TextureManager::GetTexture("TreeTexture");

	_pLeaflessTreeGraphicsObject = new GraphicsObject_TextureLight(pLeaflessTreeModel, pLeaflessTreeShader, pLeaflessTreeTexture, lightColor, lightPosition);
}

LeaflessTree::~LeaflessTree()
{
	delete _pLeaflessTreeGraphicsObject;
}

void LeaflessTree::initialize(const Vect& position, float rotationY, float uniformScale)
{
	initialize(position, Vect(0.0f, rotationY, 0.0f), Vect(uniformScale, uniformScale, uniformScale));
}

void LeaflessTree::initialize(const Vect& position, const Vect& rotation, const Vect& scale)
{
	setLocalPosition(position);
	setLocalRotation(rotation);
	setLocalScale(scale);
	
	Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	_pLeaflessTreeGraphicsObject->SetWorld(world);
	setCollidableGroup<LeaflessTree>();
	updateCollisionData(_pLeaflessTreeGraphicsObject->getWorld());

	submitDrawRegistration();
	submitCollisionRegistration();
}

#pragma region GameObject Properties

void LeaflessTree::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pLeaflessTreeGraphicsObject->Render(pCamera);

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

void LeaflessTree::collision(Tank*)
{
	_hasCollidedDebug = true;
}

void LeaflessTree::collision(Bullet*)
{
	_hasCollidedDebug = true;
}

#pragma endregion

#pragma region Setters/Getters
// --> Scale
void LeaflessTree::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect LeaflessTree::getLocalScale() const
{
	return _localScale;
}

Matrix LeaflessTree::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale * LeaflessTree::adjustedScale);
}

// --> Rotation
void LeaflessTree::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, vmath::radians(localRotation.Y()));
}

Matrix LeaflessTree::getLocalRotationMatrix() const
{
	return _localRotation;
	//return Matrix(Rot3AxisType::ROT_XYZ, vmath::radians(_localRotation.X()), vmath::radians(_localRotation.Y()), vmath::radians(_localRotation.Z()));
}

// --> Position
void LeaflessTree::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect LeaflessTree::getLocalPosition() const
{
	return _localPosition;
}

Matrix LeaflessTree::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}
#pragma endregion
