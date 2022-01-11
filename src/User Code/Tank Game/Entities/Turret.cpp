#include "Turret.h"
#include "ModelManager.h"
#include "TurretHead.h"
#include "TurretBase.h"

#include "Tank.h"

#include "BulletFactory.h"
#include "Bullet.h"

#include "TimeManager.h"
#include "ScreenLog.h"
#include "Visualizer.h"
#include "Colors.h"
#include "MathTools.h"

const float Turret::MAX_HEALTH = 20.0f;

#pragma region De/Initialization

Turret::Turret()
	: _pTarget(nullptr),
	_health(Turret::MAX_HEALTH),
	_bulletDamage(10.0f),
	_canFire(true)
{
	initializeTurretParts();
	Model* pColliderModel = ModelManager::GetModel("TurretHead");
	setColliderModel(pColliderModel, VolumeType::BSPHERE);
}

void Turret::initializeTurretParts()
{
	_pTurretHead = new TurretHead();
	_pTurretHead->setTurnSpeed(90.0f);
	_pTurretHead->setBulletSpawnOffset(Vect(0.0f, 1.0f, 3.0f));

	_pTurretBase = new TurretBase();

	_pTurretHead->attachToTurretBase(_pTurretBase);

	//Model* pModel = _pTurretHull->getModel();
	//Vect& vect = pModel->getCenter();
	//vect.set(0.0f, vect.Y(), vect.Z());
}

void Turret::initialize(const Vect& position, float rotation, float scale)
{
	setTurretPosition(position);
	setTurretRotation(rotation);
	setTurretScale(scale);
	updateTurretWorldMatrix();

	setHealth(Turret::MAX_HEALTH);
	setBulletDamage(10.0f);
	_canFire = true;

	submitSceneEntry();
}

Turret::~Turret()
{
	delete _pTurretHead;
	delete _pTurretBase;
}

#pragma endregion

#pragma region GameObject Properties

// ---> Update
void Turret::update()
{
	turnToTarget();

	updateTurretWorldMatrix();
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

void Turret::updateTurretWorldMatrix()
{
	_pTurretBase->updateWorldMatrix();
	_pTurretHead->updateWorldMatrix();
	updateCollisionData(getWorldMatrix());
	//_pOctree->update(getWorldMatrix());
}

// ---> Draw
void Turret::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pTurretHead->draw(pCamera);
	_pTurretBase->draw(pCamera);
}

// ---> Collisions
void Turret::collision(Bullet*)
{
	_hasCollidedDebug = true;
}
// ---> Alarms
void Turret::alarm1()
{
	submitAlarmRegistration(0.5f, AlarmID::ALARM_1);
	_canFire = true;
}

// ---> Scene Entry and Exit
void Turret::sceneEntry()
{
	submitUpdateRegistration();
	submitDrawRegistration();

	setCollidableGroup<Turret>();
	submitCollisionRegistration();

	submitAlarmRegistration(1.0f, AlarmID::ALARM_1);
}

void Turret::sceneExit()
{
	submitUpdateDeregistration();
	submitDrawDeregistration();

	if (isRegisteredForAlarm(AlarmID::ALARM_1))
	{
		submitAlarmDeregistration(AlarmID::ALARM_1);
	}

	submitCollisionDeregistration();
}

#pragma endregion

#pragma region Actions


// ---> Turn
void Turret::turnTurret(float turnValue)
{
	_pTurretHead->turn(turnValue);
}

void Turret::turnToTarget()
{
	// r = v x w
	// 0 = arccos(v.w/|v||w|)

	if (_pTarget == nullptr) return;

	float distance = (_pTarget->getTankPosition() - getTurretPosition()).magSqr();

	if (distance > (45.0f * 45.0f)) return;

	Visualizer::ShowLineSegment(_pTarget->getTankPosition(), getTurretPosition(), Colors::Orange);

	turnTo(_pTarget->getTankPosition());
	if (_pTarget->getHealth() <= 0)
	{
		_pTarget = nullptr;
	}
	fireBullet();

}

void Turret::turnTo(const Vect& target)
{
	_pTurretHead->turnTo(target);
}

void Turret::applyDamage(float damage)
{
	_health -= damage;
	if (_health <= 0.0f)
	{
		submitSceneExit();
	}
}

// ---> Bullet
void Turret::fireBullet()
{
	if (!_canFire) return;

	Bullet* pBullet = BulletFactory::CreateBullet(getBulletSpawnLocation(), getBulletSpawnRotation());
	pBullet->setDamage(_bulletDamage);
	pBullet->submitSceneEntry();

	_canFire = false;
}

// ---> Actions helpers
Vect Turret::getBulletSpawnLocation() const
{
	return _pTurretHead->getBulletSpawnLocation();
}

Matrix Turret::getBulletSpawnRotation() const
{
	return _pTurretHead->getWorldRotationMatrix();
}

#pragma endregion

#pragma region Setters and Getters

//-----------------------------------------------------------------------------------------------------------------------------
// Turret Properties
//-----------------------------------------------------------------------------------------------------------------------------

// ---> Target
void Turret::setTarget(Tank* pTurret)
{
	_pTarget = pTurret;
}

// ---> Health
void Turret::offsetHealth(float healthOffset)
{
	setHealth(getHealth() + healthOffset);
}

void Turret::setHealth(float health)
{
	_health = MathTools::Clamp(health, 0.0f, Turret::MAX_HEALTH);
}

float Turret::getHealth() const
{
	return _health;
}

float Turret::getHealthPercentage() const
{
	return _health / Turret::MAX_HEALTH;
}

void Turret::setBulletDamage(float bulletDamage)
{
	_bulletDamage = bulletDamage;
}

//-----------------------------------------------------------------------------------------------------------------------------
// World Properties
//-----------------------------------------------------------------------------------------------------------------------------

// ---> World
Matrix Turret::getWorldMatrix() const
{
	return _pTurretHead->getWorldMatrix();
}

// ---> Position
void Turret::setTurretPosition(const Vect& position)
{
	_pTurretBase->setLocalPosition(position);
}

Vect Turret::getTurretPosition() const
{
	return _pTurretBase->getLocalPosition() + _pTurretHead->getLocalPosition() + Vect(0.0f, 1.5f, 0.0f);
}

// ---> Rotation
void Turret::setTurretRotation(float rotation)
{
	Vect TurretBodyRotation = Vect(1.0f, rotation, 1.0f);
	_pTurretBase->setLocalRotation(TurretBodyRotation);

	Vect zeroRotation = Vect(0.0f, 0.0f, 0.0f);
	_pTurretHead->setLocalRotation(zeroRotation);
}

// ---> Scale
void Turret::setTurretScale(float scale)
{
	Vect uniformScale = Vect(1.0f, 1.0f, 1.0f) * scale;
	_pTurretBase->setLocalScale(uniformScale);
}

float Turret::getScale() const
{
	return _pTurretBase->getLocalScale()[x];
}

#pragma endregion