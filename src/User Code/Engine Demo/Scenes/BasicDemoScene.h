#ifndef _BasicDemoScene
#define _BasicDemoScene

#include "Scene.h"
#include "AzulCore.h"

class WorldPlane;
class WorldAxes;
class BasicCar;

class SceneChanger;

class BasicDemoScene : public Scene
{
public:
	// Big Six
	BasicDemoScene() = default;
	BasicDemoScene(const BasicDemoScene&) = default;
	BasicDemoScene& operator=(const BasicDemoScene&) = default;
	BasicDemoScene(BasicDemoScene&&) = default;
	BasicDemoScene& operator=(BasicDemoScene&&) = default;
	~BasicDemoScene() = default;

private:
	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

private:
	WorldPlane* _pWorldPlane;
	WorldAxes* _pWorldAxes;
	BasicCar* _pBasicCar;

	SceneChanger* _pSceneChanger;
};

#endif // !_BasicDemoScene