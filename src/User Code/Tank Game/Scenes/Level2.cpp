#include "Level2.h"
#include "CameraManager.h"
#include "CameraSwitcher.h"
#include "GameController.h"
#include "TankKillMonitor.h"
#include "DestinationMonitor.h"
#include "DestroyMonitor.h"
#include "AlarmController.h"

#include "GroundPlane.h"
#include "WorldAxes.h"
#include "TankFactory.h"
#include "Tank.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "Turret.h"
#include "Marker.h"

#include "Cottage.h"
#include "Warehouse.h"
#include "LeaflessTree.h"
#include "WindMill.h"
#include "Campfire.h"
#include "Wall.h"
#include "RoundArch.h"
#include "FlatArch.h"

#include "SceneryBuilder.h"
#include "HealthBar.h"
#include "AmmoBar.h"
#include "Reticle.h"

#include "SceneChanger.h"
#include "TestScene3.h"
#include "TestScene.h"
#include "Level3.h"
#include "MainMenu.h"

#include "vmath.h"
#include "WallBuilder.h"

void Level2::initialize()
{
	SetCollisionTests();
	setTerrain("Level2Terrain");
	initializedCameras();
	_pGroundPlane = new GroundPlane("RedSandTexture");

	// Tanks
	Tank* _pPlayerTank = TankFactory::CreateTank(TankControlType::PLAYER_CONTROL, Vect(0.0f, 0.0f, 0.0f));
	_pPlayerTank->setBulletDamage(35.0f);

	_pPlayerHealthBar = new HealthBar(_pPlayerTank);
	_pAmmoBar = new AmmoBar();
	_pAmmoBar->setTank(_pPlayerTank);

	// Game Controller
	_pGameController = new GameController();
	_pGameController->setTarget(_pPlayerTank);
	_pGameController->setCurrentScene(new Level2());
	_pGameController->setNextScene(new Level3());

	_pTankKillMonitor = new TankKillMonitor();
	_pTankKillMonitor->setTarget(_pPlayerTank);
	_pTankKillMonitor->setLeftToKill(60);
	_pTankKillMonitor->setDrawText(false);
	_pTankKillMonitor->setMaxNumberOfEnemyTanks(4);
	_pTankKillMonitor->setGameControllerToNotify(_pGameController);

	_pDestroyMonitor = new DestroyMonitor();
	_pDestroyMonitor->setGameControllerToNotify(_pGameController);

	_pAlarmController = new AlarmController();
	_pAlarmController->setGameControllerToNotify(_pGameController);
	_pAlarmController->setTriggerTime(60.0f * 3.0f);
	_pAlarmController->startTimer();

	// Camera Switcher
	Camera* pPlayerCamera = _pPlayerTank->getThirdPersonCamera();
	setCurrentCamera(pPlayerCamera);

	// Enviroment
	//initializeArches();
	initializeWalls();
	_pSceneryBuilder = new SceneryBuilder();
	initializeTrees();
	initializeCottages();
	initializeWarehouses();
	initializeWindMills();
	initializeCampfires();
	initializeTurrets(_pPlayerTank);
	initializeArches();

	_pCameraSwitcher = new CameraSwitcher();
	_pCameraSwitcher->addCamera(_pPlayerTank->getThirdPersonCamera());
	_pCameraSwitcher->addCamera(_pTopViewCamera, CameraController::Status::OPERATIONAL);
	_pCameraSwitcher->addCamera(_pSideViewCamera, CameraController::Status::OPERATIONAL);

	_gameObjects.push_back(new Reticle());
}

void Level2::initializedCameras()
{
	Vect topViewPosition(0.0f, 150.0f, -0.1f);
	Vect topViewLookAt(0.0f, 0.0f, 0.0f);
	_pTopViewCamera = CameraManager::CreateCamera(topViewPosition, topViewLookAt);

	Vect sideViewPosition(50.0f, 0.0f, 0.0f);
	Vect sideViewLookAt(0.0f, 0.0f, 0.0f);
	_pSideViewCamera = CameraManager::CreateCamera(sideViewPosition, sideViewLookAt);
}

