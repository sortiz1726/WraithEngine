#include "AlarmController.h"
#include "Wraith.h"
#include "SpriteString.h"
#include "SpriteFontManager.h"
#include "TimeManager.h"
#include "GameController.h"
#include <cmath>
#include <string>

AlarmController::AlarmController()
	: _pTimerSprite(nullptr),
	_pMessage(nullptr)
{
	_pTimerSprite = new SpriteString();
	_pMessage = new SpriteString();

	SpriteFont* pFont = SpriteFontManager::GetSpriteFont("StencilOrangeFont");
	_pMessage->set(pFont, "SURVIVE", 0, 0);
	int xPosition = (Wraith::GetWindowWidth() / 2) - (_pMessage->getWidth() / 2);
	int yPosition = Wraith::GetWindowHeight() - 80 + _pMessage->getHeight();
	_pMessage->setPosition(xPosition, yPosition);

	setTriggerTime(0.0f);

	submitUpdateRegistration();
	submitDraw2DRegistration();
}

AlarmController::~AlarmController()
{
	delete _pTimerSprite;
	delete _pMessage;
}

void AlarmController::setTriggerTime(float triggerTime)
{
	_triggerTime = triggerTime;
	if (!isRegisteredForAlarm(AlarmID::ALARM_0))
	{
		_time = _triggerTime;
	}
}

void AlarmController::startTimer()
{
	if (!isRegisteredForAlarm(AlarmID::ALARM_0))
	{
		_time = _triggerTime;
		submitAlarmRegistration(_time, AlarmID::ALARM_0);
	}
}

void AlarmController::setGameControllerToNotify(GameController* pGameController)
{
	_pGameController = pGameController;
}

void AlarmController::update()
{
	if (isRegisteredForAlarm(AlarmID::ALARM_0))
	{
		_time = getTimeLeftForAlarm(AlarmID::ALARM_0);
	}
	updateTimer();
}

void AlarmController::updateTimer()
{
	SpriteFont* pFont = SpriteFontManager::GetSpriteFont("MilitaryGreenFont");

	_pTimerSprite->set(pFont, secondsToTime(_time), 0, 0);
	int xPosition = (Wraith::GetWindowWidth()) - (_pTimerSprite->getWidth()) - 10;
	int yPosition = Wraith::GetWindowHeight() - _pTimerSprite->getHeight();
	_pTimerSprite->setPosition(xPosition, yPosition);
}

std::string AlarmController::secondsToTime(float timeInSeconds)
{
	int minutes = static_cast<int>(std::floorf(timeInSeconds / 60.0f));
	int seconds = static_cast<int>(timeInSeconds - (minutes * 60.0f));

	std::string timeMessage = std::to_string(minutes) + ":";
	if (seconds < 10)
	{
		timeMessage += std::to_string(0);
	}
	timeMessage += std::to_string(seconds);

	timeMessage = "Time left: " + timeMessage;

	return timeMessage;
}

void AlarmController::draw2D()
{
	_pTimerSprite->render();
	//_pMessage->render();
}

void AlarmController::alarm0()
{
	_pGameController->switchToMissionFailed();
}