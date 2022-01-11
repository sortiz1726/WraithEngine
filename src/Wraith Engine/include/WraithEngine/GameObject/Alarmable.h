#ifndef _Alarmable
#define _Alarmable

#include "AlarmableManager.h"
#include "AlarmIDs.h"
#include "RegistrationStates.h"

class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class Alarmable
{
	friend class AlarmableAttorney;
private:

	/**********************************************************************************************//**
	 * <summary> A registration data.</summary>
	 *
	 * <remarks> holds information for delete reference, registration/deregistration commands,
	 * 			 and current registration state for each alarm. </remarks>
	 **************************************************************************************************/
	struct RegistrationData
	{
		AlarmableManager::TimeLineReference _deleteReference;
		AlarmRegistrationCommand* _pAlarmRegistrationCommand;
		AlarmDeregistrationCommand* _pAlarmDeregistrationCommand;
		RegistrationState _currentRegistrationState;
	};

public:
	// Big Six
	Alarmable();
	Alarmable(const Alarmable&) = default;
	Alarmable& operator=(const Alarmable&) = default;
	Alarmable(Alarmable&&) = default;
	Alarmable& operator=(Alarmable&&) = default;
	virtual ~Alarmable();

protected:
	/**********************************************************************************************//**
	 * <summary> Submit alarm registration to the current scene.</summary>
	 * \ingroup ALARMS
	 * <remarks> </remarks>
	 *
	 * <param name="timeDelay"> The time delay.</param>
	 * <param name="alarmID">   Identifier for the alarm.</param>
	 **************************************************************************************************/
	void submitAlarmRegistration(float timeDelay, AlarmID alarmID);

	/**********************************************************************************************//**
	 * <summary> Submit alarm deregistration to the current scene.</summary>
	 * \ingroup ALARMS
	 * <remarks> </remarks>
	 *
	 * <param name="alarmID"> Identifier for the alarm.</param>
	 **************************************************************************************************/
	void submitAlarmDeregistration(AlarmID alarmID);

	/**********************************************************************************************//**
	 * <summary> Query if 'alarmID' is registered.</summary>
	 * \ingroup ALARMS
	 * <remarks> </remarks>
	 *
	 * <param name="alarmID"> Identifier for the alarm.</param>
	 *
	 * <returns> True if registered for alarm, false if not.</returns>
	 **************************************************************************************************/
	bool isRegisteredForAlarm(AlarmID alarmID) const;

	/**********************************************************************************************//**
	 * <summary> Gets time left for a given alarm.</summary>
	 *	\ingroup ALARMS
	 * <remarks> Used only if alarm is registered. 
	 * 			 Check using GameObject::isRegisteredForAlarm() before calling this function </remarks>
	 *
	 * <param name="alarmID"> Identifier for the alarm.</param>
	 *
	 * <returns> The time left for a given alarm.</returns>
	 **************************************************************************************************/
	float getTimeLeftForAlarm(AlarmID alarmID) const;

private:

	/**********************************************************************************************//**
	 * <summary> Registers a alarm to the current scene.</summary>
	 *
	 * <remarks> DELAYED called with a command. NOT called by the user. </remarks>
	 *
	 * <param name="timeDelay"> The time delay.</param>
	 * <param name="alarmID">   Identifier for the alarm.</param>
	 **************************************************************************************************/
	void registerAlarm(float timeDelay, AlarmID alarmID);

	/**********************************************************************************************//**
	 * <summary> Deregisters a alarm from the current scene.</summary>
	 *
	 * <remarks> DELAYED called with a command. NOT called by the user. </remarks>
	 *
	 * <param name="alarmID"> Identifier for the alarm.</param>
	 **************************************************************************************************/
	void deregisterAlarm(AlarmID alarmID);

	/**********************************************************************************************//**
	 * <summary> Trigger a alarm. Used only by the AlarmableManager</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="alarmID"> Identifier for the alarm.</param>
	 **************************************************************************************************/
	void triggerAlarm(AlarmID alarmID);

	/**********************************************************************************************//**
	 * <summary> Alarm 0.</summary>
	 * \ingroup ALARMS
	 * <remarks> To be implemented by user in object derived from GameObject (NOT directly derived from Alarmable).
	 * 			 </remarks>
	 **************************************************************************************************/
	virtual void alarm0();

	/**********************************************************************************************//**
	 * <summary> Alarm 1.</summary>
	 * \ingroup ALARMS
	 * <remarks> To be implemented by user in object derived from GameObject (NOT directly derived from Alarmable)
	 * 			 </remarks>
	 **************************************************************************************************/
	virtual void alarm1();

	/**********************************************************************************************//**
	 * <summary> Alarm 2.</summary>
	 * \ingroup ALARMS
	 * <remarks> To be implemented by user in object derived from GameObject (NOT directly derived from Alarmable)
	 *			 </remarks>
	 **************************************************************************************************/
	virtual void alarm2();

	// Setters/Getters
	void setDeleteReference(const AlarmableManager::TimeLineReference&, AlarmID);
	AlarmableManager::TimeLineReference getDeleteReference(AlarmID) const;

	RegistrationData getRegistrationData(AlarmID) const;
	RegistrationData& getRegistrationDataReference(AlarmID);

	// ---> Initialize/Deinitialize helpers
	void initializeRegistrationData();
	void deinitializeRegistrationData();
	
	void incrementAlarmID(AlarmID& currentID);

private:
	RegistrationData _registrationData[AlarmableManager::MAX_NUMBER_OF_ALARMS];

private:
	// For personal debugging
	static void DebugPrint(const std::string& message);
	static const std::string DEBUG_TITLE_MESSAGE;
};

// For personal debugging
#ifndef Alarmable_DEBUG
#define Alarmable_DEBUG false
#endif // !Alarmable_DEBUG

#endif // !_Alarmable

//-----------------------------------------------------------------------------------------------------------------------------
// Alarmable Comment Template
//-----------------------------------------------------------------------------------------------------------------------------