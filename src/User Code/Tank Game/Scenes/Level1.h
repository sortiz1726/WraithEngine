#ifndef _Level1
#define _Level1

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

class WallBuilder;
class SceneryBuilder;
class GameObject;

class Level1 : public Scene
{
public:
	Level1() = default;
	Level1(const Level1&) = default;
	Level1& operator=(const Level1&) = default;
	Level1(Level1&&) = default;
	Level1& operator=(Level1&&) = default;
	~Level1() = default;

	// Inherited via Scene
private:
	virtual void initialize() override;

	void initializedCameras();

	void SetCollisionTests();

	void initializeArches();

	void initializeWalls();


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
	WallBuilder* _pWallBuilder;

	std::vector<GameObject*> _gameObjects;
};
#endif // !_Level1

//-----------------------------------------------------------------------------------------------------------------------------
// Level1 Comment Template
//-----------------------------------------------------------------------------------------------------------------------------