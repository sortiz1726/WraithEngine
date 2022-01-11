#include "UpdateRegistrationCommand.h"
#include "UpdatableAttorney.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updatable* pUpdatable)
	: _pUpdatable(pUpdatable)
{
	assert(_pUpdatable != nullptr);
}

void UpdateRegistrationCommand::execute()
{
	UpdatableAttorney::RegistrationAccess::RegisterToScene(_pUpdatable);
}
