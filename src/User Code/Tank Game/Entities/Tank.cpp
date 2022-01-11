#include "Tank.h"
#include "ModelManager.h"
#include "TankHull.h"
#include "TankTurret.h"
#include "TankBarrel.h"

#include "TankController.h"
#include "TankFactory.h"
#include "BulletFactory.h"
#include "Bullet.h"

#include "RecycleTankStrategyCollection.h"

#include "TimeManager.h"
#include "ScreenLog.h"
#include "Visualizer.h"
#include "Colors.h"
#include "MathTools.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Terrain.h"

#include "CollisionVolumeBSphere.h"

const float Tank::MAX_HEALTH = 100.0f;
const float Tank::MAX_SPEED = 12.0f;
const int Tank::MAX_BULLET_COUNT = 3;

#pragma region De/Initialization

Tank::Tank()
	: _pController(nullptr),
	_pTarget(nullptr),
	_health(Tank::MAX_HEALTH),
	_bulletDamage(10.0f),
	_pThirdPersonCamera(nullptr)
{
	initializeTankParts();
	Model* pColliderModel = ModelManager::GetModel("TankBodyHitBox");
	setColliderModel(pColliderModel, VolumeType::OBB);

	_cameraPositionOffset.set(Vect(0.0f, 4.0f, -20.0f));
	_cameraLookAtOffset.set(Vect(0.0f, 1.0f, 1.0f));
	_pThirdPersonCamera = CameraManager::CreateCamera(_cameraPositionOffset, _cameraLookAtOffset);
}

void Tank::initializeTankParts()
{
	_pTankHull = new TankHull();
	_pTankHull->setMoveSpeed(12.0f);
	_pTankHull->setTurnSpeed(30.0f);

	_pTankTurret = new TankTurret();
	_pTankTurret->setTurnSpeed(20.0f);
	_pTankTurret->setLocalPosition(Vect(0.0f, 1.75f, 0.0f));

	_pTankBarrel = new TankBarrel();
	_pTankBarrel->setLocalPosition(Vect(0.0f, 0.35f, 1.25f));
	_pTankBarrel->setBulletSpawnOffset(Vect(0.0f, 0.0f, 3.0f));

	_pTankTurret->attachToTankHull(_pTankHull);
	_pTankBarrel->attachToTankTurret(_pTankTurret);

	Model* pModel = ModelManager::GetModel("TankBodyHitBox");
	Vect& vect = pModel->getCenter();
	vect[x] = 0.0f;
}

void Tank::initialize(TankController* pController, const Vect& position, float rotation, float scale)
{
	setController(pController);
	setTankPosition(position);
	setTankRotation(rotation);
	setTankScale(scale);
	updateTankWorldMatrix();

	setHealth(Tank::MAX_HEALTH);
	setBulletCount(Tank::MAX_BULLET_COUNT);
	setBulletDamage(10.0f);
	setBulletSpeed(40.0f);
	setMoveSpeed(Tank::MAX_SPEED);
	_velocity = Vect(0.0f, 0.0f, 0.0f, 0.0f);
	setRecycleStrategy(&RecycleTankStrategyCollection::RecycleToFactory);

	submitSceneEntry();
}

Tank::~Tank()
{
	delete _pTankHull;
	delete _pTankTurret;
	delete _pTankBarrel;
	delete _pThirdPersonCamera;
}

#pragma endregion

#pragma region GameObject Properties

// ---> Update
void Tank::update()
{
	updateTankWorldMatrix();
	updateTankCamera();

	//_hasCollidedDebug = Keyboard::GetKeyState(AZUL_KEY::KEY_N);

	//Model* pColliderModel = ModelManager::GetModel("TankBodyHitBox");


	//if (Keyboard::GetKeyState(AZUL_KEY::KEY_Z))
	//{
	//	setColliderModel(pColliderModel, VolumeType::BSPHERE);
	//}
	//if (Keyboard::GetKeyState(AZUL_KEY::KEY_X))
	//{
	//	setColliderModel(pColliderModel, VolumeType::AABB);
	//}
	//if (Keyboard::GetKeyState(AZUL_KEY::KEY_C))
	//{
	//	setColliderModel(pColliderModel, VolumeType::OBB);
	//}
	//if (Keyboard::GetKeyState(AZUL_KEY::KEY_V))
	//{
	//	setColliderModel(pColliderModel, VolumeHierarchyType::OCTREE, 4);
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

void Tank::updateTankWorldMatrix()
{
	_pTankHull->updateWorldMatrix();
	_pTankTurret->updateWorldMatrix();
	_pTankBarrel->updateWorldMatrix();
	updateCollisionData(getWorldMatrix());
}

void Tank::updateTankCamera()
{
	Matrix world = _pTankTurret->getWorldMatrix();
	Vect CamPos = _cameraPositionOffset * world;
	Vect CamLookAt = _cameraLookAtOffset * world;

	_pThirdPersonCamera->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), CamLookAt, CamPos);
	_pThirdPersonCamera->updateCamera();
}

