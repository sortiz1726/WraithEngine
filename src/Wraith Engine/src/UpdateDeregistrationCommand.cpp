#include "UpdateDeregistrationCommand.h"
#include "UpdatableAttorney.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updatable* pUpdatable)
	: _pUpdatable(pUpdatable)
{
	assert(_pUpdatable != nullptr);
}

void UpdateDeregistrationCommand::execute()
{
	UpdatableAttorney::RegistrationAccess::DeregisterFromScene(_pUpdatable);
}
