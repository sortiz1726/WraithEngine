#include "AlarmDeregistrationCommand.h"
#include "AlarmableAttorney.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* pAlarmable, AlarmID alarmID)
	: _pAlarmable(pAlarmable),
	_alarmID(alarmID)
{
	assert(_pAlarmable != nullptr);
}

void AlarmDeregistrationCommand::execute()
{
	AlarmableAttorney::RegistrationAccess::DeregisterAlarm(_pAlarmable, _alarmID);
}
