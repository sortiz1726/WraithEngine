#include "Warehouse.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "SceneManager.h"
#include "Visualizer.h"
#include "Colors.h"

#include "DestroyMonitor.h"

#include "vmath.h"

const float Warehouse::adjustedScale = 1.0f / 5.0f;

Warehouse::Warehouse()
	: _pWarehouseGraphicsObject(nullptr),
	_health(40.0f),
	_pDestroyMonitor(nullptr)
{
	Model* pWarehouseModel = ModelManager::GetModel("Warehouse");
	ShaderObject* pTextureShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pWarehouseTexture = TextureManager::GetTexture("WarehouseTexture");

	_pWarehouseGraphicsObject = new GraphicsObject_TextureFlat(pWarehouseModel, pTextureShader, pWarehouseTexture);

	Matrix world = Matrix(IDENTITY);
	_pWarehouseGraphicsObject->SetWorld(world);

	setCollidableGroup<Warehouse>();
	setColliderModel(_pWarehouseGraphicsObject->getModel(), VolumeType::OBB);
}

Warehouse::~Warehouse()
{
	delete _pWarehouseGraphicsObject;
}

void Warehouse::initialize(const Vect& position, float rotationY, float uniformScale)
{
	setLocalPosition(position);
	setLocalRotation(rotationY);
	setLocalScale(uniformScale);

	updateWorldMatrix();

	submitDrawRegistration();
	submitCollisionRegistration();
}

#pragma region GameObject Properties

void Warehouse::collision(Tank*)
{
	_hasCollidedDebug = true;
}

void Warehouse::collision(Bullet*)
{
	_hasCollidedDebug = true;
}

void Warehouse::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pWarehouseGraphicsObject->Render(pCamera);

	//Model* pColliderModel = _pWarehouseGraphicsObject->getModel();


	//if (Keyboard::GetKeyState(AZUL_KEY::KEY_1))
	//{
	//	setColliderModel(pColliderModel, VolumeType::BSPHERE);
	//	updateWorldMatrix();
	//}
	//if (Keyboard::GetKeyState(AZUL_KEY::KEY_2))
	//{
	//	setColliderModel(pColliderModel, VolumeType::AABB);
	//	updateWorldMatrix();
	//}
	//if (Keyboard::GetKeyState(AZUL_KEY::KEY_3))
	//{
	//	setColliderModel(pColliderModel, VolumeType::OBB);
	//	updateWorldMatrix();
	//}

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

void Warehouse::sceneExit()
{
	submitCollisionDeregistration();
	submitDrawDeregistration();
}

#pragma endregion

void Warehouse::updateWorldMatrix()
{
	Matrix world = getLocalScaleMatrix() * getLocalRotationMatrix() * getLocalPositionMatrix();
	_pWarehouseGraphicsObject->SetWorld(world);
	updateCollisionData(world);
}

float Warehouse::getHealthPercentage() const
{
	return 0.0f;
}

void Warehouse::applyDamage(float damage)
{
	_health -= damage;

	if (_health <= 0.0f)
	{
		if (_pDestroyMonitor != nullptr)
		{
			_pDestroyMonitor->removeBuildingToDestroy(this);
		}
		submitCollisionDeregistration();
		submitDrawDeregistration();
	}
}

void Warehouse::setDestroyMonitor(DestroyMonitor* pDestroyMonitor)
{
	_pDestroyMonitor = pDestroyMonitor;
}

#pragma region Setters/Getters

//-----------------------------------------------------------------------------------------------------------------------------
// Setters/Getters
//-----------------------------------------------------------------------------------------------------------------------------

// --> Scale
void Warehouse::setLocalScale(float uniformScale)
{
	setLocalScale(Vect(uniformScale, uniformScale, uniformScale));
}

void Warehouse::setLocalScale(const Vect& localScale)
{
	_localScale.set(localScale);
}

Vect Warehouse::getLocalScale() const
{
	return _localScale;
}

Matrix Warehouse::getLocalScaleMatrix() const
{
	return Matrix(SCALE, _localScale * Warehouse::adjustedScale);
}

// --> Rotation
void Warehouse::setLocalRotation(float rotationY)
{
	setLocalRotation(Vect(0.0f, rotationY, 0.0f));
}

void Warehouse::setLocalRotation(const Vect& localRotation)
{
	_localRotation.set(ROT_Y, vmath::radians(localRotation.Y()));
}

Matrix Warehouse::getLocalRotationMatrix() const
{
	return _localRotation;
}

// --> Position
void Warehouse::setLocalPosition(const Vect& localPosition)
{
	_localPosition.set(localPosition);
}

Vect Warehouse::getLocalPosition() const
{
	return _localPosition;
}

Matrix Warehouse::getLocalPositionMatrix() const
{
	return Matrix(TRANS, _localPosition);
}
#pragma endregion