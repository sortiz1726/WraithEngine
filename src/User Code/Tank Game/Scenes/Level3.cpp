#include "Level3.h"
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
#include "Bomber.h"

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
#include "MainMenu.h"

#include "vmath.h"
#include "WallBuilder.h"
#include "CollisionVolumeOBB.h"
#include "DrawCollisionVolumes.h"
#include "MathTools.h"

void Level3::initialize()
{
	SetCollisionTests();
	initializedCameras();
	_pGroundPlane = new GroundPlane("RedSandTexture");
	setTerrain("Level3Terrain");

	// Tanks
	Tank* _pPlayerTank = TankFactory::CreateTank(TankControlType::PLAYER_CONTROL, Vect(0.0f, 0.0f, 0.0f));
	_pPlayerTank->setBulletDamage(35.0f);
	_pPlayerTank->setTankRotation(vmath::radians(180.0f));

	_pPlayerHealthBar = new HealthBar(_pPlayerTank);
	_pAmmoBar = new AmmoBar();
	_pAmmoBar->setTank(_pPlayerTank);

	// Game Controller
	_pGameController = new GameController();
	_pGameController->setTarget(_pPlayerTank);
	_pGameController->setCurrentScene(new Level3());
	_pGameController->setNextScene(new MainMenu());

	_pTankKillMonitor = new TankKillMonitor();
	_pTankKillMonitor->setTarget(_pPlayerTank);
	_pTankKillMonitor->setLeftToKill(60);
	_pTankKillMonitor->setDrawText(false);
	_pTankKillMonitor->setMaxNumberOfEnemyTanks(8);
	_pTankKillMonitor->setGameControllerToNotify(_pGameController);

	_pAlarmController = new AlarmController();
	_pAlarmController->setGameControllerToNotify(_pGameController);
	_pAlarmController->setTriggerTime(180.0f);
	_pAlarmController->startTimer();

	_pDestintationMonitor = new DestinationMonitor();
	_pDestintationMonitor->setGameControllerToNotify(_pGameController);
	_pDestintationMonitor->setTarget(_pPlayerTank);

	// Camera Switcher
	Camera* pPlayerCamera = _pPlayerTank->getThirdPersonCamera();
	setCurrentCamera(pPlayerCamera);

	// Enviroment
	_pSceneryBuilder = new SceneryBuilder();
	initializeMarkers();
	initializeScenery();
	initializeWalls();
	initializeTurrets(_pPlayerTank);
	initializeWindMills();
	initializeCottages();
	initializeWarehouse();

	_pCameraSwitcher = new CameraSwitcher();
	_pCameraSwitcher->addCamera(_pPlayerTank->getThirdPersonCamera());
	_pCameraSwitcher->addCamera(_pTopViewCamera, CameraController::Status::OPERATIONAL);
	_pCameraSwitcher->addCamera(_pSideViewCamera, CameraController::Status::OPERATIONAL);

	_gameObjects.push_back(new Reticle());

	Bomber* pBomber = new Bomber();
	pBomber->setTarget(_pPlayerTank);
	pBomber->setTimer(5.0f);

	_gameObjects.push_back(pBomber);
}

void Level3::initializedCameras()
{
	Vect topViewPosition(0.0f, 150.0f, -0.1f);
	Vect topViewLookAt(0.0f, 0.0f, 0.0f);
	_pTopViewCamera = CameraManager::CreateCamera(topViewPosition, topViewLookAt);

	Vect sideViewPosition(50.0f, 0.0f, 0.0f);
	Vect sideViewLookAt(0.0f, 0.0f, 0.0f);
	_pSideViewCamera = CameraManager::CreateCamera(sideViewPosition, sideViewLookAt);
}

void Level3FunctionCode()
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

void Level3::SetCollisionTests()
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

void Level3::initializeScenery()
{
	
	initializeTrees();
}

