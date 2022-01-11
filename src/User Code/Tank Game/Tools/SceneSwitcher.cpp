#include "SceneSwitcher.h"
#include "SceneManager.h"
#include "Scene.h"

SceneSwitcher::SceneSwitcher()
	: _pSceneToSwitchTo(nullptr)
{}

SceneSwitcher::~SceneSwitcher()
{
	delete _pSceneToSwitchTo;
}

void SceneSwitcher::setSceneToSwitchTo(Scene* pSceneToSwitchTo)
{
	if (_pSceneToSwitchTo != nullptr)
	{
		delete _pSceneToSwitchTo;
	}
	_pSceneToSwitchTo = pSceneToSwitchTo;
}

void SceneSwitcher::switchScene()
{
	if (_pSceneToSwitchTo != nullptr)
	{
		SceneManager::SetNextScene(_pSceneToSwitchTo);
		_pSceneToSwitchTo = nullptr;
	}
}