// ---> Draw
void Tank::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pTankHull->draw(pCamera);
	_pTankTurret->draw(pCamera);
	_pTankBarrel->draw(pCamera);
}

// ---> Collisions
void Tank::collision(Tank*)
{
	_hasCollidedDebug = true;
}

void Tank::collision(Bullet*)
{
	_hasCollidedDebug = true;
}

void Tank::collision(Warehouse*)
{
	_hasCollidedDebug = true;
}

void Tank::collision(WindMill*)
{
	_hasCollidedDebug = true;
}

void Tank::collision(Cottage*)
{
	_hasCollidedDebug = true;
}

void Tank::collision(RoundArch*)
{
	_hasCollidedDebug = true;
}

void Tank::collision(LeaflessTree*)
{
	_hasCollidedDebug = true;
}

void Tank::terrainCollision()
{
	//const Terrain* pTerrain = SceneManager::GetCurrentScene()->getTerrain();
	//Vect position = getTankPosition();
	//Vect terrainPosition = pTerrain->computePointOnTerrainObject(position);
	//position[y] = terrainPosition[y];
	//setTankPosition(position);
	_hasCollidedDebug = true;
}

// ---> Alarms
void Tank::alarm1()
{
	setBulletCount(Tank::MAX_BULLET_COUNT);
}

// ---> Scene Entry and Exit
void Tank::sceneEntry()
{
	_pController->initialize();

	submitUpdateRegistration();
	submitDrawRegistration();

	setCollidableGroup<Tank>();
	submitCollisionRegistration();
}

void Tank::sceneExit()
{
	_pController->deinitialize();

	submitUpdateDeregistration();
	submitDrawDeregistration();

	if (isRegisteredForAlarm(AlarmID::ALARM_1))
	{
		submitAlarmDeregistration(AlarmID::ALARM_1);
	}

	submitCollisionDeregistration();

	_pRecycleStrategy->recycle(this);
	//TankFactory::RecycleTank(this);
}

#pragma endregion

#pragma region Actions

// ---> move
void Tank::move(float moveValue)
{
	Vect oldPosition = getTankPosition();
	//ScreenLog::Add("Tank_oldPosition: (%3.1f, %3.1f, %3.1f)", getTankPosition()[x], getTankPosition()[y], getTankPosition()[z]);

	_moveValue = moveValue;
	Vect moveDirection = Vect(0.0f, 0.0f, moveValue);
	_pTankHull->move(moveDirection);

	_velocity = (getTankPosition() - oldPosition) * (1.0f / TimeManager::GetElaspedFrameTimeInSeconds());
	//ScreenLog::Add("Tank_newPosition: (%3.1f, %3.1f, %3.1f)", _velocity[x], _velocity[y], _velocity[z]);
}

// ---> Turn
void Tank::turnHull(float turnValue)
{
	if (_moveValue == -1.0f)
	{
		turnValue *= -1;
	}
	_pTankHull->turn(turnValue);
}

void Tank::turnTurret(float turnValue)
{
	_pTankTurret->turn(turnValue);
}

void Tank::turnToTarget()
{
	// r = v x w
	// 0 = arccos(v.w/|v||w|)
	if (_pTarget != nullptr)
	{
		turnTo(_pTarget->getTankPosition());
		if (_pTarget->getHealth() <= 0)
		{
			_pTarget = nullptr;
		}
	}
}

void Tank::turnTo(const Vect& target)
{
	_pTankHull->turnTo(target);
	_pTankTurret->turnTo(target);
}

void Tank::applyDamage(float damage)
{
	_health -= damage;
	if (_health <= 0.0f)
	{
		submitSceneExit();
	}
	//Trace::out("Tank_applyDamage: took %3.1f damage, only have %3.1f health left\n", damage, _health);
}

