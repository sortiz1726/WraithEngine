#include "TankControllerAICharger.h"
#include "Tank.h"
#include "TankControllerAIChargerFactory.h"
#include "Visualizer.h"
#include "MathTools.h"
#include "ScreenLog.h"
#include <algorithm>
#include <cmath>

const TankControlType TankControllerAICharger::CONTROL_TYPE = TankControlType::AI_CHARGER_CONTROL;

void TankControllerAICharger::initialize()
{
	_pTank->setBulletSpeed(60.0f);
	_pTank->setBulletDamage(10.0f);
	_pTank->setMoveSpeed(15.0f);
	_pTank->setHealth(40.0f);
	setFireDelay(2.0f);
	submitSceneEntry();
}

void TankControllerAICharger::deinitialize()
{
	submitSceneExit();
}

void TankControllerAICharger::setTankToControl(Tank* pTank)
{
	_pTank = pTank;
	_pTank->setControlType(TankControllerAICharger::CONTROL_TYPE);
}

void TankControllerAICharger::setFireDelay(float fireDelay)
{
	_fireDelay = fireDelay;
}

#pragma region Update

void TankControllerAICharger::update()
{
	float distance = (_pTank->getTankPosition() - _pTank->getTarget()->getTankPosition()).mag();
	if (distance > 40.0f)
	{
		_pTank->move(1.0f);
	}
	else if (distance < 20.0f)
	{
		_pTank->move(-1.0f);
	}
	_pTank->turnToTarget();
}

#pragma endregion

#pragma region Fire Bullet Alarm

void TankControllerAICharger::alarm0()
{
	_pTank->fireBullet();
	resetFireBulletAlarm();
}

void TankControllerAICharger::resetFireBulletAlarm()
{
	submitAlarmRegistration(_fireDelay, AlarmID::ALARM_0);
}

void TankControllerAICharger::cancelFireBulletAlarm()
{
	if (isRegisteredForAlarm(AlarmID::ALARM_0))
	{
		submitAlarmDeregistration(AlarmID::ALARM_0);
	}
}

Vect TankControllerAICharger::computeAimPosition(const Vect& targetPosition, const Vect& targetVelocity, 
	const Vect& projectilePosition, const Vect& projectileVelocity) const
{
	float a = targetVelocity.magSqr() - projectileVelocity.magSqr();
	float b = 2 * (targetVelocity[x] * (targetPosition[x] - projectilePosition[x]) + targetVelocity[z] * (targetPosition[z] - projectilePosition[z]));
	float c = ((targetPosition[x] - projectilePosition[x]) * (targetPosition[x] - projectilePosition[x]) + (targetPosition[z] - projectilePosition[z]) * (targetPosition[z] - projectilePosition[z]));

	float disc = b * b - (4.0f * a * c);

	if (disc >= 0)
	{
		float t1 = (-b + std::sqrt(disc)) / (2.0f * a);
		float t2 = (-b - std::sqrt(disc)) / (2.0f * a);
		float t = std::max(t1, t2);
		return targetPosition + t * targetVelocity;
	}
	else
	{
		return targetPosition;
	}
}

#pragma endregion

#pragma region Scene Entry and Exit

void TankControllerAICharger::sceneEntry()
{
	submitUpdateRegistration();
	resetFireBulletAlarm();
}

void TankControllerAICharger::sceneExit()
{
	submitUpdateDeregistration();
	cancelFireBulletAlarm();

	_pTank = nullptr;

	TankControllerAIChargerFactory::RecycleController(this);
}

#pragma endregion