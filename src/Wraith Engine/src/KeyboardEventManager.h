#ifndef _KeyboardEvenManager
#define _KeyboardEvenManager

#include <map>
#include "AzulCore.h"
#include "InputTypes.h"

class Inputable;
class SingleKeyEventManager;

class KeyboardEventManager
{
private:
	typedef std::map<AZUL_KEY, SingleKeyEventManager*> KeyEventMap;
	typedef std::pair<KeyEventMap::key_type, KeyEventMap::mapped_type> KeyEventPair;
public:
	typedef KeyEventMap::iterator StorageMapReference;
public:
	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator=(const KeyboardEventManager&) = delete;
	KeyboardEventManager(KeyboardEventManager&&) = delete;
	KeyboardEventManager& operator=(KeyboardEventManager&&) = delete;
	~KeyboardEventManager();

	/**********************************************************************************************//**
	 * <summary> Registers a inputable entity with key and key event to current scene.</summary>
	 *
	 * <remarks> Will internally call on a SingleKeyEventManager</remarks>
	 *
	 * <param name="pInputable"> the inputable entity.</param>
	 * <param name="key">		 The key.</param>
	 * <param name="eventType">  Type of the event.</param>
	 **************************************************************************************************/
	void registerEntityWithKeyAndKeyEvent(Inputable* pInputable, AZUL_KEY key, InputEvent eventType);

	/**********************************************************************************************//**
	 * <summary> Deregisters a inputable entity with key and key event.</summary>
	 *
	 * <remarks> Will internally call on a SingleKeyEventManager</remarks>
	 *
	 * <param name="pInputable"> the inputable entity.</param>
	 * <param name="key">		 The key.</param>
	 * <param name="eventType">  Type of the event.</param>
	 **************************************************************************************************/
	void deregisterEntityWithKeyAndKeyEvent(Inputable* pInputable, AZUL_KEY key, InputEvent eventType);
	
	// ---> Registration/Deregistration helper functions
	StorageMapReference tryToFind(AZUL_KEY);
	bool isIteratorValid(const KeyEventMap::iterator& iterator) const;

	/**********************************************************************************************//**
	 * <summary> Process the key events.</summary>
	 *
	 * <remarks> Called only by the current Scene in Scene::Update().</remarks>
	 **************************************************************************************************/
	void processKeyEvents();

	// ---> Manager Deletion helper
	void deleteAllSingleKeyEventManagers();
private:
	KeyEventMap _singleKeyEventMap;
};
#endif // !_KeyboardEvenManager

//-----------------------------------------------------------------------------------------------------------------------------
// KeyboardEventManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------