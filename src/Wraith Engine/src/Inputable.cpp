#include "Inputable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "KeyRegistrationCommand.h"
#include "KeyDeregistrationCommand.h"

Inputable::Inputable()
{}

Inputable::~Inputable()
{
	Inputable::DebugPrint("Destructor Called");
	deinitializeRegistrationData();
}

void Inputable::deinitializeRegistrationData()
{
	for (MapPair pair : _registeredInputKeys)
	{
		RegistrationData& data = pair.second;
		delete data._pKeyRegistrationCommand;
		delete data._pKeyDeregistrationCommand;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Registration/Deregistration functions
//-----------------------------------------------------------------------------------------------------------------------------
void Inputable::submitKeyRegistration(AZUL_KEY key, InputEvent eventType)
{
	RegistrationData& data = getRegistrationDataReference(key, eventType);

	assert(data._currentRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), data._pKeyRegistrationCommand);
	data._currentRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void Inputable::registerKey(AZUL_KEY key, InputEvent eventType)
{
	RegistrationData& data = getRegistrationDataReference(key, eventType);

	assert(data._currentRegistrationState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::RegistrationAccess::RegisterEntity(SceneManager::GetCurrentScene(), this, key, eventType);
	data._currentRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::submitKeyDeregistration(AZUL_KEY key, InputEvent eventType)
{
	RegistrationData& data = getRegistrationDataReference(key, eventType);

	assert(data._currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), data._pKeyDeregistrationCommand);
	data._currentRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}

bool Inputable::isRegisterForKeyWithEvent(AZUL_KEY key, InputEvent eventType)
{
	return getRegistrationData(key, eventType)._currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::deregisterKey(AZUL_KEY key, InputEvent eventType)
{
	RegistrationData& data = getRegistrationDataReference(key, eventType);

	assert(data._currentRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::RegistrationAccess::DeregisterEntity(SceneManager::GetCurrentScene(), this, key, eventType);
	data._currentRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setter/Getter Terminate Reference
//-----------------------------------------------------------------------------------------------------------------------------
void Inputable::setKeyboardDeleteReference(const KeyboardEventManager::StorageMapReference& keyboardReference, AZUL_KEY key, InputEvent eventType)
{
	RegistrationData& data = getRegistrationDataReference(key, eventType);
	data._keyboardDeleteReference = keyboardReference;
}

KeyboardEventManager::StorageMapReference Inputable::getKeyboardDeleteReference(AZUL_KEY key, InputEvent eventType)
{
	RegistrationData& data = getRegistrationDataReference(key, eventType);
	return data._keyboardDeleteReference;
}

void Inputable::setSingleKeyDeleteReference(const SingleKeyEventManager::StorageListReference& singleKeyReference, AZUL_KEY key, InputEvent eventType)
{
	RegistrationData& data = getRegistrationDataReference(key, eventType);
	data._singleKeyDeleteReference = singleKeyReference;
}

SingleKeyEventManager::StorageListReference Inputable::getSingleKeyDeleteReference(AZUL_KEY key, InputEvent eventType)
{
	RegistrationData& data = getRegistrationDataReference(key, eventType);
	return data._singleKeyDeleteReference;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Get Registration Data functions
//-----------------------------------------------------------------------------------------------------------------------------
Inputable::RegistrationData Inputable::getRegistrationData(AZUL_KEY key, InputEvent eventType)
{
	InputDataMap::iterator iterator = tryToFind(key, eventType);
	return iterator->second;
}

Inputable::RegistrationData& Inputable::getRegistrationDataReference(AZUL_KEY key, InputEvent eventType)
{
	InputDataMap::iterator iterator = tryToFind(key, eventType);
	RegistrationData& data = iterator->second;
	return data;
}

// ---> Get Registration Data helper functions
Inputable::InputDataMap::iterator Inputable::tryToFind(AZUL_KEY key, InputEvent eventType)
{
	InputDataMap::iterator iterator = _registeredInputKeys.find(std::make_pair(key, eventType));
	if (isIteratorValid(iterator))
	{
		return iterator;
	}
	else
	{
		RegistrationData data = createRegistrationData(key, eventType);
		iterator = _registeredInputKeys.insert(std::make_pair(KeyEventPair(key, eventType), data)).first;
		return iterator;
	}
}

bool Inputable::isIteratorValid(const InputDataMap::iterator& iterator) const
{
	return iterator != _registeredInputKeys.end();
}

Inputable::RegistrationData Inputable::createRegistrationData(AZUL_KEY key, InputEvent eventType)
{
	RegistrationData data;
	data._pKeyRegistrationCommand = new KeyRegistrationCommand(this, key, eventType);
	data._pKeyDeregistrationCommand = new KeyDeregistrationCommand(this, key, eventType);
	data._currentRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
	return data;
}

//-----------------------------------------------------------------------------------------------------------------------------
// To be implemented by user in object derived from GameObject (NOT directly derived from Inputable)
//-----------------------------------------------------------------------------------------------------------------------------
void Inputable::keyPressed(AZUL_KEY)
{
	// Does nothing
}

void Inputable::keyReleased(AZUL_KEY)
{
	// Does nothing
}


//-----------------------------------------------------------------------------------------------------------------------------
// For personal debugging
//-----------------------------------------------------------------------------------------------------------------------------
static const std::string DEBUG_TITLE_MESSAGE = "Inputable_DEBUG: ";

void Inputable::DebugPrint(const std::string& message)
{
	(void(message));
#if Inputable_DEBUG
	if (message.size() == 0)
	{
		Trace::out("\n");
	}
	else
	{
		std::string finalMessage = Inputabel::DEBUG_TITLE_MESSAGE + message + std::string("\n");
		Trace::out("%s", finalMessage.c_str());
	}
#endif // !Inputable_DEBUG
}