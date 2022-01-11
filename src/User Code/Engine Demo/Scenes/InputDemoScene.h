#ifndef _InputDemoScene
#define _InputDemoScene

#include "Scene.h"
#include "AzulCore.h"

class WorldPlane;
class WorldAxes;
class InputCar;

class SceneChanger;

class InputDemoScene : public Scene
{
public:
	// Big Six
	InputDemoScene() = default;
	InputDemoScene(const InputDemoScene&) = default;
	InputDemoScene& operator=(const InputDemoScene&) = default;
	InputDemoScene(InputDemoScene&&) = default;
	InputDemoScene& operator=(InputDemoScene&&) = default;
	~InputDemoScene() = default;

private:
	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

private:
	WorldPlane* _pWorldPlane;
	WorldAxes* _pWorldAxes;
	InputCar* _pInputCar;

	SceneChanger* _pSceneChanger;

};

#endif // !_InputDemoScene