#include "TankControllerAI.h"
#include "Tank.h"
#include "TankControllerAIFactory.h"
#include "Visualizer.h"
#include "MathTools.h"
#include "ScreenLog.h"
#include <algorithm>
#include <cmath>

const TankControlType TankControllerAI::CONTROL_TYPE = TankControlType::AI_CONTROL;

void TankControllerAI::initialize()
{
	_pTank->setBulletSpeed(60.0f);
	setFireDelay(2.0f);
	submitSceneEntry();
}

void TankControllerAI::deinitialize()
{
	submitSceneExit();
}

void TankControllerAI::setTankToControl(Tank* pTank)
{
	_pTank = pTank;
	_pTank->setControlType(TankControllerAI::CONTROL_TYPE);
}

void TankControllerAI::setFireDelay(float fireDelay)
{
	_fireDelay = fireDelay;
}

#pragma region Update

void TankControllerAI::update()
{
	float distance = (_pTank->getTankPosition() - _pTank->getTarget()->getTankPosition()).mag();
	if (distance > 35.0f)
	{
		_pTank->move(1.0f);
	}
	else
	{
		_pTank->move(-1.0f);
	}
	_pTank->turnToTarget();

	//Tank* pTarget = _pTank->getTarget();
	//
	//Vect aimPosition = computeAimPosition(pTarget->getTankPosition(), pTarget->getVelocity(),
	//	_pTank->getTankPosition(), Vect(0.0f, 0.0f, _pTank->getBulletSpeed()));
	//
	////ScreenLog::Add("PlayerTank (Position): (%3.1f, %3.1f, %3.1f)", aimPosition[x], aimPosition[y], aimPosition[z]);
	//Visualizer::ShowPointAt(aimPosition);
	//
	//_pTank->turnTo(aimPosition);
}

#pragma endregion

#pragma region Fire Bullet Alarm

void TankControllerAI::alarm0()
{
	_pTank->fireBullet();
	resetFireBulletAlarm();
}

void TankControllerAI::resetFireBulletAlarm()
{
	submitAlarmRegistration(_fireDelay, AlarmID::ALARM_0);
}

void TankControllerAI::cancelFireBulletAlarm()
{
	if (isRegisteredForAlarm(AlarmID::ALARM_0))
	{
		submitAlarmDeregistration(AlarmID::ALARM_0);
	}
}

Vect TankControllerAI::computeAimPosition(const Vect& targetPosition, const Vect& targetVelocity, 
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

void TankControllerAI::sceneEntry()
{
	submitUpdateRegistration();
	resetFireBulletAlarm();
}

void TankControllerAI::sceneExit()
{
	submitUpdateDeregistration();
	cancelFireBulletAlarm();

	_pTank = nullptr;

	TankControllerAIFactory::RecycleController(this);
}

#pragma endregion