void Level3::initializeWalls()
{
	_pWallBuilder = new WallBuilder();

	int length = 21;

	float tankWidth = 6.0f;

	Vect buildPosition = Vect(0.0f, 0.0f, -280.0f);
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

std::vector<CollisionVolumeOBB> lineBoxes;

void Level3::initializeMarkers()
{
	std::vector<Vect> markerPositions;
	markerPositions.push_back(Vect(10.0f, 0.0f, -20.0f));
	markerPositions.push_back(Vect(97, 0, -46));
	markerPositions.push_back(Vect(116, 0, -90));
	markerPositions.push_back(Vect(40, 0, -107));
	markerPositions.push_back(Vect(-40, 0, -101));
	markerPositions.push_back(Vect(-106, 0, -115));
	markerPositions.push_back(Vect(-122, 0, -158));
	markerPositions.push_back(Vect(-89, 0, -194));
	markerPositions.push_back(Vect(-1, 0, -208));
	markerPositions.push_back(Vect(80, 0, -224));
	markerPositions.push_back(Vect(69, 0, -261));
	markerPositions.push_back(Vect(10, 0, -269));
	markerPositions.push_back(Vect(0, 0, -291));

	std::vector<float> archRotations;
	archRotations.push_back(-30.0f);
	archRotations.push_back(-30.0f);
	archRotations.push_back(23.0f);
	archRotations.push_back(90.0f);
	archRotations.push_back(90.0f);
	archRotations.push_back(20.0f);
	archRotations.push_back(-45.0f);
	archRotations.push_back(-35.0f);
	archRotations.push_back(-85.0f);
	archRotations.push_back(-60.0f);
	archRotations.push_back(45.0f);
	archRotations.push_back(45.0f);
	archRotations.push_back(0.0f);

	int i = 0;
	for (auto& markerPosition : markerPositions)
	{
		_pDestintationMonitor->createMarker(markerPosition);
		_pSceneryBuilder->buildRoundArch(markerPosition, archRotations[i++], 1.3f);
	}

	lineBoxes.clear();
	lineBoxes.reserve(markerPositions.size() - 1);
	CollisionVolumeOBB lineBox;

	//DrawCollisionVolumes* pDrawCollisionVolumes = new DrawCollisionVolumes();
	//_gameObjects.push_back(pDrawCollisionVolumes);
	for (std::vector<Vect>::iterator it = std::next(markerPositions.begin()); it != markerPositions.end(); ++it)
	{
		// Set Extents
		const Vect& to = (*it);
		const Vect& from = (*std::prev(it));

		Vect fromTo = to - from;

		float length = fromTo.mag() + 5;
		Vect extents = Vect(20.0f, 10.0f, length) * 0.5f;

		Vect minVertex = -extents;
		Vect maxVertex = extents;

		lineBox.setMinMaxLocalVertex(minVertex, maxVertex);

		// Set orientation
		Vect midPoint = (from + to) * 0.5f;
		float rotation = atan2f(fromTo[x], fromTo[z]);

		Matrix world = Matrix(ROT_Y, rotation) * Matrix(TRANS, midPoint);
		lineBox.setWorldMatrix(world);

		lineBoxes.push_back(lineBox);
		//pDrawCollisionVolumes->addCollisionVolume(lineBox);
	}
}

void Level3::initializeTrees()
{
	std::vector<Vect> treePositions;
	float treeSideLength = 16.0f;
	float scale = treeSideLength * 0.5f;

	treePositions.push_back(Vect(2.0f, 0.0f, 3.0f) * scale);
	treePositions.push_back(Vect(-3.0f, 0.0f, 3.0f) * scale);

	treePositions.push_back(Vect(1.0f, 0.0f, 1.0f) * scale);
	treePositions.push_back(Vect(-2.0f, 0.0f, 1.0f) * scale);

	treePositions.push_back(Vect(3.0f, 0.0f, 0.0f) * scale);

	treePositions.push_back(Vect(0.0f, 0.0f, -1.0f) * scale);

	treePositions.push_back(Vect(2.0f, 0.0f, -2.0f) * scale);
	treePositions.push_back(Vect(-3.0f, 0.0f, -2.0f) * scale);

	treePositions.push_back(Vect(-1.0f, 0.0f, -3.0f) * scale);

	float maxDistance = 3.0f;
	float treeSectionLength = (maxDistance * 2.0f + 1.0f) * treeSideLength * 0.5f;

	int xExtent = 4;
	int zExtent = 6;
	for (int i = -xExtent; i < xExtent; i++)
	{
		for (int j = 0; j > -zExtent; j--)
		{
			Vect offset = Vect(float(i), 0.0f, float(j)) * treeSectionLength;
			for (const Vect& treePosition : treePositions)
			{
				Vect buildPosition = treePosition + offset;
				if (canSpawnTreeHere(buildPosition))
				{
					_pSceneryBuilder->buildLeaflessTree(treePosition + offset);
				}
			}
		}
	}
}

bool Level3::canSpawnTreeHere(const Vect& position) const
{
	for (auto& lineBox : lineBoxes)
	{
		if (MathTools::Intersect(lineBox, position))
		{
			return false;
		}
	}
	return true;
}

void Level3::initializeTurrets(Tank* pTarget)
{
	std::vector<Vect> turretPositions;

	turretPositions.push_back(Vect(10, 0, -35));
	turretPositions.push_back(Vect(117, 0, -35));
	turretPositions.push_back(Vect(129, 0, -112));
	turretPositions.push_back(Vect(25, 0, -85));
	turretPositions.push_back(Vect(-41, 0, 119));
	turretPositions.push_back(Vect(119, 0, 109));
	turretPositions.push_back(Vect(-132, 0, 176));
	turretPositions.push_back(Vect(-79, 0, -168));
	turretPositions.push_back(Vect(-32, 0, -217));
	turretPositions.push_back(Vect(54, 0, 197));
	turretPositions.push_back(Vect(99, 0, -230));
	turretPositions.push_back(Vect(26, 0, -250));
	turretPositions.push_back(Vect(-13, 0, -253));
	turretPositions.push_back(Vect(-16, 0, -118));
	turretPositions.push_back(Vect(-93, 0, -90));
	turretPositions.push_back(Vect(-131, 0, -139));
	turretPositions.push_back(Vect(3, 0, -192));
	turretPositions.push_back(Vect(59, 0, -191));
	turretPositions.push_back(Vect(73, 0, -22));
	turretPositions.push_back(Vect(94, 0, -82));

	for (auto& turretPosition : turretPositions)
	{
		Turret* pTurret = new Turret();
		pTurret->initialize(turretPosition);
		pTurret->setBulletDamage(1.5f);
		pTurret->setHealth(20.0f);
		pTurret->setTarget(pTarget);
		_gameObjects.push_back(pTurret);
	}
}

void Level3::initializeWindMills()
{
	std::vector<Vect> windMillPositions;
	std::vector<float> windMillRotation;

	windMillPositions.push_back(Vect(-5, 0, -45));
	windMillRotation.push_back(0.0f);

	windMillPositions.push_back(Vect(130, 0, -80));
	windMillRotation.push_back(-90.0f);

	windMillPositions.push_back(Vect(-67, 0, -67));
	windMillRotation.push_back(135.0f);

	windMillPositions.push_back(Vect(-128, 0, -180));
	windMillRotation.push_back(45.0f);

	windMillPositions.push_back(Vect(40, 0, -233));
	windMillRotation.push_back(-45.0f);

	windMillPositions.push_back(Vect(135, 0, -256));
	windMillRotation.push_back(-90.0f);

	windMillPositions.push_back(Vect(-32, 0, -264));
	windMillRotation.push_back(90.0f);

	int i = 0;
	for (auto& position : windMillPositions)
	{
		_pSceneryBuilder->buildWindMill(position, windMillRotation[i]);
		++i;
	}
}

void Level3::initializeCottages()
{
	struct Transform
	{
		Vect _position = Vect(0.0f, 0.0f, 0.0f);
		float rotation = 0;
	};

	std::vector<Transform> cottageTransforms;

	cottageTransforms.push_back(Transform{ Vect(90, 0, -6), 45 });
	cottageTransforms.push_back(Transform{ Vect(98, 0, -123), 20 });
	cottageTransforms.push_back(Transform{ Vect(26, 0, -121) , -20 });
	cottageTransforms.push_back(Transform{ Vect(-48, 0, 84) , -20 });
	cottageTransforms.push_back(Transform{ Vect(-67, 0, -144) });
	cottageTransforms.push_back(Transform{ Vect(-127, 0, -210) , 45 });
	cottageTransforms.push_back(Transform{ Vect(-13, 0, -179) });
	cottageTransforms.push_back(Transform{ Vect(96, 0, -205), 45 });
	cottageTransforms.push_back(Transform{ Vect(87, 0, -269), -35 });

	for (auto& transform : cottageTransforms)
	{
		_pSceneryBuilder->buildCottage(transform._position, transform.rotation);
	}

	//std::vector<Vect> cottagePositions;
	//std::vector<float> cottageRotations;

	//int i = 0;
	//for (auto& position : cottagePositions)
	//{
	//	_pSceneryBuilder->buildCottage(position, cottageRotations[i]);
	//	++i;
	//}
}

void Level3::initializeWarehouse()
{
	struct Transform
	{
		Vect _position = Vect(0.0f, 0.0f, 0.0f);
		float _rotation = 0;
	};

	std::vector<Transform> warehouseTransforms;

	warehouseTransforms.push_back(Transform{ Vect(70, 0, -62), 20 });
	warehouseTransforms.push_back(Transform{ Vect(-38, 0, -62) });
	warehouseTransforms.push_back(Transform{ Vect(-120, 0, -100) , 90 + 30 });
	warehouseTransforms.push_back(Transform{ Vect(-70, 0, -231) , 20 });
	warehouseTransforms.push_back(Transform{ Vect(52, 0, -161) , 30 });
	warehouseTransforms.push_back(Transform{ Vect(119, 0, -198) , -135 });

	for (auto& transform : warehouseTransforms)
	{
		_pSceneryBuilder->buildWarehouse(transform._position, transform._rotation);
		_pTankKillMonitor->createTankSpawnerAt(transform._position);
	}
}

#pragma endregion

void Level3::sceneEnd()
{
	BulletFactory::RecallActiveBullets();
	TankFactory::RecallActiveTanks();

	delete _pGameController;
	delete _pTankKillMonitor;
	delete _pAlarmController;
	delete _pDestintationMonitor;

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