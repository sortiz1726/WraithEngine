#ifndef _KeyDeregistrationCommand
#define _KeyDeregistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
#include "InputTypes.h"

class Inputable;

class KeyDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	KeyDeregistrationCommand() = delete;
	KeyDeregistrationCommand(const KeyDeregistrationCommand&) = default;
	KeyDeregistrationCommand& operator=(const KeyDeregistrationCommand&) = default;
	KeyDeregistrationCommand(KeyDeregistrationCommand&&) = default;
	KeyDeregistrationCommand& operator=(KeyDeregistrationCommand&&) = default;
	~KeyDeregistrationCommand() = default;

	KeyDeregistrationCommand(Inputable*, AZUL_KEY, InputEvent);

	// Inherited via SceneRegistrationCommand
	virtual void execute() override;

private:
	Inputable* _pInputable;
	AZUL_KEY _key;
	InputEvent _eventType;
};
#endif // !_KeyDeregistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// KeyDeregistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------