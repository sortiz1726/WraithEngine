#include "AlarmableManager.h"
#include "TimeManager.h"
#include "Alarmable.h"
#include "AlarmableAttorney.h"

AlarmableManager::~AlarmableManager()
{
	_alarmTimeLineMap.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Register/Deregister Alarm functions
//-----------------------------------------------------------------------------------------------------------------------------
void AlarmableManager::registerAlarmWithDelayTime(Alarmable* pAlarmable, const float timeDelay, AlarmID alarmID)
{
	assert(pAlarmable != nullptr);
	Time triggerTime = TimeManager::GetTimeInSeconds() + timeDelay;
	AlarmEvent alarmEvent = AlarmEvent(pAlarmable, alarmID);

	TimeLineReference deleteReference = _alarmTimeLineMap.insert(std::make_pair(triggerTime, alarmEvent));
	AlarmableAttorney::FieldAccess::SetDeleteReference(pAlarmable, deleteReference, alarmID);
}

void AlarmableManager::deregisterAlarm(Alarmable* pAlarmable, AlarmID alarmID)
{
	assert(pAlarmable != nullptr);
	_alarmTimeLineMap.erase(AlarmableAttorney::FieldAccess::GetDeleteReference(pAlarmable, alarmID));
}

//-----------------------------------------------------------------------------------------------------------------------------
// Process Alarms functions
//-----------------------------------------------------------------------------------------------------------------------------
void AlarmableManager::processAlarms()
{
	//debugPrintTriggerAlarmsBanner();

	Time currentTime = TimeManager::GetTimeInSeconds();

	TimeLineReference currentAlarmIterator = _alarmTimeLineMap.begin();
	while (currentAlarmIterator != _alarmTimeLineMap.end() && getTriggerTime(currentAlarmIterator) <= currentTime)
	{
		triggerAndRemoveAlarm(currentAlarmIterator++);
	}

}

// Process Alarms helper functions
void AlarmableManager::debugPrintTriggerAlarmsBanner()
{
	if (!_alarmTimeLineMap.empty() && getTriggerTime(_alarmTimeLineMap.begin()) <= TimeManager::GetTimeInSeconds())
	{
		Trace::out("\n--------------------------------------------\n");
		Trace::out("Alarmable_DEBUG: %d possible alarm(s) to trigger\n", _alarmTimeLineMap.size());
	}
}

AlarmableManager::Time AlarmableManager::getTriggerTime(const TimeLineReference& currentAlarmIterator) const
{
	return currentAlarmIterator->first;
}

void AlarmableManager::triggerAndRemoveAlarm(const TimeLineReference& currentAlarmIterator)
{
	Alarmable* pAlarmable = currentAlarmIterator->second.first;
	AlarmID alarmID = currentAlarmIterator->second.second;
	AlarmableAttorney::AlarmAccess::TriggerAlarm(pAlarmable, alarmID);
	_alarmTimeLineMap.erase(currentAlarmIterator);
}
