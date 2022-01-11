#include "MainMenu.h"
#include "MainMenuController.h"
#include "Level1.h"

void MainMenu::initialize()
{
	_pMainMenuController = new MainMenuController();
	_pMainMenuController->setLevelToChangeTo(new Level1());
}

void MainMenu::sceneEnd()
{
	delete _pMainMenuController;
}
