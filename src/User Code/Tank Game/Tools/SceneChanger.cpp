#include "SceneChanger.h"
#include "SceneSwitcher.h"

const AZUL_KEY SceneChanger::NEXT_SCENE_KEY = AZUL_KEY::KEY_ARROW_UP;
const AZUL_KEY SceneChanger::PREVIOUS_SCENE_KEY = AZUL_KEY::KEY_ARROW_DOWN;

SceneChanger::SceneChanger()
	: _pNextScene(new SceneSwitcher()),
	_pPreviousScene(new SceneSwitcher())
{
	// Registrating key press to as way to call the switch scene function calls
	submitKeyRegistration(NEXT_SCENE_KEY, InputEvent::KEY_PRESS);
	submitKeyRegistration(PREVIOUS_SCENE_KEY, InputEvent::KEY_PRESS);
}

SceneChanger::~SceneChanger()
{
	delete _pNextScene;
	delete _pPreviousScene;
}

void SceneChanger::setNextScene(Scene* pNextScene)
{
	_pNextScene->setSceneToSwitchTo(pNextScene);
}

void SceneChanger::setPreviousScene(Scene* pPreviousScene)
{
	_pPreviousScene->setSceneToSwitchTo(pPreviousScene);
}

void SceneChanger::keyPressed(AZUL_KEY key)
{
	// Here is where we check which registered key was pressed.
	switch (key)
	{
	case SceneChanger::NEXT_SCENE_KEY:
		_pNextScene->switchScene();
		break;
	case SceneChanger::PREVIOUS_SCENE_KEY:
		_pPreviousScene->switchScene();
		break;
	}
}