#ifndef _TestScene
#define _TestScene

#include "Scene.h"
#include <vector>

class CameraSwitcher;
class Camera;
class SceneChanger;
class WorldPlane;
class WorldAxes;
class DebugRegistrationCube;
class TesterObject;
class Warehouse;

class GameObject;

class TestScene : public Scene
{
public:
	TestScene() = default;
	TestScene(const TestScene&) = default;
	TestScene& operator=(const TestScene&) = default;
	TestScene(TestScene&&) = default;
	TestScene& operator=(TestScene&&) = default;
	~TestScene() = default;

	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

private:
	CameraSwitcher* _pCameraSwitcher;
	Camera* _pTopViewCamera;
	Camera* _pSideViewCamera;

	int _numberOfEnemyTanks = 0;

	WorldPlane* _pWorldPlane;
	WorldAxes* _pWorldAxes;

	Warehouse* _pWarehouse;

	DebugRegistrationCube* _pDebugRegistrationCubeX;
	DebugRegistrationCube* _pDebugRegistrationCubeY;
	DebugRegistrationCube* _pDebugRegistrationCubeZ;

	TesterObject* _pTesterObject;

	SceneChanger* _pSceneChanger;

	std::vector<GameObject*> _gameObjects;
};
#endif // !_TestScene

//-----------------------------------------------------------------------------------------------------------------------------
// TestScene Comment Template
//-----------------------------------------------------------------------------------------------------------------------------