void Level2FunctionCode()
{
	//pTurret = new Turret();
//pTurret->initialize(Vect(50.0f, 0.0f, 50.0f), 3.14f / 2.0f);
//pTurret->setBulletDamage(1.0f);
//pTurret->setTarget(_pPlayerTank);

	//
//_pAlarmController = new AlarmController();
//_pAlarmController->setGameControllerToNotify(_pGameController);
//_pAlarmController->setTriggerTime(61.0f);
//_pAlarmController->startTimer();

//pDestinationMonitor = new DestinationMonitor();
//
//pDestinationMonitor->setGameControllerToNotify(_pGameController);
//pDestinationMonitor->setTarget(_pPlayerTank);
//pDestinationMonitor->createMarker(Vect(0.0f, 0.0f, 10.0f));
//pDestinationMonitor->createMarker(Vect(0.0f, 0.0f, 30.0f));
//pDestinationMonitor->createMarker(Vect(30.0f, 0.0f, 30.0f));
//pDestinationMonitor->createMarker(Vect(0.0f, 0.0f, -10.0f));

//pDestroyMonitor = new DestroyMonitor();
//pDestroyMonitor->setGameControllerToNotify(_pGameController);

		//_pCameraSwitcher = new CameraSwitcher();
	//_pCameraSwitcher->addCamera(_pPlayerTank->getThirdPersonCamera());
	//_pCameraSwitcher->addCamera(_pTopViewCamera, CameraController::Status::OPERATIONAL);
	//_pCameraSwitcher->addCamera(_pSideViewCamera, CameraController::Status::OPERATIONAL);

	//_pSceneChanger = new SceneChanger();
	//_pSceneChanger->setPreviousScene(new TestScene3());
	//_pSceneChanger->setNextScene(new TestScene());

	//std::vector<Vect> treePositions;
	//float scale = 4.0f;
	//treePositions.push_back(Vect(3.0f, 0.0f, -4.0f) * scale);
	//treePositions.push_back(Vect(5.0f, 0.0f, 0.0f) * scale);
	//treePositions.push_back(Vect(0.0f, 0.0f, 7.0f) * scale);
	//treePositions.push_back(Vect(-4.0f, 0.0f, 3.0f) * scale);
	//treePositions.push_back(Vect(3.0f, 0.0f, 4.0f) * scale);
	//
	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		float xOffset = static_cast<float>((i - 5) * 80);
	//		float zOffset = static_cast<float>((j - 5) * 80);
	//		Vect offset = Vect(xOffset, 0.0, zOffset);
	//		for (const auto& treePosition : treePositions)
	//		{
	//			Vect spawnPosition = treePosition + offset;
	//
	//			if (canSpawnTreeHere(spawnPosition))
	//			{
	//				_pSceneryBuilder->buildLeaflessTree(spawnPosition);
	//			}
	//		}
	//	}
	//}
}

void Level2::SetCollisionTests()
{
	// Setting collision to tests
	setCollisionSelf<Tank>();
	setCollisionPair<Tank, Bullet>();
	setCollisionPair<Tank, Marker>();
	setCollisionPair<Tank, Wall>();

	setCollisionSelf<Bullet>();
	setCollisionPair<Bullet, Warehouse>();
	setCollisionPair<Bullet, WindMill>();
	setCollisionPair<Bullet, Cottage>();
	setCollisionPair<Bullet, LeaflessTree>();
	setCollisionPair<Bullet, Turret>();
	setCollisionPair<Bullet, Wall>();
	setCollisionPair<Bullet, RoundArch>();
	setCollisionPair<Bullet, FlatArch>();
}

#pragma region Initialize Scenery

void Level2::initializeArches()
{
	_pSceneryBuilder->buildRoundArch(Vect(0.0f, 0.0f, 0.0f));
	_pSceneryBuilder->buildRoundArch(Vect(0.0f, 0.0f, 20.0f));
	_pSceneryBuilder->buildRoundArch(Vect(0.0f, 0.0f, 50.0f));

	_pSceneryBuilder->buildRoundArch(Vect(17.0f, 0.0f, 150.0f));
	_pSceneryBuilder->buildRoundArch(Vect(-19.0f, 0.0f, 150.0f));

	_pSceneryBuilder->buildRoundArch(Vect(32.0f, 0.0f, 225.0f), 90.0f);
	_pSceneryBuilder->buildRoundArch(Vect(-32.0f, 0.0f, 227.0f), 90.0f);

	_pSceneryBuilder->buildFlatArch(Vect(2.5f, 0.0f, 260.0f), 0.0f, 1.5f);
	_pSceneryBuilder->buildFlatArch(Vect(0.0f, 0.0f, 225.0f), 90.0f, 1.5f);
	_pSceneryBuilder->buildFlatArch(Vect(0.0f, 0.0f, 163.0f), 90.0f, 1.5f);
	//_pSceneryBuilder = new SceneryBuilder();
	//initializeNorthStreet();
	//initializeEastStreet();
	//initializeSouthStreet();
	//initializeWestStreet();

	//initializeWarehouses();
	//initializeCottages();
	//initializeTrees();
}

