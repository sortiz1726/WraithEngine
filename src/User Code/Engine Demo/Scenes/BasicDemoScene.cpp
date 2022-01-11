#include "BasicDemoScene.h"

#include "WorldPlane.h"
#include "WorldAxes.h"
#include "BasicCar.h"

#include "SceneChanger.h"
#include "AlarmDemoScene.h"
#include "CollisionDemoScene.h"

void BasicDemoScene::initialize()
{
	Trace::out("BasicDemoScene::initialize\n");
	// Create game objects here
	_pWorldPlane = new WorldPlane();
	_pWorldAxes = new WorldAxes();
	_pBasicCar = new BasicCar();

	_pSceneChanger = new SceneChanger();
	_pSceneChanger->setNextScene(new AlarmDemoScene());
	_pSceneChanger->setPreviousScene(new CollisionDemoScene());
}

void BasicDemoScene::sceneEnd()
{
	Trace::out("BasicDemoScene::sceneEnd\n");
	// Terminate game obejcts here. 
	// If a factory is used then call factory to recycle created objects
	delete _pWorldPlane;
	delete _pWorldAxes;
	delete _pBasicCar;

	delete _pSceneChanger;
}