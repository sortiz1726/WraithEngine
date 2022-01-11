#include "TestScene3.h"
#include "CameraManager.h"
#include "CameraController.h"
#include "CameraSwitcher.h"
#include "WorldPlane.h"
#include "WorldAxes.h"

#include "TankFactory.h"
#include "Tank.h"
#include "BulletFactory.h"

#include "DebugRegistrationCube.h"
#include "TesterObject.h"

#include "SceneChanger.h"
#include "Level1.h"
#include "MainMenu.h"
#include "TestScene2.h"
#include "TestScene.h"

#include "vmath.h"

void TestScene3::initialize()
{
	setCollisionSelf<DebugRegistrationCube>();

	Vect topViewPosition(0.0f, 750.0f, -0.1f);
	Vect topViewLookAt(0.0f, 0.0f, 0.0f);
	_pTopViewCamera = CameraManager::CreateCamera(topViewPosition, topViewLookAt);

	Vect sideViewPosition(50.0f, 0.0f, 0.0f);
	Vect sideViewLookAt(0.0f, 0.0f, 0.0f);
	_pSideViewCamera = CameraManager::CreateCamera(sideViewPosition, sideViewLookAt);
	// Enviroment
	_pWorldPlane = new WorldPlane();
	_pWorldAxes = new WorldAxes();

	// Tanks
	Tank* _pPlayerTank = TankFactory::CreateTank(TankControlType::PLAYER_CONTROL, Vect(0.0f, 0.0f, 0.0f));

	Tank* _pEnemyTank = TankFactory::CreateTank(TankControlType::AI_CONTROL, Vect(0.0f, 0.0f, 25.0f));

	_pEnemyTank->setTarget(_pPlayerTank);
	_pPlayerTank->setTarget(_pEnemyTank);

	Vect spawnPoint = Vect(0.0f, 0.0f, 80.0f);
	Matrix rotation = Matrix(ROT_Y, vmath::radians(360.0f / _numberOfEnemyTanks));

	std::vector<Tank*> _enemyTanks;
	for (int i = 0; i < _numberOfEnemyTanks; i++)
	{
		Tank* pTank = TankFactory::CreateTank(TankControlType::AI_CONTROL, spawnPoint);
		_enemyTanks.push_back(pTank);
		spawnPoint *= rotation;
	}

	for (int i = 0; i < _numberOfEnemyTanks; i++)
	{
		Tank* pEnemyTank = _enemyTanks.at(i);
		Tank* pTargetTank = _enemyTanks.at((i + 1) % _numberOfEnemyTanks);
		pEnemyTank->setTarget(pTargetTank);

	}

	// Camera Switcher
	_pCameraSwitcher = new CameraSwitcher();
	_pCameraSwitcher->addCamera(_pPlayerTank->getThirdPersonCamera());
	_pCameraSwitcher->addCamera(_pTopViewCamera, CameraController::Status::OPERATIONAL);
	_pCameraSwitcher->addCamera(_pSideViewCamera, CameraController::Status::OPERATIONAL);


	// Tester objects that stress every registration
	_pDebugRegistrationCubeX = new DebugRegistrationCube("Xaviar", "Red", Vect(0, 0, 0), Vect(1, 0, 0));
	_pDebugRegistrationCubeY = new DebugRegistrationCube("Yandel", "Green", Vect(0, 0, 0), Vect(0, 1, 0));
	_pDebugRegistrationCubeZ = new DebugRegistrationCube("Zachary", "Blue", Vect(0, 0, 0), Vect(0, 0, 1));

	_pSceneChanger = new SceneChanger();
	_pSceneChanger->setNextScene(new TestScene());
	_pSceneChanger->setPreviousScene(new TestScene2());
}

void TestScene3::sceneEnd()
{
	BulletFactory::RecallActiveBullets();
	TankFactory::RecallActiveTanks();

	delete _pCameraSwitcher;
	delete _pTopViewCamera;
	delete _pSideViewCamera;

	delete _pWorldPlane;
	delete _pWorldAxes;

	delete _pDebugRegistrationCubeX;
	delete _pDebugRegistrationCubeY;
	delete _pDebugRegistrationCubeZ;

	delete _pTesterObject;

	delete _pSceneChanger;
}
