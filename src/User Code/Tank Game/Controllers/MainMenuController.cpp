#include "MainMenuController.h"
#include "Sprite.h"
#include "SpriteString.h"
#include "SpriteFontManager.h"
#include "Wraith.h"
#include "SceneSwitcher.h"

MainMenuController::MainMenuController()
	: _pSceneSwitcher(new SceneSwitcher())
{
	_pMainMenuSprite = new Sprite("MainMenuImage");
	float xPosition, yPosition;
	xPosition = Wraith::GetWindowWidth() / 2.0f;
	yPosition = Wraith::GetWindowHeight() / 2.0f;
	_pMainMenuSprite->setPosition(xPosition, yPosition);


	SpriteFont* pFont = SpriteFontManager::GetSpriteFont("MilitaryGreenFont");
	
	int xPositionMessage = Wraith::GetWindowHeight() - 30;
	SpriteString* pSpriteString = new SpriteString();
	pSpriteString->set(pFont, "TANK GAME V 2.0!", (Wraith::GetWindowWidth() / 2) - pSpriteString->getWidth() / 2, xPositionMessage);
	_messages.push_back(pSpriteString);

	xPositionMessage -= pSpriteString->getHeight();
	pSpriteString = new SpriteString();
	pSpriteString->set(pFont, "CONTROLS:", 0, xPositionMessage);
	_messages.push_back(pSpriteString);

	xPositionMessage -= pSpriteString->getHeight();
	pSpriteString = new SpriteString();
	pSpriteString->set(pFont, "W S: forwards and backwards", 0, xPositionMessage);
	_messages.push_back(pSpriteString);

	xPositionMessage -= pSpriteString->getHeight();
	pSpriteString = new SpriteString();
	pSpriteString->set(pFont, "A D: turn Tank Hull", 0, xPositionMessage);
	_messages.push_back(pSpriteString);

	xPositionMessage -= pSpriteString->getHeight();
	pSpriteString = new SpriteString();
	pSpriteString->set(pFont, "J L: turn Tank Turret", 0, xPositionMessage);
	_messages.push_back(pSpriteString);

	xPositionMessage -= pSpriteString->getHeight();
	pSpriteString = new SpriteString();
	pSpriteString->set(pFont, "SPACEBAR: Fire", 0, xPositionMessage);
	_messages.push_back(pSpriteString);

	xPositionMessage -= pSpriteString->getHeight();
	xPositionMessage -= pSpriteString->getHeight();
	pSpriteString = new SpriteString();
	pSpriteString->set(pFont, "PRESS ENTER TO START", 0, xPositionMessage);
	pSpriteString->set(pFont, "PRESS ENTER TO START", (Wraith::GetWindowWidth() / 2) - pSpriteString->getWidth() / 2, xPositionMessage);
	_messages.push_back(pSpriteString);


	submitDraw2DRegistration();
	submitKeyRegistration(AZUL_KEY::KEY_ENTER, InputEvent::KEY_PRESS);
}

MainMenuController::~MainMenuController()
{
	delete _pMainMenuSprite;
	delete _pSceneSwitcher;
	for (auto& message : _messages)
	{
		delete message;
	}
}

void MainMenuController::setLevelToChangeTo(Scene* pScene)
{
	_pSceneSwitcher->setSceneToSwitchTo(pScene);
}

void MainMenuController::draw2D()
{
	_pMainMenuSprite->render();
	for (auto& message : _messages)
	{
		message->render();
	}
}

void MainMenuController::keyPressed(AZUL_KEY key)
{
	if (key == AZUL_KEY::KEY_ENTER)
	{
		Trace::out("MainMenu Controller: Entered Pressed\n");
		goToLevel();
	}
}

void MainMenuController::goToLevel()
{
	_pSceneSwitcher->switchScene();
}
