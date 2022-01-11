#include "TestScene2.h"
#include "CameraManager.h"
#include "CameraController.h"

#include "WorldPlane.h"
#include "WorldAxes.h"

#include "TesterObject.h"
#include "TankFactory.h"
#include "BulletFactory.h"
#include "SpaceFrigate.h"

#include "DebugRegistrationCube.h"

#include "SceneChanger.h"
#include "TestScene3.h"
#include "TestScene.h"

void TestScene2::initialize()
{
	// No Collision Test

	_pCameraController = new CameraController();
	_pWorldPlane = new WorldPlane();
	_pWorldAxes = new WorldAxes();

	TankFactory::CreateTank(TankControlType::PLAYER_CONTROL, Vect(0.0f, 0.0f, 0.0f));

	TankFactory::CreateTank(TankControlType::PLAYER_CONTROL, Vect(30.0f, 0.0f, 0.0f));

	TankFactory::CreateTank(TankControlType::PLAYER_CONTROL, Vect(-30.0f, 0.0f, 0.0f));

	_pSceneChanger = new SceneChanger();
	_pSceneChanger->setNextScene(new TestScene3());
	_pSceneChanger->setPreviousScene(new TestScene());
}

void TestScene2::sceneEnd()
{
	BulletFactory::RecallActiveBullets();
	TankFactory::RecallActiveTanks();

	delete _pCameraController;
	delete _pSpaceFrigate;
	delete _pWorldPlane;
	delete _pWorldAxes;

	delete _pDebugRegistrationCube;
	delete _pDebugRegistrationCubeX;
	delete _pDebugRegistrationCubeY;
	delete _pDebugRegistrationCubeZ;

	delete _pTesterObject;

	delete _pSceneChanger;
}