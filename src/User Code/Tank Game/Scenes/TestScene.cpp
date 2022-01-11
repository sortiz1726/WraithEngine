#include "TestScene.h"
#include "CameraManager.h"
#include "CameraController.h"
#include "CameraSwitcher.h"
#include "WorldPlane.h"
#include "WorldAxes.h"
#include "DebugRegistrationCube.h"
#include "TesterObject.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "TankFactory.h"
#include "Tank.h"
#include "SceneChanger.h"
#include "TestScene2.h"
#include "TestScene3.h"
#include "MainMenu.h"
#include "vmath.h"
#include "SpaceFrigate.h"
#include "Warehouse.h"
#include "WindMill.h"
#include "LeaflessTree.h"
#include "RoundArch.h"

#include "CollisionTestObject.h"
#include "Wall.h"

CollisionTestObject* pCollisionTestObject = nullptr;

void TestScene::initialize()
{
	// Setting collision to tests
	//setCollisionSelf<DebugRegistrationCube>();
	setCollisionSelf<RoundArch>();
	setCollisionPair<Tank, RoundArch>();
	setCollisionPair<Bullet, RoundArch>();
	// setCollisionPair<Tank, Bullet>();
	//setCollisionPair<DebugRegistrationCube, Tank>();
	//setCollisionPair<DebugRegistrationCube, Bullet>();

	Vect topViewPosition(0.0f, 150.0f, -0.1f);
	Vect topViewLookAt(0.0f, 0.0f, 0.0f);
	_pTopViewCamera = CameraManager::CreateCamera(topViewPosition, topViewLookAt);

	Vect sideViewPosition(50.0f, 0.0f, 0.0f);
	Vect sideViewLookAt(0.0f, 0.0f, 0.0f);
	_pSideViewCamera = CameraManager::CreateCamera(sideViewPosition, sideViewLookAt);
	// Enviroment
	_pWorldPlane = new WorldPlane();
	_pWorldAxes = new WorldAxes();

	//Warehouse* pWarehouse = nullptr;
	//pWarehouse;
	//pWarehouse = new Warehouse();
	//pWarehouse->initialize(Vect(0.0, 0.0f, 0.0f), 45.0f, 0.5f);
	//_gameObjects.push_back(pWarehouse);
	//
	//pWarehouse = new Warehouse();
	//pWarehouse->initialize(Vect(30.0f, 0.0f, 50.0f), 30, 0.5f);
	//_gameObjects.push_back(pWarehouse);
	//
	//pWarehouse = new Warehouse();
	//pWarehouse->initialize(Vect(-30.0f, 0.0f, 40.0f), -60, 2.0f);
	//_gameObjects.push_back(pWarehouse);

	//LeaflessTree* pLeaflessTree = nullptr;
	//pLeaflessTree = new LeaflessTree();
	//pLeaflessTree->initialize(Vect(0.0, 0.0f, 0.0f), 1.0f);
	//_gameObjects.push_back(pLeaflessTree);

	//pLeaflessTree = new LeaflessTree();
	//pLeaflessTree->initialize(Vect(30.0f, 0.0f, 0.0f), 30, 0.5f);
	//_gameObjects.push_back(pLeaflessTree);

	//pLeaflessTree = new LeaflessTree();
	//pLeaflessTree->initialize(Vect(-30.0f, 0.0f, 0.0f), -60, 2.0f);
	//_gameObjects.push_back(pLeaflessTree);

	//WindMill* pWindMill = nullptr;
	//pWindMill = new WindMill();
	//pWindMill->initialize(Vect(0.0, 0.0f, -60.0f), 1.0f);
	//_gameObjects.push_back(pWindMill);

	//pWindMill = new WindMill();
	//pWindMill->initialize(Vect(30.0f, 0.0f, -50.0f), 30, 0.5f);
	//_gameObjects.push_back(pWindMill);

	//pWindMill = new WindMill();
	//pWindMill->initialize(Vect(-30.0f, 0.0f, -40.0f), -60, 2.0f);
	//_gameObjects.push_back(pWindMill);


	RoundArch* pRoundArch = new RoundArch();
	pRoundArch->initialize(Vect(0.0, 0.0f, 0.0f), 0.0f, 1.5f);
	_gameObjects.push_back(pRoundArch);

	pRoundArch = new RoundArch();
	pRoundArch->initialize(Vect(0.0, 12.0f, -30.0f), Vect(180.0f, 90.0f, 0.0f), Vect(1.0f, 1.0f, 1.0f) * 1.5f);
	pRoundArch->_canMove = true;
	_gameObjects.push_back(pRoundArch);

	// Tanks
	Tank* _pPlayerTank = TankFactory::CreateTank(TankControlType::PLAYER_CONTROL, Vect(0.0f, 0.0f, 0.0f));
	_pPlayerTank->setMoveSpeed(5.0f);
	//
	//TankFactory::CreateTank(TankControlType::NULL_CONTROL, Vect(70.0f, 0.0f, -45.0f));
	//TankFactory::CreateTank(TankControlType::NULL_CONTROL, Vect(50.0f, 0.0f, -30.0f));
	//_pPlayerTank->setMoveSpeed(50.0f);
	//float offset = 100.0f;
	//Tank* _pEnemyTank = TankFactory::CreateTank(TankControlType::AI_CONTROL, Vect(0.0f, 0.0f, 20.0f));
	//_pEnemyTank->setTankScale(1.0f);
	//_pEnemyTank->setTarget(_pPlayerTank);
	//_pEnemyTank->setMoveSpeed(0.0f);
	//_pEnemyTank->_pTerrain = pTerrain;
	//
	//_pEnemyTank = TankFactory::CreateTank(TankFactory::TankControl::AI_CONTROL, Vect(offset, 0.0f, offset));
	//_pEnemyTank->setTankScale(3.0f);
	//_pEnemyTank->setTarget(_pPlayerTank);
	//_pEnemyTank->setMoveSpeed(0.0f);
	//
	//_pEnemyTank = TankFactory::CreateTank(TankFactory::TankControl::AI_CONTROL, Vect(offset, 0.0f, 0.0f));
	//_pEnemyTank->setTankScale(1.0f / 3.0f);
	//_pEnemyTank->setTarget(_pPlayerTank);
	//_pEnemyTank->setMoveSpeed(0.0f);

	//_pEnemyTank->setTarget(_pPlayerTank);
	//_pPlayerTank->setTarget(_pEnemyTank);

	_numberOfEnemyTanks = 4;
	Vect spawnPoint = Vect(0.0f, 0.0f, 80.0f);
	Matrix rotation = Matrix(ROT_Y, vmath::radians(360.0f / _numberOfEnemyTanks));

	for (int i = 0; i < _numberOfEnemyTanks; i++)
	{
		Tank* pTank = TankFactory::CreateTank(TankControlType::AI_CONTROL, spawnPoint);
		pTank->setTarget(_pPlayerTank);
		spawnPoint *= rotation;
	}

	// Camera Switcher
	_pCameraSwitcher = new CameraSwitcher();
	_pCameraSwitcher->addCamera(_pPlayerTank->getThirdPersonCamera());
	_pCameraSwitcher->addCamera(_pTopViewCamera, CameraController::Status::OPERATIONAL);
	_pCameraSwitcher->addCamera(_pSideViewCamera, CameraController::Status::OPERATIONAL);


	// Tester objects that stress every registration
	//_pDebugRegistrationCubeX = new DebugRegistrationCube("X", "Red", Vect(0, 0, 0), Vect(1, 0, 0));
	//_pDebugRegistrationCubeY = new DebugRegistrationCube("Y", "Green", Vect(0, 0, 0), Vect(0, 1, 0));
	//_pDebugRegistrationCubeZ = new DebugRegistrationCube("Z", "Blue", Vect(0, 0, 0), Vect(0, 0, 1));

	_pSceneChanger = new SceneChanger();
	_pSceneChanger->setNextScene(new TestScene2());
	_pSceneChanger->setPreviousScene(new TestScene3());

	//_pTesterObject = new TesterObject();

	//pCollisionTestObject = new CollisionTestObject();

	//LeaflessTree* pTree = new LeaflessTree();
	//pTree->initialize(Vect(-10.0f, 0.0f, 0.0f));
	//_gameObjects.push_back(pTree);

	//Wall* pWall = new Wall();
	//pWall->initialize(Vect(0.0f, 0.0f, 10.0f));
	//_gameObjects.push_back(pWall);
}

void TestScene::sceneEnd()
{
	BulletFactory::RecallActiveBullets();
	TankFactory::RecallActiveTanks();

	delete _pCameraSwitcher;
	delete _pTopViewCamera;
	delete _pSideViewCamera;

	delete _pWorldPlane;
	delete _pWorldAxes;
	delete _pWarehouse;

	delete _pDebugRegistrationCubeX;
	delete _pDebugRegistrationCubeY;
	delete _pDebugRegistrationCubeZ;

	delete _pTesterObject;

	delete _pSceneChanger;

	for (auto& pGameObjects : _gameObjects)
	{
		delete pGameObjects;
	}

	delete pCollisionTestObject;
}
