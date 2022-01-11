#include "AlarmDemoScene.h"

#include "WorldPlane.h"
#include "WorldAxes.h"
#include "AlarmCar.h"

#include "SceneChanger.h"
#include "InputDemoScene.h"
#include "BasicDemoScene.h"

void AlarmDemoScene::initialize()
{
	Trace::out("AlarmDemoScene::initialize\n");
	// Create game objects here
	_pWorldPlane = new WorldPlane();
	_pWorldAxes = new WorldAxes();
	_pAlarmCar = new AlarmCar();

	_pSceneChanger = new SceneChanger();
	_pSceneChanger->setNextScene(new InputDemoScene());
	_pSceneChanger->setPreviousScene(new BasicDemoScene());
}

void AlarmDemoScene::sceneEnd()
{
	Trace::out("AlarmDemoScene::sceneEnd\n");
	// Terminate game obejcts here. 
	// If a factory is used then call factory to recycle created objects
	delete _pWorldPlane;
	delete _pWorldAxes;
	delete _pAlarmCar;

	delete _pSceneChanger;
}