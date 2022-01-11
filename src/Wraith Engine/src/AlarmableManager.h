#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>
#include "AlarmIDs.h"

class Alarmable;

class AlarmableManager
{
	typedef float Time;
	typedef std::pair<Alarmable*, AlarmID> AlarmEvent;
	typedef std::multimap<Time, AlarmEvent> TimeLine;

public:
	typedef TimeLine::iterator TimeLineReference;

public:
	AlarmableManager() = default;
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator=(const AlarmableManager&) = delete;
	AlarmableManager(AlarmableManager&&) = delete;
	AlarmableManager& operator=(AlarmableManager&&) = delete;
	~AlarmableManager();

	/**********************************************************************************************//**
	 * <summary> Registers an Alarmable entity for an alarm with delay time</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pAlarmable"> a alarmable entity.</param>
	 * <param name="timeDelay">  The time delay.</param>
	 * <param name="alarmID">    Identifier for the alarm.</param>
	 **************************************************************************************************/
	void registerAlarmWithDelayTime(Alarmable* pAlarmable, const float timeDelay, AlarmID alarmID);

	/**********************************************************************************************//**
	 * <summary> Deregisters an Alarmable entity for an alarm</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pAlarmable"> the alarmable entity.</param>
	 * <param name="alarmID">    Identifier for the alarm.</param>
	 **************************************************************************************************/
	void deregisterAlarm(Alarmable* pAlarmable, AlarmID alarmID);

	/**********************************************************************************************//**
	 * <summary> Process the registered alarms.</summary>
	 *
	 * <remarks> Called only by the current Scene in Scene::Update(). </remarks>
	 **************************************************************************************************/
	void processAlarms();

	// ---> Process Alarms helpers 
	Time getTriggerTime(const TimeLineReference& currentAlarmIterator) const;
	void triggerAndRemoveAlarm(const TimeLineReference& currentAlarmIterator);

private:
	void debugPrintTriggerAlarmsBanner();

public:
	static const int MAX_NUMBER_OF_ALARMS = 3;

private:
	TimeLine _alarmTimeLineMap;
};
#endif // !_AlarmableManager

//-----------------------------------------------------------------------------------------------------------------------------
// AlarmableManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------