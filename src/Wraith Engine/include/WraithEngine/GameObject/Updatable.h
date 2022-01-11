#ifndef _Updatable
#define _Updatable

#include "UpdatableManager.h"
#include "RegistrationStates.h"

class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

/**********************************************************************************************//**
 * <summary> Updatable control update callback and registration/deregistration. </summary>
 *	\ingroup UPDATABLE_INTERNALS
 * <remarks> </remarks>
 **************************************************************************************************/
class Updatable
{
	friend class UpdatableAttorney;
public:
	/**********************************************************************************************//**
	 * <summary> Default constructor.</summary>
	 *
	 * <remarks> Initializes its UpdateRegistrationCommand and UpdateDeregistrationCommand.
	 * 			 Also sets its RegistrationState to RegistrationState::CURRENTLY_DEREGISTERED. </remarks>
	 **************************************************************************************************/
	Updatable();
	Updatable(const Updatable&) = default;
	Updatable& operator=(const Updatable&) = default;
	Updatable(Updatable&&) = default;
	Updatable& operator=(Updatable&&) = default;
	virtual ~Updatable();

protected:
	//  Registration/Deregistration 

	/**********************************************************************************************//**
	 * <summary> Submit update registration to current scene.</summary>
	 * \ingroup UPDATE
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void submitUpdateRegistration();

	/**********************************************************************************************//**
	 * <summary> Submit update deregistration to current scene.</summary>
	 * \ingroup UPDATE
	 * <remarks> .</remarks>
	 **************************************************************************************************/
	void submitUpdateDeregistration();

	/**********************************************************************************************//**
	 * <summary> Query if this object is registered for update.</summary>
	 * \ingroup UPDATE
	 * <remarks> </remarks>
	 *
	 * <returns> True if registered for update, false if not.</returns>
	 **************************************************************************************************/
	bool isRegisteredForUpdate() const;

private:
	// Setter/Getters of Terminate Reference
	void setDeleteReference(const UpdatableManager::StorageListReference&);
	UpdatableManager::StorageListReference getDeleteReference() const;

	/**********************************************************************************************//**
	 * <summary> Registers to the current scene.</summary>
	 * \ingroup UPDATABLE_INTERNALS
	 * <remarks> DELAYED called with a command. NOT called by the user. </remarks>
	 **************************************************************************************************/
	void registerToScene();

	/**********************************************************************************************//**
	 * <summary> Deregisters from the current scene.</summary>
	 * \ingroup UPDATABLE_INTERNALS
	 * <remarks> DELAYED called with a command. NOT called by the user. </remarks>
	 **************************************************************************************************/
	void deregisterFromScene();

	/**********************************************************************************************//**
	 * <summary> Update callback for this object.</summary>
	 * \ingroup UPDATE
	 * 
	 * <remarks> To be implemented by user in object derived from GameObject (NOT directly derived from Updatable).
	 * 			 Called ONLY by current active scene.
	 * 			 </remarks>
	 **************************************************************************************************/
	virtual void update();

private:
	UpdatableManager::StorageListReference _deleteReference;

	UpdateRegistrationCommand* _pUpdateRegistrationCommand;
	UpdateDeregistrationCommand* _pUpdateDeregistrationCommand;

	RegistrationState _currentRegistrationState;

private:
	// For personal debugging
	static void DebugPrint(const std::string& message);
	static const std::string DEBUG_TITLE_MESSAGE;
};

// For personal debugging
#ifndef Updatable_DEBUG
#define Updatable_DEBUG false
#endif // !ModelManager_DEBUG

#endif // !_Updatable

//-----------------------------------------------------------------------------------------------------------------------------
//  UPDATABLE COMMENT TEMPLATE
//-----------------------------------------------------------------------------------------------------------------------------