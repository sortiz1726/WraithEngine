#ifndef _MainMenu
#define _MainMenu

#include "Scene.h"

class MainMenuController;

class MainMenu : public Scene
{
public:
	MainMenu() = default;
	MainMenu(const MainMenu&) = default;
	MainMenu& operator=(const MainMenu&) = default;
	MainMenu(MainMenu&&) = default;
	MainMenu& operator=(MainMenu&&) = default;
	~MainMenu() = default;

	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

private:
	MainMenuController* _pMainMenuController;
};
#endif // !_MainMenu

//-----------------------------------------------------------------------------------------------------------------------------
// MainMenu Comment Template
//-----------------------------------------------------------------------------------------------------------------------------