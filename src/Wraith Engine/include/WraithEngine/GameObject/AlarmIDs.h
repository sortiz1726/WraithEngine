#ifndef _AlarmID
#define _AlarmID

/**********************************************************************************************//**
 * <summary> Values that represent alarm Identifiers.</summary>
 *	\ingroup ALARMS
 * <remarks> To be used in GameObject::submitAlarmRegistration() 
 * 			 and GameObject::submitAlarmDeregistration() </remarks>
 **************************************************************************************************/
enum class AlarmID
{
	ALARM_0, 
	ALARM_1, 
	ALARM_2
};

#endif // !_AlarmID