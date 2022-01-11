#include "KeyboardEventManager.h"
#include "SingleKeyEventManager.h"
#include "InputableAttorney.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Manager Deletion
//-----------------------------------------------------------------------------------------------------------------------------
KeyboardEventManager::~KeyboardEventManager()
{
	deleteAllSingleKeyEventManagers();
}

// ---> Manager Deletion helper function
void KeyboardEventManager::deleteAllSingleKeyEventManagers()
{
	for (KeyEventPair pair : _singleKeyEventMap)
	{
		SingleKeyEventManager* pSingleKey = pair.second;
		delete pSingleKey;
	}
	_singleKeyEventMap.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Registration/Deregistration functions
//-----------------------------------------------------------------------------------------------------------------------------
void KeyboardEventManager::registerEntityWithKeyAndKeyEvent(Inputable* pInputable, AZUL_KEY key, InputEvent eventType)
{
	StorageMapReference mapReference = tryToFind(key);
	SingleKeyEventManager* pSingleKey = mapReference->second;
	InputableAttorney::FieldAccess::SetKeyboardDeleteRerefence(pInputable, mapReference, key, eventType);
	pSingleKey->registerEntity(pInputable, eventType);
}

void KeyboardEventManager::deregisterEntityWithKeyAndKeyEvent(Inputable* pInputable, AZUL_KEY key, InputEvent eventType)
{
	StorageMapReference mapReference = InputableAttorney::FieldAccess::GetKeyboardDeleteRerefence(pInputable, key, eventType);
	SingleKeyEventManager* pSingleKey = mapReference->second;
	pSingleKey->deregisterEntity(pInputable, eventType);
}

// ---> Registration/Deregistration helper functions
KeyboardEventManager::StorageMapReference KeyboardEventManager::tryToFind(AZUL_KEY key)
{
	StorageMapReference mapReference = _singleKeyEventMap.find(key);
	if (!isIteratorValid(mapReference))
	{
		SingleKeyEventManager* pSingleKey = new SingleKeyEventManager(key);
		mapReference = _singleKeyEventMap.insert(std::make_pair(key, pSingleKey)).first;
	}
	return mapReference;
}

bool KeyboardEventManager::isIteratorValid(const KeyEventMap::iterator& iterator) const
{
	return iterator != _singleKeyEventMap.end();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Proccess Key Event function
//-----------------------------------------------------------------------------------------------------------------------------
void KeyboardEventManager::processKeyEvents()
{
	for (KeyEventPair pair : _singleKeyEventMap)
	{
		SingleKeyEventManager* pSingleKey = pair.second;
		pSingleKey->processEntities();
	}
}
