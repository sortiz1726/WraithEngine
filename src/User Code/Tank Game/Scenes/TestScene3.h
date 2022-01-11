#ifndef _TestScene3
#define _TestScene3

#include <vector>
#include "Scene.h"

class CameraController;
class CameraSwitcher;
class Camera;
class WorldPlane;
class WorldAxes;
class DebugRegistrationCube;
class TesterObject;
class SceneChanger;

class TestScene3 : public Scene
{
public:
	TestScene3() = default;
	TestScene3(const TestScene3&) = default;
	TestScene3& operator=(const TestScene3&) = default;
	TestScene3(TestScene3&&) = default;
	TestScene3& operator=(TestScene3&&) = default;
	~TestScene3() = default;

	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

private:
	CameraSwitcher* _pCameraSwitcher;
	Camera* _pTopViewCamera;
	Camera* _pSideViewCamera;

	WorldPlane* _pWorldPlane;
	WorldAxes* _pWorldAxes;

	int _numberOfEnemyTanks = 8;

	DebugRegistrationCube* _pDebugRegistrationCubeX;
	DebugRegistrationCube* _pDebugRegistrationCubeY;
	DebugRegistrationCube* _pDebugRegistrationCubeZ;

	TesterObject* _pTesterObject;

	SceneChanger* _pSceneChanger;
};

#endif // !_TestScene3