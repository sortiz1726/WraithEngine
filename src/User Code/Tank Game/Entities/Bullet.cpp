#include "Bullet.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "BulletFactory.h"
#include "Tank.h"
#include "Turret.h"
#include "Warehouse.h"

#include "TimeManager.h"
#include "Visualizer.h"
#include "Colors.h"

const float Bullet::MAX_LIFESPAN = 10.0f;
const float Bullet::ADJUSTED_SCALE = 5.0f;

Bullet::Bullet()
	: _pBulletGraphicsObject(nullptr),
	_pTankOwner(nullptr),
	_speed(70.0f)
{
	Model* pBulletModel = ModelManager::GetModel("Bullet");
	ShaderObject* pBulletShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pBulletTexture = TextureManager::GetTexture("BulletTexture");

	Vect lightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect lightPosition(1.0f, 1.0f, 1.0f, 1.0f);

	_pBulletGraphicsObject = new GraphicsObject_TextureLight(pBulletModel, pBulletShader, pBulletTexture, lightColor, lightPosition);

	setColliderModel(_pBulletGraphicsObject->getModel(), VolumeType::OBB);
}

Bullet::~Bullet()
{
	delete _pBulletGraphicsObject;
}

void Bullet::initialize(const Vect& position, float rotation, float uniformScale)
{
	initialize(position, Matrix(RotType::ROT_Y, rotation), uniformScale);
}

void Bullet::initialize(const Vect& position, const Matrix& rotation, float uniformScale)
{
	setBulletPosition(position);
	setBulletRotation(rotation);
	setBulletScale(uniformScale);

	setSpeed(40.0f);
	setDamage(10.0f);
	setTankOwner(nullptr);

	updateBulletWorldMatrix();
}

void Bullet::updateBulletWorldMatrix()
{
	Matrix world = _localScale * _localRotation * Matrix(TRANS, _localPosition);
	_pBulletGraphicsObject->SetWorld(world);
	updateCollisionData(_pBulletGraphicsObject->getWorld());
}

#pragma region GameObject Properties

// Update
void Bullet::update()
{
	moveForward();
	updateBulletWorldMatrix();

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

// ---> Update helper
void Bullet::moveForward()
{
	Vect fowardDirection = Vect(0, 0, 1.0f) * _localRotation;
	Vect moveOffset = fowardDirection * _speed * TimeManager::GetElaspedFrameTimeInSeconds();
	_localPosition += moveOffset;
}

// Draw
void Bullet::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pBulletGraphicsObject->Render(pCamera);
}

// Alarms
void Bullet::alarm0()
{
	submitSceneExit();
}

void Bullet::collision(Tank* pTankHit)
{
	pTankHit->applyDamage(_damage);
	if (pTankHit->getHealth() <= 0)
	{
		if (_pTankOwner != nullptr)
		{
			_pTankOwner->offsetHealth(100.0f);
			_pTankOwner = nullptr;
		}
	}

	_hasCollidedDebug = true;
	submitSceneExit();
}

void Bullet::collision(Turret* pTurret)
{
	pTurret->applyDamage(_damage);
	if (pTurret->getHealth() <= 0)
	{
		if (_pTankOwner != nullptr)
		{
			_pTankOwner->offsetHealth(10.0f);
			_pTankOwner = nullptr;
		}
	}
	_hasCollidedDebug = true;
	submitSceneExit();
}

void Bullet::collision(Bullet*)
{
	_hasCollidedDebug = true;
	submitSceneExit();
}

void Bullet::collision(Warehouse* pWarehouse)
{
	_hasCollidedDebug = true;
	pWarehouse->applyDamage(_damage);
	submitSceneExit();
}

void Bullet::collision(WindMill*)
{
	_hasCollidedDebug = true;
	submitSceneExit();
}

void Bullet::collision(Cottage*)
{
	_hasCollidedDebug = true;
	submitSceneExit();
}

void Bullet::collision(LeaflessTree*)
{
	_hasCollidedDebug = true;
	submitSceneExit();
}

void Bullet::collision(Wall*)
{
	_hasCollidedDebug = true;
	submitSceneExit();
}

void Bullet::collision(RoundArch*)
{
	_hasCollidedDebug = true;
	submitSceneExit();
}

void Bullet::collision(FlatArch*)
{
	_hasCollidedDebug = true;
	submitSceneExit();
}

void Bullet::terrainCollision()
{
	_hasCollidedDebug = true;
	submitSceneExit();
}

// Scene Entry and Exit
void Bullet::sceneExit()
{
	submitUpdateDeregistration();
	submitDrawDeregistration();

	if (isRegisteredForAlarm(AlarmID::ALARM_0))
	{
		submitAlarmDeregistration(AlarmID::ALARM_0);
	}

	submitCollisionDeregistration();

	_pTankOwner = nullptr;

	BulletFactory::RecycleBullet(this);
}

void Bullet::sceneEntry()
{
	submitUpdateRegistration();
	submitDrawRegistration();
	submitAlarmRegistration(Bullet::MAX_LIFESPAN, AlarmID::ALARM_0);

	setCollidableGroup<Bullet>();
	submitCollisionRegistration();
}

#pragma endregion

#pragma region Setters/Getters

// Bullet Properties
void Bullet::setDamage(float damage)
{
	_damage = damage;
}

void Bullet::setTankOwner(Tank* pTankOwner)
{
	_pTankOwner = pTankOwner;
}

void Bullet::setSpeed(float speed)
{
	_speed = speed;
}

float Bullet::getSpeed() const
{
	return _speed;
}

// World Properties
void Bullet::setBulletPosition(const Vect& position)
{
	_localPosition = position;
}

Vect Bullet::getBulletPosition() const
{
	return _localPosition;
}

void Bullet::setBulletRotation(float rotation)
{
	_localRotation.set(ROT_AXIS_ANGLE, Vect(0.0f, 1.0f, 0.0f), rotation);
}

void Bullet::setBulletRotation(const Matrix& rotation)
{
	_localRotation = rotation;
}

void Bullet::setBulletScale(float scale)
{
	_localScale.set(SCALE, Vect(scale, scale, scale) * Bullet::ADJUSTED_SCALE);
}

#pragma endregion