void Level2::initializeWalls()
{
	_pWallBuilder = new WallBuilder();

	int length = 21;

	float tankWidth = 6.0f;

	Vect buildPosition = Vect(0.0f, 0.0f, 50.0f);
	buildPosition[x] -= (tankWidth * 1.0f);
	float buildAngle = 0.0f;

	_pWallBuilder->buildWalls(buildPosition, -180.0f, length / 2);
	buildPosition[x] += (tankWidth * 2.0f);

	buildPosition = _pWallBuilder->buildWalls(buildPosition, buildAngle, length / 2);
	buildAngle += -90.0f;

	buildPosition = _pWallBuilder->buildWalls(buildPosition, buildAngle, length);
	buildAngle += -90.0f;

	buildPosition = _pWallBuilder->buildWalls(buildPosition, buildAngle, length);
	buildAngle += -90.0f;

	buildPosition = _pWallBuilder->buildWalls(buildPosition, buildAngle, length);
	buildAngle += -90.0f;
}

void Level2::initializeTurrets(Tank* pTarget)
{
	std::vector<Vect> turretPositions;

	turretPositions.push_back(Vect(0.0f, 0.0f, 100.0f));

	// bottom
	turretPositions.push_back(Vect(75.0f, 0.0f, 80.0f));
	turretPositions.push_back(Vect(75.0f, 0.0f, 100.0f));
	turretPositions.push_back(Vect(100.0f, 0.0f, 120.0f));

	turretPositions.push_back(Vect(-75.0f, 0.0f, 80.0f));
	turretPositions.push_back(Vect(-75.0f, 0.0f, 100.0f));
	turretPositions.push_back(Vect(-100.0f, 0.0f, 120.0f));

	// middle
	turretPositions.push_back(Vect(100.0f, 0.0f, 135.0f));
	turretPositions.push_back(Vect(75.0f, 0.0f, 170.0f));
	turretPositions.push_back(Vect(100.0f, 0.0f, 200.0f));

	turretPositions.push_back(Vect(-100.0f, 0.0f, 135.0f));
	turretPositions.push_back(Vect(-75.0f, 0.0f, 170.0f));
	turretPositions.push_back(Vect(-100.0f, 0.0f, 200.0f));

	// Top
	turretPositions.push_back(Vect(90.0f, 0.0f, 220.0f));
	turretPositions.push_back(Vect(75.0f, 0.0f, 250.0f));
	turretPositions.push_back(Vect(80.0f, 0.0f, 300.0f));

	turretPositions.push_back(Vect(-90.0f, 0.0f, 220.0f));
	turretPositions.push_back(Vect(-75.0f, 0.0f, 250.0f));
	turretPositions.push_back(Vect(-80.0f, 0.0f, 300.0f));

	for (auto& positions : turretPositions)
	{
		Turret* pTurret = new Turret();
		pTurret->initialize(positions);
		pTurret->setTarget(pTarget);
		pTurret->setBulletDamage(1.0f);
		_gameObjects.push_back(pTurret);
	}
}

void Level2::initializeNorthStreet()
{
	//pDestroyMonitor->addBuildingToDestroy(_pSceneryBuilder->buildWarehouse(Vect(15.0f, 0.0f, 15.0f), 45.0f + 180.0f, 0.7f));
	_pSceneryBuilder->buildCottage(Vect(-15.0f, 0.0f, 15.0f), -45.0f);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, 25.0f), 90.0f);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, 25.0f), 90.0f);

	_pSceneryBuilder->buildLeaflessTree(Vect(10.0f, 0.0f, 40.0f), 90.0f);
	_pSceneryBuilder->buildLeaflessTree(Vect(-10.0f, 0.0f, 32.0f), 90.0f, 0.8f);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, 40.0f), 90.0f);
	_pSceneryBuilder->buildCampfire(Vect(10.0f, 0.0f, 33.0f), 90.0f, 1.0f);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, 53.0f), 90.0f);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, 53.0f), 90.0f);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, 67.0f), 90.0f);
	_pSceneryBuilder->buildWarehouse(Vect(-13.0f, 0.0f, 66.0f), 90.0f, 0.7f);

	_pSceneryBuilder->buildWindMill(Vect(0.0f, 0.0f, 86.0f), 180.0f);

	// Trees
	//_pSceneryBuilder->buildLeaflessTree(Vect(25.0f, 0.0, 20.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-25.0f, 0.0, 20.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(35.0f, 0.0, 20.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-35.0f, 0.0, 20.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(35.0f, 0.0, 20.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-35.0f, 0.0, 20.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(45.0f, 0.0, 34.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-45.0f, 0.0, 40.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(45.0f, 0.0, 56.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-45.0f, 0.0, 40.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(35.0f, 0.0, 46.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-35.0f, 0.0, 65.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(50.0f, 0.0, 50.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-50.0f, 0.0, 50.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(40.0f, 0.0, 50.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-40.0f, 0.0, 50.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(30.0f, 0.0, 35.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-30.0f, 0.0, 35.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(30.0f, 0.0, 50.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-30.0f, 0.0, 50.0f));
}

