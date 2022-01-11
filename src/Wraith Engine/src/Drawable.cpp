#include "Drawable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneAttorney.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"
#include "Draw2DRegistrationCommand.h"
#include "Draw2DDeregistrationCommand.h"

Drawable::Drawable()
	: _pDrawRegistrationCommand(new DrawRegistrationCommand(this)),
	_pDrawDeregistrationCommand(new DrawDeregistrationCommand(this)),
	_currentRegistrationState(RegistrationState::CURRENTLY_DEREGISTERED),
	_pDraw2DRegistrationCommand(new Draw2DRegistrationCommand(this)),
	_pDraw2DDeregistrationCommand(new Draw2DDeregistrationCommand(this)),
	_currentRegistrationState2D(RegistrationState::CURRENTLY_DEREGISTERED)
{}

Drawable::~Drawable()
{
	Drawable::DebugPrint("Destructor Called");
	delete _pDrawRegistrationCommand;
	delete _pDrawDeregistrationCommand;
	delete _pDraw2DRegistrationCommand;
	delete _pDraw2DDeregistrationCommand;
}

//-----------------------------------------------------------------------------------------------------------------------------
//  Registration/Deregistration
//-----------------------------------------------------------------------------------------------------------------------------
void Drawable::submitDrawRegistration()
{
	assert(_currentRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pDrawRegistrationCommand);
	_currentRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::registerToScene()
{
	assert(_currentRegistrationState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::RegistrationAccess::RegisterEntity(SceneManager::GetCurrentScene(), this);
	_currentRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::submitDrawDeregistration()
{
	assert(_currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pDrawDeregistrationCommand);
	_currentRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}

void Drawable::deregisterFromScene()
{
	assert(_currentRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::RegistrationAccess::DeregisterEntity(SceneManager::GetCurrentScene(), this);
	_currentRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

// ---> For 2D registration
void Drawable::submitDraw2DRegistration()
{
	assert(_currentRegistrationState2D == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pDraw2DRegistrationCommand);
	_currentRegistrationState2D = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::register2DToScene()
{
	assert(_currentRegistrationState2D == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::RegistrationAccess::Register2DEntity(SceneManager::GetCurrentScene(), this);
	_currentRegistrationState2D = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::deregister2DFromScene()
{
	assert(_currentRegistrationState2D == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::RegistrationAccess::Deregister2DEntity(SceneManager::GetCurrentScene(), this);
	_currentRegistrationState2D = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Drawable::submitDraw2DDeregistration()
{
	assert(_currentRegistrationState2D == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), _pDraw2DDeregistrationCommand);
	_currentRegistrationState2D = RegistrationState::PENDING_DEREGISTRATION;
}

bool Drawable::isRegisteredForDraw() const
{
	return _currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED;
}


bool Drawable::isRegisteredForDraw2D() const
{
	return _currentRegistrationState2D == RegistrationState::CURRENTLY_REGISTERED;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setter/Getter Terminate Reference
//-----------------------------------------------------------------------------------------------------------------------------
void Drawable::setDeleteReference(const DrawableManager::StorageListReference& deleteReference)
{
	_deleteReference = deleteReference;
}

DrawableManager::StorageListReference Drawable::getDeleteReference() const
{
	return _deleteReference;
}

void Drawable::setDeleteReference2D(const Drawable2DManager::StorageListReference& deleteReference2D)
{
	_deleteReference2D = deleteReference2D;
}

Drawable2DManager::StorageListReference Drawable::getDeleteReference2D() const
{
	return _deleteReference2D;
}

//-----------------------------------------------------------------------------------------------------------------------------
//  To be implemented by user in object derived from GameObject (NOT directly derived from Updatable)
//-----------------------------------------------------------------------------------------------------------------------------
void Drawable::draw()
{
	// Does nothing
}

void Drawable::draw2D()
{
	// Does nothing
}


//-----------------------------------------------------------------------------------------------------------------------------
// For personal debugging
//-----------------------------------------------------------------------------------------------------------------------------

const std::string Drawable::DEBUG_TITLE_MESSAGE = "Drawable_DEBUG: ";

void Drawable::DebugPrint(const std::string& message)
{
	(void(message));
#if Drawable_DEBUG
	if (message.size() == 0)
	{
		Trace::out("\n");
	}
	else
	{
		std::string finalMessage = Drawable::DEBUG_TITLE_MESSAGE + message + std::string("\n");
		Trace::out("%s", finalMessage.c_str());
	}
#endif // !Drawable_DEBUG
}
