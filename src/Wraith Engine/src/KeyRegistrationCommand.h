#ifndef _KeyRegistrationCommand
#define _KeyRegistrationCommand

#include "AzulCore.h"
#include "SceneRegistrationCommand.h"
#include "InputTypes.h"

class Inputable;

class KeyRegistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	KeyRegistrationCommand() = delete;
	KeyRegistrationCommand(const KeyRegistrationCommand&) = default;
	KeyRegistrationCommand& operator=(const KeyRegistrationCommand&) = default;
	KeyRegistrationCommand(KeyRegistrationCommand&&) = default;
	KeyRegistrationCommand& operator=(KeyRegistrationCommand&&) = default;
	~KeyRegistrationCommand() = default;

	KeyRegistrationCommand(Inputable*, AZUL_KEY, InputEvent);

	// Inherited via SceneRegistrationCommand
	virtual void execute() override;

private:
	Inputable* _pInputable;
	AZUL_KEY _key;
	InputEvent _eventType;
};
#endif // !_KeyRegistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// KeyRegistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------