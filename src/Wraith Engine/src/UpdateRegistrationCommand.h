#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand

#include "SceneRegistrationCommand.h"

class Updatable;

/**********************************************************************************************//**
 * <summary> A update registration command.</summary>
 * \ingroup UPDATABLE_INTERNALS
 * <remarks> Responsible for calling on Updatable::registerToScene(). </remarks>
 **************************************************************************************************/
class UpdateRegistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	UpdateRegistrationCommand() = delete;
	UpdateRegistrationCommand(const UpdateRegistrationCommand&) = default;
	UpdateRegistrationCommand& operator=(const UpdateRegistrationCommand&) = default;
	UpdateRegistrationCommand(UpdateRegistrationCommand&&) = default;
	UpdateRegistrationCommand& operator=(UpdateRegistrationCommand&&) = default;
	~UpdateRegistrationCommand() = default;

	/**********************************************************************************************//**
	* <summary> Constructor getting a pointer to a Updatable.</summary>
	*
	* <remarks> Initialzed ONLY by Updatable::Updatable(). </remarks>
	*
	* <param name="pUpdatable"> an Updatable pointer.</param>
	**************************************************************************************************/
	UpdateRegistrationCommand(Updatable* pUpdatable);

	// Inherited via SceneRegistrationCommand

	/**********************************************************************************************//**
	 * <summary> Calls on Updatable::registerToScene() to its current Updatable pointer.</summary>
	 *
	 * <remarks> Called ONLY by SceneRegistrationBroker::executeCommands(). </remarks>
	 **************************************************************************************************/
	virtual void execute() override;

private:
	Updatable* _pUpdatable;
};
#endif // !_UpdateRegistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// UpdateRegistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------