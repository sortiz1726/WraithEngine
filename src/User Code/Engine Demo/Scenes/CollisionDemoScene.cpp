#include "CollisionDemoScene.h"

#include "WorldPlane.h"
#include "WorldAxes.h"
#include "CollisionCar.h"
#include "OtherCollisionCar.h"

#include "SceneChanger.h"
#include "BasicDemoScene.h"
#include "InputDemoScene.h"

void CollisionDemoScene::initialize()
{
	Trace::out("CollisionDemoScene::initialize\n");
	// Set collison tests
	setCollisionPair<CollisionCar, OtherCollisionCar>();

	// Create game objects here
	_pWorldPlane = new WorldPlane();
	_pWorldAxes = new WorldAxes();
	_pCollisionCar = new CollisionCar();
	_pOtherCollisionCar = new OtherCollisionCar();

	_pSceneChanger = new SceneChanger();
	_pSceneChanger->setNextScene(new BasicDemoScene());
	_pSceneChanger->setPreviousScene(new InputDemoScene());
}

void CollisionDemoScene::sceneEnd()
{
	Trace::out("CollisionDemoScene::sceneEnd\n");
	// Terminate game obejct here. 
	// If a factory is used then call factory to recycle created objects
	delete _pWorldPlane;
	delete _pWorldAxes;
	delete _pCollisionCar;
	delete _pOtherCollisionCar;

	delete _pSceneChanger;
}