// ---> Bullet
void Tank::fireBullet()
{
	if (getBulletCount() > 0)
	{
		Bullet* pBullet = BulletFactory::CreateBullet(getBulletSpawnLocation(), getBulletSpawnRotation());
		pBullet->setDamage(_bulletDamage);
		pBullet->setTankOwner(this);
		pBullet->setSpeed(getBulletSpeed());
		pBullet->submitSceneEntry();
		setBulletCount(getBulletCount() - 1);
	}
}

void Tank::reloadBullets()
{
	if (!isRegisteredForAlarm(AlarmID::ALARM_1))
	{
		submitAlarmRegistration(3.0f, AlarmID::ALARM_1);
		_bulletCount = 0;
	}
}

// ---> Actions helpers
Vect Tank::getBulletSpawnLocation() const
{
	return _pTankBarrel->getBulletSpawnLocation();
}

Matrix Tank::getBulletSpawnRotation() const
{
	return _pTankBarrel->getWorldRotationMatrix();
}

#pragma endregion

#pragma region Setters and Getters

//-----------------------------------------------------------------------------------------------------------------------------
// Tank Properties
//-----------------------------------------------------------------------------------------------------------------------------

// ---> Target
void Tank::setTarget(Tank* pTank)
{
	_pTarget = pTank;
}

Tank* Tank::getTarget() const
{
	return _pTarget;
}

// ---> Controller
void Tank::setController(TankController* pController)
{
	_pController = pController;
	_pController->setTankToControl(this);
}

void Tank::setControlType(TankControlType controlType)
{
	_controlType = controlType;
}

// ---> Health
void Tank::offsetHealth(float healthOffset)
{
	setHealth(getHealth() + healthOffset);
}

void Tank::setHealth(float health)
{
	_health = MathTools::Clamp(health, 0.0f, Tank::MAX_HEALTH);
}

float Tank::getHealth() const
{
	return _health;
}

float Tank::getHealthPercentage() const
{
	return _health / Tank::MAX_HEALTH;
}

// ---> Bullet
void Tank::setBulletCount(int bulletCount)
{
	_bulletCount = bulletCount;
	if (_bulletCount <= 0)
	{
		reloadBullets();
	}
}

int Tank::getBulletCount() const
{
	return _bulletCount;
}

void Tank::setBulletDamage(float bulletDamage)
{
	_bulletDamage = bulletDamage;
}

// ---> Movement
void Tank::setMoveSpeed(float moveSpeed)
{
	_pTankHull->setMoveSpeed(moveSpeed);
}

const Vect& Tank::getVelocity() const
{
	return _velocity;
}

void Tank::setBulletSpeed(float bulletSpeed)
{
	_bulletSpeed = bulletSpeed;
}

float Tank::getBulletSpeed() const
{
	return _bulletSpeed;
}

// ---> Camera
Camera* Tank::getThirdPersonCamera() const
{
	return _pThirdPersonCamera;
}

void Tank::setRecycleStrategy(RecycleTankStrategy* pRecycleStrategy)
{
	_pRecycleStrategy = pRecycleStrategy;
}

//-----------------------------------------------------------------------------------------------------------------------------
// World Properties
//-----------------------------------------------------------------------------------------------------------------------------

// ---> World
Matrix Tank::getWorldMatrix() const
{
	return _pTankHull->getLocalWorldMatrix();
}

// ---> Position
void Tank::setTankPosition(const Vect& position)
{
	_pTankHull->setLocalPosition(position);
}

Vect Tank::getTankPosition() const
{
	return _pTankHull->getLocalPosition(); //+ _pTankTurret->getLocalPosition();
}

// ---> Rotation
void Tank::setTankRotation(float rotation)
{
	Vect tankBodyRotation = Vect(1.0f, rotation, 1.0f);
	_pTankHull->setLocalRotation(tankBodyRotation);

	Vect zeroRotation = Vect(0.0f, 0.0f, 0.0f);
	_pTankTurret->setLocalRotation(zeroRotation);
	_pTankBarrel->setLocalRotation(zeroRotation);
}

void Tank::setTankUpAxis(const Vect& axis)
{
	_pTankHull->setUpAxis(axis);
}

// ---> Scale
void Tank::setTankScale(float scale)
{
	Vect uniformScale = Vect(1.0f, 1.0f, 1.0f) * scale;
	_pTankHull->setLocalScale(uniformScale);
}

float Tank::getScale() const
{
	return _pTankHull->getLocalScale()[x];
}

#pragma endregion