#ifndef _Inputable
#define _Inputable

#include <map>
#include "AzulCore.h"
#include "InputTypes.h"
#include "RegistrationStates.h"
#include "KeyboardEventManager.h"
#include "SingleKeyEventManager.h"

class KeyRegistrationCommand;
class KeyDeregistrationCommand;

class Inputable
{
	friend class InputableAttorney;
private:

	/**********************************************************************************************//**
	 * <summary> A registration data.</summary>
	 *
	 * <remarks> holds information for delete reference, registration/deregistration commands,
	 * 			 and current registration state for each KeyEventPair. </remarks>
	 **************************************************************************************************/
	struct RegistrationData
	{
		KeyboardEventManager::StorageMapReference _keyboardDeleteReference;

		SingleKeyEventManager::StorageListReference _singleKeyDeleteReference;
		KeyRegistrationCommand* _pKeyRegistrationCommand;
		KeyDeregistrationCommand* _pKeyDeregistrationCommand;
		RegistrationState _currentRegistrationState;
	};

	typedef std::pair<AZUL_KEY, InputEvent> KeyEventPair;
	typedef std::map<KeyEventPair, RegistrationData> InputDataMap;
	
	typedef std::pair<InputDataMap::key_type, InputDataMap::mapped_type> MapPair;

public:
	Inputable();
	Inputable(const Inputable&) = default;
	Inputable& operator=(const Inputable&) = default;
	Inputable(Inputable&&) = default;
	Inputable& operator=(Inputable&&) = default;
	virtual ~Inputable();

protected:
	// Registration/Deregistration

	/**********************************************************************************************//**
	 * <summary> Submit key registration to current scene.</summary>
	 * \ingroup INPUTS
	 * <remarks> </remarks>
	 *
	 * <param name="key">	    The key.</param>
	 * <param name="eventType"> Type of the event.</param>
	 **************************************************************************************************/
	void submitKeyRegistration(AZUL_KEY key, InputEvent eventType);

	/**********************************************************************************************//**
	 * <summary> Submit key deregistration to current scene.</summary>
	 * \ingroup INPUTS
	 * <remarks> </remarks>
	 *
	 * <param name="key">	   The key.</param>
	 * <param name="eventType"> The event typ.</param>
	 **************************************************************************************************/
	void submitKeyDeregistration(AZUL_KEY key, InputEvent eventType);

	/**********************************************************************************************//**
	 * <summary> Query if 'key' is register for key with event.</summary>
	 * \ingroup INPUTS
	 * <remarks> </remarks>
	 *
	 * <param name="key">	    The key.</param>
	 * <param name="eventType"> Type of the event.</param>
	 *
	 * <returns> True if register for key with event, false if not.</returns>
	 **************************************************************************************************/
	bool isRegisterForKeyWithEvent(AZUL_KEY key, InputEvent eventType);

private:

	/**********************************************************************************************//**
	 * <summary> //Registers a key with a event type to the current scene.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="key">	    The key.</param>
	 * <param name="eventType"> Type of the event.</param>
	 **************************************************************************************************/
	void registerKey(AZUL_KEY key, InputEvent eventType);

	/**********************************************************************************************//**
	 * <summary> Deregisters a key with a event type from the current scene.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="key">	    The key.</param>
	 * <param name="eventType"> Type of the event.</param>
	 **************************************************************************************************/
	void deregisterKey(AZUL_KEY key, InputEvent eventType);
	
	// Setter/Getter Terminate Reference
	void setKeyboardDeleteReference(const KeyboardEventManager::StorageMapReference&, AZUL_KEY, InputEvent);
	KeyboardEventManager::StorageMapReference getKeyboardDeleteReference(AZUL_KEY, InputEvent);

	void setSingleKeyDeleteReference(const SingleKeyEventManager::StorageListReference&, AZUL_KEY, InputEvent);
	SingleKeyEventManager::StorageListReference getSingleKeyDeleteReference(AZUL_KEY, InputEvent);

	// Get Registration Data functions
	RegistrationData getRegistrationData(AZUL_KEY, InputEvent);
	RegistrationData& getRegistrationDataReference(AZUL_KEY, InputEvent);

	//	---> Get Registration Data helper functions
	InputDataMap::iterator tryToFind(AZUL_KEY, InputEvent);
	bool isIteratorValid(const InputDataMap::iterator&) const;
	RegistrationData createRegistrationData(AZUL_KEY, InputEvent);

	/**********************************************************************************************//**
	 * <summary> Key pressed callback.</summary>
	 * \ingroup INPUTS
	 * <remarks> To be implemented by user in object derived from GameObject (NOT directly derived from Inputable)
	 * 			 </remarks>
	 *
	 * <param name="key"> The key.</param>
	 **************************************************************************************************/
	virtual void keyPressed(AZUL_KEY key);

	/**********************************************************************************************//**
	 * <summary> Key released callback.</summary>
	 * \ingroup INPUTS
	 * <remarks> To be implemented by user in object derived from GameObject (NOT directly derived from Inputable)
	 * 			 </remarks>
	 *
	 * <param name="key"> The key.</param>
	 **************************************************************************************************/
	virtual void keyReleased(AZUL_KEY key);

	void deinitializeRegistrationData();
private:
	InputDataMap _registeredInputKeys;

private:
	// For personal debugging
	static const std::string DEBUG_TITLE_MESSAGE;
	static void DebugPrint(const std::string& message);
};

// For personal debugging
#ifndef Inputable_DEBUG
#define Inputable_DEBUG false
#endif // !Alarmable_DEBUG

#endif // !_Inputable

//-----------------------------------------------------------------------------------------------------------------------------
// Inputable Comment Template
//-----------------------------------------------------------------------------------------------------------------------------