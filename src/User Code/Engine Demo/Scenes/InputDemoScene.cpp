#include "InputDemoScene.h"

#include "WorldPlane.h"
#include "WorldAxes.h"
#include "InputCar.h"

#include "SceneChanger.h"
#include "CollisionDemoScene.h"
#include "AlarmDemoScene.h"

void InputDemoScene::initialize()
{
	Trace::out("InputDemoScene::initialize\n");

	// Create game objects here
	_pWorldPlane = new WorldPlane();
	_pWorldAxes = new WorldAxes();
	_pInputCar = new InputCar();

	_pSceneChanger = new SceneChanger();
	_pSceneChanger->setNextScene(new CollisionDemoScene());
	_pSceneChanger->setPreviousScene(new AlarmDemoScene());
}

void InputDemoScene::sceneEnd()
{
	Trace::out("InputDemoScene::sceneEnd\n");
	// Terminate game obejcts here. 
	// If a factory is used then call factory to recycle created objects
	delete _pWorldPlane;
	delete _pWorldAxes;
	delete _pInputCar;

	delete _pSceneChanger;
}