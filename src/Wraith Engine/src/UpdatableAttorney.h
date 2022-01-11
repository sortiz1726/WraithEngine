#ifndef _UpdatableAttorney
#define _UpdatableAttorney

#include "Updatable.h"

/**********************************************************************************************//**
 * <summary> A UpdatableAttorney giving access to certain Updatable functions
 * 			 to certain classes.</summary>
 *  \ingroup UPDATABLE_INTERNALS
 *
 * <remarks> NEVER called by the user. </remarks>
 **************************************************************************************************/
class UpdatableAttorney
{
private:
	UpdatableAttorney() = delete;
	UpdatableAttorney(const UpdatableAttorney&) = delete;
	UpdatableAttorney& operator=(const UpdatableAttorney&) = delete;
	UpdatableAttorney(UpdatableAttorney&&) = delete;
	UpdatableAttorney& operator=(UpdatableAttorney&&) = delete;
	~UpdatableAttorney() = delete;

public:

	/**********************************************************************************************//**
	 * <summary> Provides update access to Updatable functions.</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	class UpdateAccess
	{
		friend class UpdatableManager;

		/**********************************************************************************************//**
		 * <summary> update access of Updatable::update() callback. </summary>
		 *
		 * <remarks> ONLY UpdatableManager have access. </remarks>
		 *
		 * <param name="pUpdatable"> an Updatable pointer.</param>
		 **************************************************************************************************/
		static void Update(Updatable* pUpdatable) { pUpdatable->update(); }
	};

	/**********************************************************************************************//**
	* <summary> Provides registration access to Updatable functions.</summary>
	*
	* <remarks> </remarks>
	**************************************************************************************************/
	class RegistrationAccess
	{
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;

		/**********************************************************************************************//**
		* <summary> Registration access for connecting to the scene. </summary>
		*
		* <remarks> ONLY UpdateRegistrationCommand and UpdateDeregistrationCommand have access. </remarks>
		*
		* <param name="pUpdatable"> an Updatable pointer.</param>
		**************************************************************************************************/
		static void RegisterToScene(Updatable* pUpdatable) { pUpdatable->registerToScene(); }

		/**********************************************************************************************//**
		* <summary> Registration access for connecting to the scene. </summary>
		*
		* <remarks> ONLY UpdateRegistrationCommand and UpdateDeregistrationCommand have access. </remarks>
		*
		* <param name="pUpdatable"> an Updatable pointer.</param>
		**************************************************************************************************/
		static void DeregisterFromScene(Updatable* pUpdatable) { pUpdatable->deregisterFromScene(); }
	};


	/**********************************************************************************************//**
	* <summary> Provides field access to Updatable.</summary>
	*
	* <remarks> </remarks>
	**************************************************************************************************/
	class FieldAccess
	{
		friend class UpdatableManager;

		/**********************************************************************************************//**
		 * <summary> Sets delete reference.</summary>
		 *
		 * <remarks> ONLY UpdatableManager have access. </remarks>
		 *
		 * <param name="pUpdatable"> an Updatable pointer.</param>
		 * <param name="deleteReference"> The delete reference.</param>
		 **************************************************************************************************/
		static void SetDeleteReference(Updatable* pUpdatable, const UpdatableManager::StorageListReference& deleteReference)
		{
			pUpdatable->setDeleteReference(deleteReference);
		}

		/**********************************************************************************************//**
		 * <summary> Gets delete reference.</summary>
		 *
		 * <remarks> ONLY UpdatableManager have access.</remarks>
		 *
		 * <param name="pUpdatable"> an Updatable pointer. </param>
		 *
		 * <returns> The delete reference.</returns>
		 **************************************************************************************************/
		static UpdatableManager::StorageListReference GetDeleteReference(Updatable* pUpdatable)
		{
			return pUpdatable->getDeleteReference();
		}
	};

};
#endif // !_UpdatableAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// UpdatableAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------