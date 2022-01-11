#ifndef _AlarmableAttorney
#define _AlarmableAttorney

#include "Alarmable.h"

class AlarmableAttorney
{
private:
	AlarmableAttorney() = delete;
	AlarmableAttorney(const AlarmableAttorney&) = delete;
	AlarmableAttorney& operator=(const AlarmableAttorney&) = delete;
	AlarmableAttorney(AlarmableAttorney&&) = delete;
	AlarmableAttorney& operator=(AlarmableAttorney&&) = delete;
	~AlarmableAttorney() = delete;

public:
	class AlarmAccess
	{
		friend class AlarmableManager;

		static void TriggerAlarm(Alarmable* pAlarmable, AlarmID alarmID) { pAlarmable->triggerAlarm(alarmID); }
	};

	class RegistrationAccess
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;

		static void RegisterAlarm(Alarmable* pAlarmable, AlarmID alarmID, float timeDelay) { pAlarmable->registerAlarm(timeDelay, alarmID); }
		static void DeregisterAlarm(Alarmable* pAlarmable, AlarmID alarmID) { pAlarmable->deregisterAlarm(alarmID); }
	};

	class FieldAccess
	{
		friend class AlarmableManager;

		static void SetDeleteReference(Alarmable* pAlarmable, const AlarmableManager::TimeLineReference& deleteReference, AlarmID alarmID)
		{
			pAlarmable->setDeleteReference(deleteReference, alarmID);
		}

		static AlarmableManager::TimeLineReference GetDeleteReference(Alarmable* pAlarmable, AlarmID alarmID)
		{
			return pAlarmable->getDeleteReference(alarmID);
		}
	};

};
#endif // !_AlarmableAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// AlarmableAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------