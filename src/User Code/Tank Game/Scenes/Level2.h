#ifndef _Level2
#define _Level2

#include <vector>
#include "Scene.h"

class CameraSwitcher;
class Camera;
class SceneChanger;

class WorldAxes;
class GroundPlane;

class HealthBar;
class AmmoBar;
class GameController;
class TankKillMonitor;
class AlarmController;
class DestroyMonitor;

class WallBuilder;
class SceneryBuilder;
class GameObject;

class Tank;

class Level2 : public Scene
{
public:
	Level2() = default;
	Level2(const Level2&) = default;
	Level2& operator=(const Level2&) = default;
	Level2(Level2&&) = default;
	Level2& operator=(Level2&&) = default;
	~Level2() = default;

	// Inherited via Scene
private:
	virtual void initialize() override;

	void initializedCameras();

	void SetCollisionTests();

	void initializeArches();

	void initializeWalls();

	void initializeTurrets(Tank* pTarget);


	void initializeNorthStreet();
	void initializeEastStreet();
	void initializeSouthStreet();
	void initializeWestStreet();

	void initializeWarehouses();
	void initializeCottages();
	void initializeTrees();
	bool canSpawnTreeHere(const Vect& position) const;
	void initializeWindMills();
	void initializeCampfires();

	virtual void sceneEnd() override;

private:
	CameraSwitcher* _pCameraSwitcher;
	Camera* _pTopViewCamera;
	Camera* _pSideViewCamera;

	SceneChanger* _pSceneChanger;

	WorldAxes* _pWorldAxes;
	GroundPlane* _pGroundPlane;

	HealthBar* _pPlayerHealthBar;
	AmmoBar* _pAmmoBar;

	SceneryBuilder* _pSceneryBuilder;

	GameController* _pGameController;
	TankKillMonitor* _pTankKillMonitor;
	AlarmController* _pAlarmController;
	DestroyMonitor* _pDestroyMonitor;
	WallBuilder* _pWallBuilder;

	std::vector<GameObject*> _gameObjects;
};
#endif // !_Level2

//-----------------------------------------------------------------------------------------------------------------------------
// Level2 Comment Template
//-----------------------------------------------------------------------------------------------------------------------------