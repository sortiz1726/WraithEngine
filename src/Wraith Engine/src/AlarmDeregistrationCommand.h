#ifndef _AlarmDeregistrationCommand
#define _AlarmDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	AlarmDeregistrationCommand() = delete;
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand&) = default;
	AlarmDeregistrationCommand& operator=(const AlarmDeregistrationCommand&) = default;
	AlarmDeregistrationCommand(AlarmDeregistrationCommand&&) = default;
	AlarmDeregistrationCommand& operator=(AlarmDeregistrationCommand&&) = default;
	~AlarmDeregistrationCommand() = default;

	AlarmDeregistrationCommand(Alarmable*, AlarmID);

	// Inherited via SceneRegistrationCommand
	virtual void execute() override;

private:
	Alarmable* _pAlarmable;
	AlarmID _alarmID;
};
#endif // !_AlarmDeregistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// AlarmDeregistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------