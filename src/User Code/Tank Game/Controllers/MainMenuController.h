#ifndef _MainMenuController
#define _MainMenuController

#include <vector>
#include "GameObject.h"

class SpriteString;
class Sprite;
class Scene;
class SceneSwitcher;

class MainMenuController : public GameObject
{
public:
	MainMenuController();
	MainMenuController(const MainMenuController&) = default;
	MainMenuController& operator=(const MainMenuController&) = default;
	MainMenuController(MainMenuController&&) = default;
	MainMenuController& operator=(MainMenuController&&) = default;
	~MainMenuController();

	void setLevelToChangeTo(Scene* pScene);

private:
	virtual void draw2D() override;
	virtual void keyPressed(AZUL_KEY) override;

	void goToLevel();

private:
	Sprite* _pMainMenuSprite;
	std::vector<SpriteString*> _messages;
	SceneSwitcher* _pSceneSwitcher;

};
#endif // !_MainMenuController

//-----------------------------------------------------------------------------------------------------------------------------
// MainMenuController Comment Template
//-----------------------------------------------------------------------------------------------------------------------------