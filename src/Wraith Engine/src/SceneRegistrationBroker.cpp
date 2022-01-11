#include "SceneRegistrationBroker.h"
#include "SceneRegistrationCommand.h"

void SceneRegistrationBroker::addCommand(SceneRegistrationCommand* pCommand)
{
	_sceneRegistrationCommands.push_back(pCommand);
}

void SceneRegistrationBroker::executeCommands()
{
	while (!_sceneRegistrationCommands.empty())
	{
		SceneRegistrationCommand* pCommand = _sceneRegistrationCommands.front();
		pCommand->execute();
		_sceneRegistrationCommands.pop_front();
	}
	_sceneRegistrationCommands.clear();
}
