#include "MissionFailed.h"
#include "MissionFailedController.h"
#include "Level1.h"

void MissionFailed::initialize()
{
	_pMissionFailedController = new MissionFailedController();
	_pMissionFailedController->setLevelToChangeTo(_pRestartScene);
}

void MissionFailed::sceneEnd()
{
	delete _pMissionFailedController;
}

void MissionFailed::setRestartScene(Scene* pRestartScene)
{
	_pRestartScene = pRestartScene;
}
