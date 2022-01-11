#ifndef _MissionFailedController
#define _MissionFailedController

#include <vector>
#include "GameObject.h"

class SpriteString;
class Sprite;
class Scene;
class SceneSwitcher;

class MissionFailedController : public GameObject
{
public:
	MissionFailedController();
	MissionFailedController(const MissionFailedController&) = default;
	MissionFailedController& operator=(const MissionFailedController&) = default;
	MissionFailedController(MissionFailedController&&) = default;
	MissionFailedController& operator=(MissionFailedController&&) = default;
	~MissionFailedController();

	void setLevelToChangeTo(Scene* pScene);

private:
	virtual void draw2D() override;
	virtual void keyPressed(AZUL_KEY) override;

	void goToLevel();

private:
	Sprite* _pMissionFailedSprite;
	std::vector<SpriteString*> _messages;
	SceneSwitcher* _pSceneSwitcher;

};
#endif // !_MissionFailedController

//-----------------------------------------------------------------------------------------------------------------------------
// MissionFailedController Comment Template
//-----------------------------------------------------------------------------------------------------------------------------