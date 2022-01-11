#ifndef _GameController
#define _GameController

#include <vector>
#include "GameObject.h"
#include "RecycleTankToGameControllerStrategy.h"

class Tank;
class TankSpawner;
class Scene;
class SceneSwitcher;
class SpriteString;

class GameController : public GameObject
{
public:
	GameController();
	GameController(const GameController&) = default;
	GameController& operator=(const GameController&) = default;
	GameController(GameController&&) = default;
	GameController& operator=(GameController&&) = default;
	~GameController();

	void setTarget(Tank*);

	void setCurrentScene(Scene*);
	void setNextScene(Scene*);

	void switchToNextScene();
	void switchToMissionFailed();

private:
	virtual void update() override;
	virtual void draw2D() override;
	virtual void alarm0() override;

	void goToNextScene();
	void clearScenePointers();


private:
	Tank* _pTarget;
	Scene* _pCurrentScene;
	SceneSwitcher* _pNextScene;

};
#endif // !_GameController

//-----------------------------------------------------------------------------------------------------------------------------
// GameController Comment Template
//-----------------------------------------------------------------------------------------------------------------------------