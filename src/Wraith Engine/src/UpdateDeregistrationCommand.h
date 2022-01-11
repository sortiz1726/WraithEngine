#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand

#include "SceneRegistrationCommand.h"

class Updatable;

/**********************************************************************************************//**
 * <summary> A update deregistration command.</summary>
 * \ingroup UPDATABLE_INTERNALS
 * <remarks> Responsible for calling on Updatable::deregisterFromScene(). </remarks>
 **************************************************************************************************/
class UpdateDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	UpdateDeregistrationCommand() = delete;
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand&) = default;
	UpdateDeregistrationCommand& operator=(const UpdateDeregistrationCommand&) = default;
	UpdateDeregistrationCommand(UpdateDeregistrationCommand&&) = default;
	UpdateDeregistrationCommand& operator=(UpdateDeregistrationCommand&&) = default;
	~UpdateDeregistrationCommand() = default;


	/**********************************************************************************************//**
	* <summary> Constructor getting a pointer to a Updatable.</summary>
	*
	* <remarks> Initialzed ONLY by Updatable::Updatable(). </remarks>
	*
	* <param name="pUpdatable"> an Updatable pointer.</param>
	**************************************************************************************************/
	UpdateDeregistrationCommand(Updatable* pUpdatable);

	// Inherited via SceneRegistrationCommand
	
	/**********************************************************************************************//**
	 * <summary> Calls on Updatable::registerFromScene() to its current Updatable pointer.</summary>
	 *
	 * <remarks> Called ONLY by SceneRegistrationBroker::executeCommands(). </remarks>
	 **************************************************************************************************/
	virtual void execute() override;

private:
	Updatable* _pUpdatable;
};
#endif // !_UpdateDeregistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// UpdateDeregistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------