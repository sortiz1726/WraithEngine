#include "AlarmRegistrationCommand.h"
#include "AlarmableAttorney.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* pAlarmable, AlarmID alarmID)
	: _pAlarmable(pAlarmable),
	_alarmID(alarmID),
	_timeDelay(0.0f)
{
	assert(pAlarmable != nullptr);
}

void AlarmRegistrationCommand::setTimeDelay(const float timeDelay)
{
	assert(timeDelay >= 0.0f);
	_timeDelay = timeDelay;
}

void AlarmRegistrationCommand::execute()
{
	AlarmableAttorney::RegistrationAccess::RegisterAlarm(_pAlarmable, _alarmID, _timeDelay);
}
