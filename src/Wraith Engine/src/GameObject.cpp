#include "GameObject.h"
#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"
#include "SceneAttorney.h"
#include "SceneManager.h"

GameObject::GameObject()
	: _pGameObjectEntryCommand(new GameObjectEntryCommand(this)),
	_pGameObjectExitCommand(new GameObjectExitCommand(this)),
	_currentRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED)
{}

GameObject::~GameObject()
{
	delete _pGameObjectEntryCommand;
	delete _pGameObjectExitCommand;
}

void GameObject::submitSceneEntry()
{
	assert(_currentRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pGameObjectEntryCommand);
	_currentRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void GameObject::connectToScene()
{
	assert(_currentRegistrationState == RegistrationState::PENDING_REGISTRATION);
	sceneEntry();
	_currentRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void GameObject::submitSceneExit()
{
	if (_currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED)
	{
		SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pGameObjectExitCommand);
		_currentRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void GameObject::disconnectFromScene()
{
	assert(_currentRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	sceneExit();
	_currentRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void GameObject::sceneEntry()
{
}

void GameObject::sceneExit()
{
}
