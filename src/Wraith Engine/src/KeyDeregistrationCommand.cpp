#include "KeyDeregistrationCommand.h"
#include "InputableAttorney.h"

KeyDeregistrationCommand::KeyDeregistrationCommand(Inputable* pInputable, AZUL_KEY key, InputEvent eventType)
	: _pInputable(pInputable),
	_key(key),
	_eventType(eventType)
{
	assert(_pInputable != nullptr);
}

void KeyDeregistrationCommand::execute()
{
	InputableAttorney::RegistrationAccess::DeregisterKey(_pInputable, _key, _eventType);
}
