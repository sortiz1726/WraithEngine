#include "KeyRegistrationCommand.h"
#include "InputableAttorney.h"

KeyRegistrationCommand::KeyRegistrationCommand(Inputable* pInputable, AZUL_KEY key, InputEvent eventType)
	: _pInputable(pInputable),
	_key(key),
	_eventType(eventType)
{
	assert(pInputable != nullptr);
}

void KeyRegistrationCommand::execute()
{
	InputableAttorney::RegistrationAccess::RegisterKey(_pInputable, _key, _eventType);
}
