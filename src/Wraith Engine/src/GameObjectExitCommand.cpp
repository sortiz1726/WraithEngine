#include "GameObjectExitCommand.h"
#include "GameObjectAttorney.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject* pGameObject)
	: _pGameObject(pGameObject)
{
	assert(_pGameObject != nullptr);
}

void GameObjectExitCommand::execute()
{
	GameObjectAttorney::RegistrationAccess::DisconnectFromScene(_pGameObject);
}
