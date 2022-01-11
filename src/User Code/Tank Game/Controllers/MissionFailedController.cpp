#include "MissionFailedController.h"
#include "Sprite.h"
#include "SpriteString.h"
#include "SpriteFontManager.h"
#include "Wraith.h"
#include "SceneSwitcher.h"

MissionFailedController::MissionFailedController()
	: _pSceneSwitcher(new SceneSwitcher())
{
	_pMissionFailedSprite = new Sprite("MissionFailedImage");
	float xPosition, yPosition;
	xPosition = Wraith::GetWindowWidth() / 2.0f;
	yPosition = Wraith::GetWindowHeight() / 2.0f;
	_pMissionFailedSprite->setPosition(xPosition, yPosition);


	SpriteFont* pFont = SpriteFontManager::GetSpriteFont("MilitaryGreenFont");
	
	int xPositionMessage = Wraith::GetWindowHeight() - 100;
	SpriteString* pSpriteString = new SpriteString();
	pSpriteString->set(pFont, "Missioned Failed!", (Wraith::GetWindowWidth() / 2) - pSpriteString->getWidth() / 2, xPositionMessage);
	_messages.push_back(pSpriteString);

	xPositionMessage -= pSpriteString->getHeight();
	xPositionMessage -= pSpriteString->getHeight();
	pSpriteString = new SpriteString();
	pSpriteString->set(pFont, "Press Enter to try again", (Wraith::GetWindowWidth() / 2) - 200, xPositionMessage);
	_messages.push_back(pSpriteString);


	submitDraw2DRegistration();
	submitKeyRegistration(AZUL_KEY::KEY_ENTER, InputEvent::KEY_PRESS);
}

MissionFailedController::~MissionFailedController()
{
	delete _pMissionFailedSprite;
	delete _pSceneSwitcher;
	for (auto& message : _messages)
	{
		delete message;
	}
}

void MissionFailedController::setLevelToChangeTo(Scene* pScene)
{
	_pSceneSwitcher->setSceneToSwitchTo(pScene);
}

void MissionFailedController::draw2D()
{
	_pMissionFailedSprite->render();
	for (auto& message : _messages)
	{
		message->render();
	}
}

void MissionFailedController::keyPressed(AZUL_KEY key)
{
	if (key == AZUL_KEY::KEY_ENTER)
	{
		goToLevel();
	}
}

void MissionFailedController::goToLevel()
{
	_pSceneSwitcher->switchScene();
}
