#include "Alarmable.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "TimeManager.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Initialize/Deinitialize functions
//-----------------------------------------------------------------------------------------------------------------------------
Alarmable::Alarmable()
{
	initializeRegistrationData();
}

void Alarmable::initializeRegistrationData()
{
	AlarmID currentAlarmID = AlarmID::ALARM_0;
	for (RegistrationData& registrationData : _registrationData)
	{
		registrationData._pAlarmRegistrationCommand = new AlarmRegistrationCommand(this, currentAlarmID);
		registrationData._pAlarmDeregistrationCommand = new AlarmDeregistrationCommand(this, currentAlarmID);
		registrationData._currentRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;

		incrementAlarmID(currentAlarmID);
	}
}

void Alarmable::incrementAlarmID(AlarmID& currentID)
{
	currentID = static_cast<AlarmID>(static_cast<int>(currentID) + 1);
}

Alarmable::~Alarmable()
{
	Alarmable::DebugPrint("Destructor Called");
	deinitializeRegistrationData();
}

void Alarmable::deinitializeRegistrationData()
{
	for (RegistrationData& registrationData : _registrationData)
	{
		delete registrationData._pAlarmRegistrationCommand;
		delete registrationData._pAlarmDeregistrationCommand;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Registration/Deregistration functions
//-----------------------------------------------------------------------------------------------------------------------------
void Alarmable::submitAlarmRegistration(float timeDelay, AlarmID alarmID)
{
	RegistrationData& registrationData = getRegistrationDataReference(alarmID);

	assert(registrationData._currentRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	registrationData._pAlarmRegistrationCommand->setTimeDelay(timeDelay);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), registrationData._pAlarmRegistrationCommand);
	registrationData._currentRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::registerAlarm(float timeDelay, AlarmID alarmID)
{
	RegistrationData& registrationData = getRegistrationDataReference(alarmID);

	assert(registrationData._currentRegistrationState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::RegistrationAccess::RegisterEntity(SceneManager::GetCurrentScene(), this, timeDelay, alarmID);
	registrationData._currentRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}


void Alarmable::submitAlarmDeregistration(AlarmID alarmID)
{
	RegistrationData& registrationData = getRegistrationDataReference(alarmID);
	
	assert(registrationData._currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::RegistrationAccess::SubmitCommand(SceneManager::GetCurrentScene(), registrationData._pAlarmDeregistrationCommand);
	registrationData._currentRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}

void Alarmable::deregisterAlarm(AlarmID alarmID)
{
	RegistrationData& registrationData = getRegistrationDataReference(alarmID);

	assert(registrationData._currentRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::RegistrationAccess::DeregisterEntity(SceneManager::GetCurrentScene(), this, alarmID);
	registrationData._currentRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

bool Alarmable::isRegisteredForAlarm(AlarmID alarmID) const
{
	return getRegistrationData(alarmID)._currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED;
}

float Alarmable::getTimeLeftForAlarm(AlarmID alarmID) const
{
	RegistrationData registrationData = getRegistrationData(alarmID);

	float timeLeft = 0.0f;

	if(registrationData._currentRegistrationState == RegistrationState::CURRENTLY_REGISTERED)
	{
		float triggerTime = registrationData._deleteReference->first;
		float currentTime = TimeManager::GetTimeInSeconds();

		timeLeft = triggerTime - currentTime;
	}

	return timeLeft;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setter/Getter Terminate Reference
//-----------------------------------------------------------------------------------------------------------------------------
void Alarmable::setDeleteReference(const AlarmableManager::TimeLineReference& deleteReference, AlarmID alarmID)
{
	RegistrationData& registrationData = getRegistrationDataReference(alarmID);

	registrationData._deleteReference = deleteReference;
}

AlarmableManager::TimeLineReference Alarmable::getDeleteReference(AlarmID alarmID) const
{
	RegistrationData registrationData = getRegistrationData(alarmID);

	return registrationData._deleteReference;
}

Alarmable::RegistrationData& Alarmable::getRegistrationDataReference(AlarmID alarmID)
{
	return _registrationData[static_cast<int>(alarmID)];
}

Alarmable::RegistrationData Alarmable::getRegistrationData(AlarmID alarmID) const
{
	return _registrationData[static_cast<int>(alarmID)];
}

//-----------------------------------------------------------------------------------------------------------------------------
// Alarm Trigger functions
//-----------------------------------------------------------------------------------------------------------------------------
void Alarmable::triggerAlarm(AlarmID alarmID)
{
	RegistrationData& registrationData = getRegistrationDataReference(alarmID);

	registrationData._currentRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
	switch (alarmID)
	{
	case AlarmID::ALARM_0:
		alarm0();
		break;
	case AlarmID::ALARM_1:
		alarm1();
		break;
	case AlarmID::ALARM_2:
		alarm2();
		break;
	}
}


//-----------------------------------------------------------------------------------------------------------------------------
//  To be implemented by user in object derived from GameObject (NOT directly derived from Alarmable)
//-----------------------------------------------------------------------------------------------------------------------------
void Alarmable::alarm0()
{
	// Does nothing
}

void Alarmable::alarm1()
{
	// Does nothing
}

void Alarmable::alarm2()
{
	// Does nothing
}

//-----------------------------------------------------------------------------------------------------------------------------
// For personal debugging
//-----------------------------------------------------------------------------------------------------------------------------
const std::string Alarmable::DEBUG_TITLE_MESSAGE = "Alarmable_DEBUG: ";

void Alarmable::DebugPrint(const std::string& message)
{
	(void(message));
#if Alarmable_DEBUG
	if (message.size() == 0)
	{
		Trace::out("\n");
	}
	else
	{
		std::string finalMessage = Alarmable::DEBUG_TITLE_MESSAGE + message + std::string("\n");
		Trace::out("%s", finalMessage.c_str());
	}
#endif // !Alarmable_DEBUG
}
