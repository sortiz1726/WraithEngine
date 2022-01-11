#ifndef _CollisionDemoScene
#define _CollisionDemoScene

#include "Scene.h"
#include "AzulCore.h"

class WorldPlane;
class WorldAxes;
class CollisionCar;
class OtherCollisionCar;

class SceneChanger;

class CollisionDemoScene : public Scene
{
public:
	// Big Six
	CollisionDemoScene() = default;
	CollisionDemoScene(const CollisionDemoScene&) = default;
	CollisionDemoScene& operator=(const CollisionDemoScene&) = default;
	CollisionDemoScene(CollisionDemoScene&&) = default;
	CollisionDemoScene& operator=(CollisionDemoScene&&) = default;
	~CollisionDemoScene() = default;

private:
	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

private:
	WorldPlane* _pWorldPlane;
	WorldAxes* _pWorldAxes;
	CollisionCar* _pCollisionCar;
	OtherCollisionCar* _pOtherCollisionCar;

	SceneChanger* _pSceneChanger;
};

#endif // !_CollisionDemoScene