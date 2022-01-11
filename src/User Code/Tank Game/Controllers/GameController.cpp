#include "GameController.h"
#include "Tank.h"
#include "SceneSwitcher.h"
#include "SceneManager.h"
#include "Wraith.h"
#include "MissionFailed.h"

GameController::GameController()
	: _pTarget(nullptr),
	_pCurrentScene(nullptr), _pNextScene(new SceneSwitcher())
{
	submitUpdateRegistration();
}

GameController::~GameController()
{
	clearScenePointers();
}

void GameController::clearScenePointers()
{
	delete _pCurrentScene;
	delete _pNextScene;
}

#pragma region GameObject Properties

void GameController::update()
{
	if (_pTarget->getHealth() <= 0.0f)
	{
		switchToMissionFailed();
	}
}

void GameController::draw2D()
{
	
}

void GameController::alarm0()
{
	submitAlarmRegistration(3.0f, AlarmID::ALARM_0);
}

#pragma endregion

#pragma region Actions

void GameController::switchToMissionFailed()
{
	MissionFailed* pMissonFailed = new MissionFailed();
	pMissonFailed->setRestartScene(_pCurrentScene);
	_pCurrentScene = nullptr;
	SceneManager::SetNextScene(pMissonFailed);
}

void GameController::goToNextScene()
{
	_pNextScene->switchScene();
}

void GameController::switchToNextScene()
{
	_pNextScene->switchScene();
}

#pragma endregion

#pragma region Setters/Getters

void GameController::setTarget(Tank* pTarget)
{
	_pTarget = pTarget;
}

void GameController::setCurrentScene(Scene* pCurrentScene)
{
	_pCurrentScene = pCurrentScene;
}

void GameController::setNextScene(Scene* pNextScene)
{
	_pNextScene->setSceneToSwitchTo(pNextScene);
}

#pragma endregion
