#ifndef _AlarmController
#define _AlarmController

#include "GameObject.h"
#include <string>

class SpriteString;
class GameController;

class AlarmController : public GameObject
{
public:
	AlarmController();
	AlarmController(const AlarmController&) = default;
	AlarmController& operator=(const AlarmController&) = default;
	AlarmController(AlarmController&&) = default;
	AlarmController& operator=(AlarmController&&) = default;
	~AlarmController();

	void setTriggerTime(float timer);
	void startTimer();

	void setGameControllerToNotify(GameController*);

private:
	virtual void update() override;
	virtual void draw2D() override;
	virtual void alarm0() override;

	void updateTimer();
	std::string secondsToTime(float seconds);

private:
	SpriteString* _pTimerSprite;
	SpriteString* _pMessage;
	float _triggerTime;
	float _time;
	GameController* _pGameController;

};
#endif // !_AlarmController

//-----------------------------------------------------------------------------------------------------------------------------
// AlarmController Comment Template
//-----------------------------------------------------------------------------------------------------------------------------