#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include <list>
#include "AzulCore.h"
#include "InputTypes.h"

class Inputable;

/**********************************************************************************************//**
 * <summary> Manager for single key events.</summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class SingleKeyEventManager
{
private:

	/**********************************************************************************************//**
	 * <summary> Values that represent key states.</summary>
	 *
	 * <remarks> Used internally by the SingleKeyEventManager.</remarks>
	 **************************************************************************************************/
	enum class KeyState
	{
		KEY_DOWN,
		KEY_UP
	};
	typedef std::list<Inputable*> StorageList;
public:
	typedef StorageList::iterator StorageListReference;

public:
	SingleKeyEventManager() = delete;
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator=(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager(SingleKeyEventManager&&) = delete;
	SingleKeyEventManager& operator=(SingleKeyEventManager&&) = delete;
	~SingleKeyEventManager();

	/**********************************************************************************************//**
	 * <summary> Constructor.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="key"> The key.</param>
	 **************************************************************************************************/
	SingleKeyEventManager(AZUL_KEY key);

	/**********************************************************************************************//**
	 * <summary> Registers the entity.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pInputable"> the inputable.</param>
	 * <param name="eventType">  Type of the event.</param>
	 **************************************************************************************************/
	void registerEntity(Inputable* pInputable, InputEvent eventType);

	/**********************************************************************************************//**
	 * <summary> Deregisters the entity.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pInputable"> the inputable.</param>
	 * <param name="eventType">  Type of the event.</param>
	 **************************************************************************************************/
	void deregisterEntity(Inputable* pInputable, InputEvent eventType);

	/**********************************************************************************************//**
	 * <summary> Process the entities.</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void processEntities();

private:
	// ---> Process Entities helper functions

	/**********************************************************************************************//**
	 * <summary> Gets key state.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> The key state.</returns>
	 **************************************************************************************************/
	KeyState getKeyState() const;

	/**********************************************************************************************//**
	 * <summary> Query if 'keyState' is key pressed.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="keyState"> State of the key.</param>
	 *
	 * <returns> True if key pressed, false if not.</returns>
	 **************************************************************************************************/
	bool isKeyPressed(KeyState keyState) const;

	/**********************************************************************************************//**
	 * <summary> Query if 'keyState' is key released.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="keyState"> State of the key.</param>
	 *
	 * <returns> True if key released, false if not.</returns>
	 **************************************************************************************************/
	bool isKeyReleased(KeyState keyState) const;

	/**********************************************************************************************//**
	 * <summary> Process the key pressed entities.</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void processKeyPressedEntities();

	/**********************************************************************************************//**
	 * <summary> Process the key released entities.</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void processKeyReleasedEntities();

private:
	AZUL_KEY _key;
	StorageList _registeredKeyPressEntites;
	StorageList _registeredKeyReleaseEntites;

	// Internal Property
	KeyState _previousKeyState;

};
#endif // !_SingleKeyEventManager

//-----------------------------------------------------------------------------------------------------------------------------
// SingleKeyEventManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------