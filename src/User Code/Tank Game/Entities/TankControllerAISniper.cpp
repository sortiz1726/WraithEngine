#include "TankControllerAISniper.h"
#include "Tank.h"
#include "TankControllerAISniperFactory.h"
#include "Visualizer.h"
#include "MathTools.h"
#include "ScreenLog.h"
#include <algorithm>
#include <cmath>

const TankControlType TankControllerAISniper::CONTROL_TYPE = TankControlType::AI_SNIPER_CONTROL;

void TankControllerAISniper::initialize()
{
	_pTank->setBulletSpeed(80.0f);
	_pTank->setBulletDamage(25.0f);
	_pTank->setMoveSpeed(10.0f);
	_pTank->setHealth(30.0f);
	setFireDelay(5.0f);
	submitSceneEntry();
}

void TankControllerAISniper::deinitialize()
{
	submitSceneExit();
}

void TankControllerAISniper::setTankToControl(Tank* pTank)
{
	_pTank = pTank;
	_pTank->setControlType(TankControllerAISniper::CONTROL_TYPE);
}

void TankControllerAISniper::setFireDelay(float fireDelay)
{
	_fireDelay = fireDelay;
}

#pragma region Update

void TankControllerAISniper::update()
{
	float distance = (_pTank->getTankPosition() - _pTank->getTarget()->getTankPosition()).mag();
	if (distance > 100.0f)
	{
		_pTank->move(1.0f);
	}
	else if(distance < 70.0f)
	{
		_pTank->move(-1.0f);
	}

	Tank* pTarget = _pTank->getTarget();
	
	Vect aimPosition = computeAimPosition(pTarget->getTankPosition(), pTarget->getVelocity(),
		_pTank->getTankPosition(), Vect(0.0f, 0.0f, _pTank->getBulletSpeed()));
	
	//ScreenLog::Add("PlayerTank (Position): (%3.1f, %3.1f, %3.1f)", aimPosition[x], aimPosition[y], aimPosition[z]);
	Visualizer::ShowPointAt(aimPosition);
	
	_pTank->turnTo(aimPosition);
}

#pragma endregion

#pragma region Fire Bullet Alarm

void TankControllerAISniper::alarm0()
{
	_pTank->fireBullet();
	resetFireBulletAlarm();
}

void TankControllerAISniper::resetFireBulletAlarm()
{
	submitAlarmRegistration(_fireDelay, AlarmID::ALARM_0);
}

void TankControllerAISniper::cancelFireBulletAlarm()
{
	if (isRegisteredForAlarm(AlarmID::ALARM_0))
	{
		submitAlarmDeregistration(AlarmID::ALARM_0);
	}
}

Vect TankControllerAISniper::computeAimPosition(const Vect& targetPosition, const Vect& targetVelocity, 
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

void TankControllerAISniper::sceneEntry()
{
	submitUpdateRegistration();
	resetFireBulletAlarm();
}

void TankControllerAISniper::sceneExit()
{
	submitUpdateDeregistration();
	cancelFireBulletAlarm();

	_pTank = nullptr;

	TankControllerAISniperFactory::RecycleController(this);
}

#pragma endregion