void Level2::initializeEastStreet()
{
	Matrix rotateY = Matrix(ROT_Y, vmath::radians(-90.0f));
	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, 25.0f) * rotateY);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, 25.0f) * rotateY);

	_pSceneryBuilder->buildLeaflessTree(Vect(10.0f, 0.0f, 40.0f) * rotateY);
	_pSceneryBuilder->buildLeaflessTree(Vect(-10.0f, 0.0f, 32.0f) * rotateY, 0.0, 0.8f);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, 40.0f) * rotateY);
	_pSceneryBuilder->buildCampfire(Vect(10.0f, 0.0f, 33.0f) * rotateY, 0.0f, 1.0f);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, 53.0f) * rotateY);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, 53.0f) * rotateY);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, 67.0f) * rotateY);
	_pSceneryBuilder->buildWarehouse(Vect(-13.0f, 0.0f, 66.0f) * rotateY, 0.0f, 0.7f);

	_pSceneryBuilder->buildWindMill(Vect(0.0f, 0.0f, 86.0f) * rotateY, 90.0f);

	// Trees
	//_pSceneryBuilder->buildLeaflessTree(Vect(25.0f, 0.0, 20.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-25.0f, 0.0, 20.0f) * rotateY);
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(35.0f, 0.0, 20.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-35.0f, 0.0, 20.0f) * rotateY);
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(35.0f, 0.0, 20.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-35.0f, 0.0, 20.0f) * rotateY);
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(45.0f, 0.0, 34.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-45.0f, 0.0, 40.0f) * rotateY);
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(45.0f, 0.0, 56.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-45.0f, 0.0, 40.0f) * rotateY);
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(35.0f, 0.0, 46.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-35.0f, 0.0, 65.0f) * rotateY);
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(50.0f, 0.0, 50.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-50.0f, 0.0, 50.0f) * rotateY);
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(40.0f, 0.0, 50.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-40.0f, 0.0, 50.0f) * rotateY);
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(30.0f, 0.0, 35.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-30.0f, 0.0, 35.0f) * rotateY);
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(30.0f, 0.0, 50.0f) * rotateY);
	//_pSceneryBuilder->buildLeaflessTree(Vect(-30.0f, 0.0, 50.0f) * rotateY);
}

void Level2::initializeSouthStreet()
{
	//pDestroyMonitor->addBuildingToDestroy(_pSceneryBuilder->buildWarehouse(Vect(-15.0f, 0.0f, -15.0f), 45.0f, 0.7f));
	_pSceneryBuilder->buildCottage(Vect(15.0f, 0.0f, -15.0f), -45.0f + 180.0f);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, -25.0f), 90.0f);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, -25.0f), 90.0f);

	_pSceneryBuilder->buildLeaflessTree(Vect(10.0f, 0.0f, -40.0f), 90.0f);
	_pSceneryBuilder->buildLeaflessTree(Vect(-10.0f, 0.0f, -32.0f), 90.0f, 0.8f);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, -40.0f), 90.0f);
	_pSceneryBuilder->buildCampfire(Vect(10.0f, 0.0f, -33.0f), 90.0f, 1.0f);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, -53.0f), 90.0f);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, -53.0f), 90.0f);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, -67.0f), 90.0f);
	_pSceneryBuilder->buildWarehouse(Vect(-13.0f, 0.0f, -66.0f), 90.0f, 0.7f);

	_pSceneryBuilder->buildWindMill(Vect(0.0f, 0.0f, -86.0f), 180.0f);

	// Trees
	//_pSceneryBuilder->buildLeaflessTree(Vect(25.0f, 0.0, -20.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-25.0f, 0.0, -20.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(35.0f, 0.0, -20.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-35.0f, 0.0, -20.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(35.0f, 0.0, -20.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-35.0f, 0.0, -20.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(45.0f, 0.0, -34.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-45.0f, 0.0, -40.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(45.0f, 0.0, -56.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-45.0f, 0.0, -40.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(35.0f, 0.0, -46.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-35.0f, 0.0, -65.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(50.0f, 0.0, -50.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-50.0f, 0.0, -50.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(40.0f, 0.0, -50.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-40.0f, 0.0, -50.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(30.0f, 0.0, -35.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-30.0f, 0.0, -35.0f));
	//
	//_pSceneryBuilder->buildLeaflessTree(Vect(30.0f, 0.0, -50.0f));
	//_pSceneryBuilder->buildLeaflessTree(Vect(-30.0f, 0.0, -50.0f));
}

