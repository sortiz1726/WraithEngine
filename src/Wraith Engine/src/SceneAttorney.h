#ifndef _SceneAttorney
#define _SceneAttorney

#include "Scene.h"
#include "SceneManager.h"
#include "InputTypes.h"

class SceneRegistrationCommand;
class CollisionManager;
class TerrainManager;

class SceneAttorney
{
private:
	SceneAttorney() = delete;
	SceneAttorney(const SceneAttorney&) = delete;
	SceneAttorney& operator=(const SceneAttorney&) = delete;
	SceneAttorney(SceneAttorney&&) = delete;
	SceneAttorney& operator=(SceneAttorney&&) = delete;
	~SceneAttorney() = delete;

public:
	class InitializeAccess
	{
		friend class SceneManager;

		static void Initialize(Scene* pScene) { pScene->initialize(); }
	};

	class GameLoopAccess
	{
		friend class SceneManager;

		static void Update(Scene* pScene) { pScene->update(); }
		static void Draw(Scene* pScene) { pScene->draw(); }
	};

	class RegistrationAccess
	{
		friend class Updatable;
		friend class Drawable;
		friend class Alarmable;
		friend class Inputable;
		friend class Collidable;
		friend class GameObject;

		static void SubmitCommand(Scene* pScene, SceneRegistrationCommand* pCommand) { pScene->submitCommand(pCommand); }

		static void RegisterEntity(Scene* pScene, Updatable* pUpdatable) { pScene->registerEntity(pUpdatable); }
		static void RegisterEntity(Scene* pScene, Drawable* pDrawable) { pScene->registerEntity(pDrawable); }
		static void Register2DEntity(Scene* pScene, Drawable* pDrawable) { pScene->register2DEntity(pDrawable); }
		static void RegisterEntity(Scene* pScene, Alarmable* pAlarmable, float timeDelay, AlarmID alarmID) { pScene->registerEntity(pAlarmable, timeDelay, alarmID); }
		static void RegisterEntity(Scene* pScene, Inputable* pInputable, AZUL_KEY key, InputEvent eventType) { pScene->registerEntity(pInputable, key, eventType); }

		static void DeregisterEntity(Scene* pScene, Updatable* pUpdatable) { pScene->deregisterEntity(pUpdatable); }
		static void DeregisterEntity(Scene* pScene, Drawable* pDrawable) { pScene->deregisterEntity(pDrawable); }
		static void Deregister2DEntity(Scene* pScene, Drawable* pDrawable) { pScene->deregister2DEntity(pDrawable); }
		static void DeregisterEntity(Scene* pScene, Alarmable* pAlarmable, AlarmID alarmID) { pScene->deregisterEntity(pAlarmable, alarmID); }
		static void DeregisterEntity(Scene* pScene, Inputable* pInputable, AZUL_KEY key, InputEvent eventType) { pScene->deregisterEntity(pInputable, key, eventType); }

		static CollisionManager& GetCollisionManager(Scene* pScene) { return pScene->getCollisionManager(); }
		static CollisionManager& GetCollisionManager() { return SceneManager::GetCurrentScene()->getCollisionManager(); }
	};

	class EndAccess
	{
		friend class SceneManager;

		static void DeregisterTerrain(Scene* pScene) { pScene->_terrainManager.deregisterTerrain(); }
		static void ExecuteCommands(Scene* pScene) { pScene->executeCommands(); };
		static void SceneEnd(Scene* pScene) { pScene->sceneEnd(); }
	};
};
#endif // !_SceneAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// SceneAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------