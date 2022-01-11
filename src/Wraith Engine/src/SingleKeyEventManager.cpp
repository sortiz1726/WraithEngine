#include "SingleKeyEventManager.h"
#include "InputableAttorney.h"

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY key)
	: _key(key),
	_previousKeyState(getKeyState())
{}

SingleKeyEventManager::~SingleKeyEventManager()
{
	_registeredKeyPressEntites.clear();
	_registeredKeyReleaseEntites.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Registration/Deregistration functions
//-----------------------------------------------------------------------------------------------------------------------------
void SingleKeyEventManager::registerEntity(Inputable* pInputable, InputEvent eventType)
{
	StorageListReference deleteReference;
	switch (eventType)
	{
	case InputEvent::KEY_PRESS:
		deleteReference = _registeredKeyPressEntites.insert(_registeredKeyPressEntites.end(), pInputable);
		break;
	case InputEvent::KEY_RELEASE:
		deleteReference = _registeredKeyReleaseEntites.insert(_registeredKeyReleaseEntites.end(), pInputable);
		break;
	}
	InputableAttorney::FieldAccess::SetSingleKeyDeleteRerefence(pInputable, deleteReference, _key, eventType);
}

void SingleKeyEventManager::deregisterEntity(Inputable* pInputable, InputEvent eventType)
{
	StorageListReference deleteRefereence = InputableAttorney::FieldAccess::GetSingleKeyDeleteRerefence(pInputable, _key, eventType);
	switch (eventType)
	{
	case InputEvent::KEY_PRESS:
		_registeredKeyPressEntites.erase(deleteRefereence);
		break;
	case InputEvent::KEY_RELEASE:
		_registeredKeyReleaseEntites.erase(deleteRefereence);
		break;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Process Entities function
//-----------------------------------------------------------------------------------------------------------------------------
void SingleKeyEventManager::processEntities()
{
	KeyState _currentKeyState = getKeyState();
	if (isKeyPressed(_currentKeyState))
	{
		processKeyPressedEntities();
	}
	else if (isKeyReleased(_currentKeyState))
	{
		processKeyReleasedEntities();
	}
	_previousKeyState = _currentKeyState;
}

// ---> Process Entities helper functions
SingleKeyEventManager::KeyState SingleKeyEventManager::getKeyState() const
{
	return Keyboard::GetKeyState(_key) ? KeyState::KEY_DOWN : KeyState::KEY_UP;
}

bool SingleKeyEventManager::isKeyPressed(KeyState currentKeyState) const
{
	return (currentKeyState == KeyState::KEY_DOWN) && (_previousKeyState == KeyState::KEY_UP);
}

void SingleKeyEventManager::processKeyPressedEntities()
{
	for (Inputable* pInputable : _registeredKeyPressEntites)
	{
		InputableAttorney::InputAccess::KeyPressed(pInputable, _key);
	}
}

bool SingleKeyEventManager::isKeyReleased(KeyState currentKeyState) const
{
	return (currentKeyState == KeyState::KEY_UP) && (_previousKeyState == KeyState::KEY_DOWN);
}

void SingleKeyEventManager::processKeyReleasedEntities()
{
	for (Inputable* pInputable : _registeredKeyReleaseEntites)
	{
		InputableAttorney::InputAccess::KeyReleased(pInputable, _key);
	}
}