#include "Updatable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneAttorney.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"

Updatable::Updatable()
	: _pUpdateRegistrationCommand(new UpdateRegistrationCommand(this)),
	_pUpdateDeregistrationCommand(new UpdateDeregistrationCommand(this)),
	_currentRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED)
{}

Updatable::~Updatable()
{
	Updatable::DebugPrint("Destructor Called");
	delete _pUpdateRegistrationCommand;
	delete _pUpdateDeregistrationCommand;
}

//-----------------------------------------------------------------------------------------------------------------------------
//  Registration/Deregistration
//-----------------------------------------------------------------------------------------------------------------------------
void Updatable::submitUpdateRegistration()
{
	assert(_currentRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pUpdateRegistrationCommand);
	_currentRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void Updatable::registerToScene()
{
	assert(_currentRegistrationState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::RegistrationAccess::RegisterEntity(SceneManager::GetCurrentScene(), this);
	_currentRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void Updatable::submitUpdateDeregistration()
{
	assert(_currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pUpdateDeregistrationCommand);
	_currentRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}

void Updatable::deregisterFromScene()
{
	assert(_currentRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	//auto a = *_deleteReference;
	//AZUL_UNUSED(a);
	SceneAttorney::RegistrationAccess::DeregisterEntity(SceneManager::GetCurrentScene(), this);
	_currentRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

bool Updatable::isRegisteredForUpdate() const
{
	return _currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setter/Getters of Terminate Reference
//-----------------------------------------------------------------------------------------------------------------------------
void Updatable::setDeleteReference(const UpdatableManager::StorageListReference& deleteReference)
{
	_deleteReference = deleteReference;
}

UpdatableManager::StorageListReference Updatable::getDeleteReference() const
{
	return _deleteReference;
}

//-----------------------------------------------------------------------------------------------------------------------------
//  To be implemented by user in object derived from GameObject (NOT directly derived from Updatable)
//-----------------------------------------------------------------------------------------------------------------------------
void Updatable::update()
{
	// Does nothing
}


//-----------------------------------------------------------------------------------------------------------------------------
// For personal debugging
//-----------------------------------------------------------------------------------------------------------------------------

const std::string Updatable::DEBUG_TITLE_MESSAGE = "Updatable_DEBUG: ";

void Updatable::DebugPrint(const std::string& message)
{
	(void(message));
#if Updatable_DEBUG
	if (message.size() == 0)
	{
		Trace::out("\n");
	}
	else
	{
		std::string finalMessage = Updatable::DEBUG_TITLE_MESSAGE + message + std::string("\n");
		Trace::out("%s", finalMessage.c_str());
	}
#endif // !Updatable_DEBUG
}