void Level2::initializeWestStreet()
{
	Matrix rotateY = Matrix(ROT_Y, vmath::radians(90.0f));
	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, 25.0f) * rotateY);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, 25.0f) * rotateY);

	_pSceneryBuilder->buildLeaflessTree(Vect(10.0f, 0.0f, 40.0f) * rotateY);
	_pSceneryBuilder->buildLeaflessTree(Vect(-10.0f, 0.0f, 32.0f) * rotateY, 0.0, 0.8f);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, 40.0f) * rotateY);
	_pSceneryBuilder->buildCampfire(Vect(10.0f, 0.0f, 33.0f) * rotateY, 0.0f, 1.0f);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, 53.0f) * rotateY);
	_pSceneryBuilder->buildCottage(Vect(-10.0f, 0.0f, 53.0f) * rotateY);

	_pSceneryBuilder->buildCottage(Vect(10.0f, 0.0f, 67.0f) * rotateY);
	_pSceneryBuilder->buildWarehouse(Vect(-13.0f, 0.0f, 66.0f) * rotateY, 180.0f, 0.7f);

	_pSceneryBuilder->buildWindMill(Vect(0.0f, 0.0f, 86.0f) * rotateY, -90.0f);
}

void Level2::initializeWarehouses()
{
	float zOffset = 80.0f;
	Vect offset = Vect(100.0, 0.0f, 90.0f);
	Vect spawnPosition = Vect(0.0f, 0.0f, 0.0f);

	std::vector<Vect> spawnPositions;
	std::vector<float> rotations;

	int numberofSpawnSettings = 3;

	for (int i = 0; i < numberofSpawnSettings; i++)
	{
		spawnPositions.push_back(spawnPosition + offset);
		spawnPosition += Vect(0.0f, 0.0f, zOffset);
		rotations.push_back(90.0f + (i + 1) * 4.0f);
	}

	for (int i = 0; i < numberofSpawnSettings; i++)
	{
		Damagable* pWarehouse = nullptr;

		const Vect& position = spawnPositions[i];
		float rotation = rotations[i];
		pWarehouse = _pSceneryBuilder->buildWarehouse(position, rotation);
		_pDestroyMonitor->addBuildingToDestroy(pWarehouse);
		_pTankKillMonitor->createTankSpawnerAt(position);

		Matrix flipX = Matrix(SCALE, Vect(-1.0, 1.0f, 1.0f));
		pWarehouse = _pSceneryBuilder->buildWarehouse(position * flipX, (180 - rotation));
		_pDestroyMonitor->addBuildingToDestroy(pWarehouse);
		_pTankKillMonitor->createTankSpawnerAt(position * flipX);
	}
}

