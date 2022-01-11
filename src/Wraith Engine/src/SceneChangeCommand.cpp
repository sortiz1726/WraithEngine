#include "SceneChangeCommand.h"
#include "SceneManagerAttorney.h"

SceneChangeCommand::SceneChangeCommand()
	: _pSceneToChangeTo(nullptr)
{}

void SceneChangeCommand::setSceneToChangeTo(Scene* pSceneToChangeTo)
{
	_pSceneToChangeTo = pSceneToChangeTo;
}

void SceneChangeCommand::execute()
{
	SceneManagerAttorney::SceneAccess::ChangeScene(_pSceneToChangeTo);
}
