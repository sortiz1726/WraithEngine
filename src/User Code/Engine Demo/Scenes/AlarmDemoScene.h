#ifndef _AlarmDemoScene
#define _AlarmDemoScene

#include "Scene.h"
#include "AzulCore.h"

class WorldPlane;
class WorldAxes;
class AlarmCar;

class SceneChanger;

class AlarmDemoScene : public Scene
{
public:
	AlarmDemoScene() = default;
	AlarmDemoScene(const AlarmDemoScene&) = default;
	AlarmDemoScene& operator=(const AlarmDemoScene&) = default;
	AlarmDemoScene(AlarmDemoScene&&) = default;
	AlarmDemoScene& operator=(AlarmDemoScene&&) = default;
	~AlarmDemoScene() = default;

private:
	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

private:
	WorldPlane* _pWorldPlane;
	WorldAxes* _pWorldAxes;
	AlarmCar* _pAlarmCar;

	SceneChanger* _pSceneChanger;
};

#endif // !_AlarmDemoScene