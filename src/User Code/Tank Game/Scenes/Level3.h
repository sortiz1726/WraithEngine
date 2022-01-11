#ifndef _Level3
#define _Level3

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
class DestinationMonitor;

class WallBuilder;
class SceneryBuilder;
class GameObject;

class Tank;

class Level3 : public Scene
{
public:
	Level3() = default;
	Level3(const Level3&) = default;
	Level3& operator=(const Level3&) = default;
	Level3(Level3&&) = default;
	Level3& operator=(Level3&&) = default;
	~Level3() = default;

	// Inherited via Scene
private:
	virtual void initialize() override;

	void initializedCameras();
	void SetCollisionTests();
	void initializeScenery();

	void initializeWalls();
	void initializeMarkers();

	void initializeTrees();
	bool canSpawnTreeHere(const Vect& position) const;

	void initializeTurrets(Tank*);

	void initializeWindMills();
	void initializeCottages();
	void initializeWarehouse();

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
	DestinationMonitor* _pDestintationMonitor;
	WallBuilder* _pWallBuilder;

	std::vector<GameObject*> _gameObjects;
};
#endif // !_Level3

//-----------------------------------------------------------------------------------------------------------------------------
// Level3 Comment Template
//-----------------------------------------------------------------------------------------------------------------------------