void Level2::initializeCottages()
{
	Vect offset = Vect(50.0, 0.0f, 70.0f);

	Vect spawnCottagePosition = Vect(0.0f, 0.0f, 0.0f);
	float zOffset = 30.0f;

	std::vector<Vect> spawnPositions;
	std::vector<float> rotations;

	int size = 9;

	for (int i = 0; i < size; i++)
	{
		Vect variation = Vect(5.0f, 0.0f, 0.0f);
		float rotationVariation = 25.0f;
		if (i % 2 != 0)
		{
			variation *= -1.0f;
			rotationVariation *= -1.0f;
		}
		spawnPositions.push_back(spawnCottagePosition + offset + variation);
		spawnCottagePosition += Vect(0.0f, 0.0f, zOffset);

		rotations.push_back(90.0f + rotationVariation);
	}

	int last = 3;
	for (int i = 0; i < last; i++)
	{
		int index = (spawnPositions.size() - last) + i;
		spawnPositions[index][x] += (i + 1) * 20.0f;
		rotations[index] = 135.0f;
	}

	for (int i = 0; i < size; i++)
	{
		const Vect& position = spawnPositions[i];
		float rotation = rotations[i];
		_pSceneryBuilder->buildCottage(position, rotation);
		_pSceneryBuilder->buildCottage(position * Matrix(SCALE, Vect(-1.0, 1.0f, 1.0f)), (180 - rotation));
	}


	//_pSceneryBuilder->buildCottage(Vect(cottageOffset, 0.0f, cottageOffset), 30.0f);
	//_pSceneryBuilder->buildCottage(Vect(-cottageOffset, 0.0f, cottageOffset), 58.0f);
	//_pSceneryBuilder->buildCottage(Vect(cottageOffset, 0.0f, -cottageOffset), -40.0f);
	//_pSceneryBuilder->buildCottage(Vect(-cottageOffset, 0.0f, -cottageOffset), 72.0f);
	//_pSceneryBuilder->buildCottage(Vect(100.0f, 0.0f, 0.0f));
}

void Level2::initializeTrees()
{
	std::vector<Vect> treePositions;
	float scale = 6.0f;
	treePositions.push_back(Vect(3.0f, 0.0f, -4.0f) * scale);
	treePositions.push_back(Vect(5.0f, 0.0f, 0.0f) * scale);
	treePositions.push_back(Vect(0.0f, 0.0f, 5.0f) * scale);
	treePositions.push_back(Vect(-4.0f, 0.0f, 3.0f) * scale);
	treePositions.push_back(Vect(3.0f, 0.0f, 4.0f) * scale);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			float xOffset = static_cast<float>((i - 5) * 80);
			float zOffset = static_cast<float>((j - 5) * 80);
			Vect offset = Vect(xOffset, 0.0, zOffset);
			for (const auto& treePosition : treePositions)
			{
				Vect spawnPosition = treePosition + offset;

				//if (canSpawnTreeHere(spawnPosition))
				//{
				_pSceneryBuilder->buildLeaflessTree(spawnPosition);
				//}
			}
		}
	}
}

bool Level2::canSpawnTreeHere(const Vect& position) const
{
	//return position[x] == position[x];
	if (position[x] <= 10.0f && position[x] >= -10.0f)
	{
		return false;
	}

	if (position[z] <= 10.0f && position[z] >= -10.0f)
	{
		return false;
	}

	return true;
}

void Level2::initializeWindMills()
{
	float offset = 180.f;
	_pSceneryBuilder->buildWindMill(Vect(40.0f, 0.0f, 270.0f), 30.0f + offset, 2.0f);
	_pSceneryBuilder->buildWindMill(Vect(-40.0f, 0.0f, 270.0f), -30.0f + offset, 2.0f);
}

void Level2::initializeCampfires()
{
	float offset = 10.0f;

	_pSceneryBuilder->buildCampfire(Vect(offset, 0.0f, 0.0f), 30.0f);
	_pSceneryBuilder->buildCampfire(Vect(0.0f, 0.0f, offset), 58.0f);
	_pSceneryBuilder->buildCampfire(Vect(-offset, 0.0f, 0.0f), -40.0f);
	_pSceneryBuilder->buildCampfire(Vect(0.0f, 0.0f, -offset), 72.0f);
	_pSceneryBuilder->buildCampfire(Vect(5.0f, 0.0f, 0.0f));
}

#pragma endregion

void Level2::sceneEnd()
{
	BulletFactory::RecallActiveBullets();
	TankFactory::RecallActiveTanks();

	delete _pGameController;
	delete _pTankKillMonitor;
	delete _pAlarmController;
	delete _pDestroyMonitor;

	delete _pCameraSwitcher;
	delete _pTopViewCamera;
	delete _pSideViewCamera;

	delete _pGroundPlane;
	delete _pWorldAxes;

	delete _pPlayerHealthBar;
	delete _pAmmoBar;

	delete _pSceneryBuilder;
	delete _pSceneChanger;

	//delete pTurret;

	for (auto& pGameObjects : _gameObjects)
	{
		delete pGameObjects;
	}

	delete _pWallBuilder;
}
