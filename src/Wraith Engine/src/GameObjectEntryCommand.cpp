#include "GameObjectEntryCommand.h"
#include "GameObjectAttorney.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject* pGameObject)
	: _pGameObject(pGameObject)
{
	assert(_pGameObject != nullptr);
}

void GameObjectEntryCommand::execute()
{
	GameObjectAttorney::RegistrationAccess::ConnectToScene(_pGameObject);
}
