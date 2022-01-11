#ifndef _AlarmRegistrationCommand
#define _AlarmRegistrationCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmRegistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	AlarmRegistrationCommand() = delete;
	AlarmRegistrationCommand(const AlarmRegistrationCommand&) = default;
	AlarmRegistrationCommand& operator=(const AlarmRegistrationCommand&) = default;
	AlarmRegistrationCommand(AlarmRegistrationCommand&&) = default;
	AlarmRegistrationCommand& operator=(AlarmRegistrationCommand&&) = default;
	~AlarmRegistrationCommand() = default;

	AlarmRegistrationCommand(Alarmable*, AlarmID);

	void setTimeDelay(const float timeDelay);

	// Inherited via SceneRegistrationCommand
	virtual void execute() override;

private:
	Alarmable* _pAlarmable;
	AlarmID _alarmID;
	float _timeDelay;
};
#endif // !_AlarmRegistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// AlarmRegistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------