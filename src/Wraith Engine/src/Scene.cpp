#include "Scene.h"

Scene::~Scene()
{
	_sceneRegistrationBroker.executeCommands();
}

void Scene::setTerrain(const std::string& terrainObjectName)
{
	_terrainManager.setTerrain(terrainObjectName);
}

//-----------------------------------------------------------------------------------------------------------------------------
//  Game Cycle
//-----------------------------------------------------------------------------------------------------------------------------
void Scene::update()
{
	// Process Registration/Deregistrations
	_sceneRegistrationBroker.executeCommands();

	_keyboardEventManager.processKeyEvents();

	_alarmableManager.processAlarms();

	_collisionManager.processCollisions();

	// Start next frame
	_updatableManager.processEntities();
}

void Scene::draw()
{
	_drawableManager.processEntities();
}


//-----------------------------------------------------------------------------------------------------------------------------
// Setting Current Camera
//-----------------------------------------------------------------------------------------------------------------------------
void Scene::setCurrentCamera(Camera* pCamera)
{
	_cameraManager.setCurrentCamera(pCamera);
}

void Scene::setDefaultCameraAsCurrentCamera()
{
	_cameraManager.setDefaultCameraAsCurrentCamera();
}

void Scene::setCurrent2DCamera(Camera* p2DCamera)
{
	_cameraManager.setCurrent2DCamera(p2DCamera);
}

void Scene::setDefault2DCameraAsCurrentCamera()
{
	_cameraManager.setDefault2DCameraAsCurrentCamera();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getting Current Camera
//-----------------------------------------------------------------------------------------------------------------------------
Camera* Scene::getCurrentCamera() const
{
	return _cameraManager.getCurrentCamera();
}

Camera* Scene::getDefaultCamera() const
{
	return _cameraManager.getDefaultCamera();
}

Camera* Scene::getCurrent2DCamera() const
{
	return _cameraManager.getCurrent2DCamera();
}

Camera* Scene::getDefault2DCamera() const
{
	return _cameraManager.getDefault2DCamera();
}

const Terrain* Scene::getTerrain() const
{
	return _terrainManager.getTerrain();
}


//-----------------------------------------------------------------------------------------------------------------------------
// Register and Deregister SceneRegistrationCommand function
//-----------------------------------------------------------------------------------------------------------------------------
void Scene::submitCommand(SceneRegistrationCommand* pCommand)
{
	_sceneRegistrationBroker.addCommand(pCommand);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Entity Registration/Deregistration
//-----------------------------------------------------------------------------------------------------------------------------

// ---> Updatable
void Scene::registerEntity(Updatable* pUpdatable)
{
	_updatableManager.registerEntity(pUpdatable);
}

void Scene::deregisterEntity(Updatable* pUpdatable)
{
	_updatableManager.deregisterEntity(pUpdatable);
}

// ---> Drawable
void Scene::registerEntity(Drawable* pDrawable)
{
	_drawableManager.registerEntity(pDrawable);
}

void Scene::deregisterEntity(Drawable* pDrawable)
{
	_drawableManager.deregisterEntity(pDrawable);
}

void Scene::register2DEntity(Drawable* pDrawable)
{
	_drawableManager.register2DEntity(pDrawable);
}

void Scene::deregister2DEntity(Drawable* pDrawable)
{
	_drawableManager.deregister2DEntity(pDrawable);
}

// ---> Alarmable
void Scene::registerEntity(Alarmable* pAlarmable, const float timeDelay, AlarmID alarmID)
{
	_alarmableManager.registerAlarmWithDelayTime(pAlarmable, timeDelay, alarmID);
}

void Scene::deregisterEntity(Alarmable* pAlarmable, AlarmID alarmID)
{
	_alarmableManager.deregisterAlarm(pAlarmable, alarmID);
}

// ---> Inputable
void Scene::registerEntity(Inputable* pInputable, AZUL_KEY key, InputEvent eventType)
{
	_keyboardEventManager.registerEntityWithKeyAndKeyEvent(pInputable, key, eventType);
}

void Scene::deregisterEntity(Inputable* pInputable, AZUL_KEY key, InputEvent eventType)
{
	_keyboardEventManager.deregisterEntityWithKeyAndKeyEvent(pInputable, key, eventType);
}

void Scene::executeCommands()
{
	_sceneRegistrationBroker.executeCommands();
}

CollisionManager& Scene::getCollisionManager()
{
	return _collisionManager;
}
