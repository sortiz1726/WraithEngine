#ifndef _TestScene2
#define _TestScene2

#include "Scene.h"
#include "AzulCore.h"


class CameraController;
class SpaceFrigate;
class WorldPlane;
class WorldAxes;
class DebugRegistrationCube;
class TesterObject;
class SceneChanger;

class TestScene2 : public Scene
{
public:
	// Big Six
	TestScene2() = default;
	TestScene2(const TestScene2&) = default;
	TestScene2& operator=(const TestScene2&) = default;
	TestScene2(TestScene2&&) = default;
	TestScene2& operator=(TestScene2&&) = default;
	~TestScene2() = default;

private:
	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

private:
	// Game Objects
	CameraController* _pCameraController;
	SpaceFrigate* _pSpaceFrigate;
	WorldPlane* _pWorldPlane;
	WorldAxes* _pWorldAxes;

	DebugRegistrationCube* _pDebugRegistrationCube;
	DebugRegistrationCube* _pDebugRegistrationCubeX;
	DebugRegistrationCube* _pDebugRegistrationCubeY;
	DebugRegistrationCube* _pDebugRegistrationCubeZ;

	TesterObject* _pTesterObject;

	SceneChanger* _pSceneChanger;
};

#endif // !_TestScene2

//-----------------------------------------------------------------------------------------------------------------------------
// TestScene2 Comment Template
//-----------------------------------------------------------------------------------------------------------------------------
