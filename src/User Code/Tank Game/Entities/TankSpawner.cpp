#include "TankSpawner.h"
#include "TankFactory.h"

Tank* TankSpawner::spawnCharger()
{
	return TankFactory::CreateTank(TankControlType::AI_CHARGER_CONTROL, _pTarget, _position);
}

Tank* TankSpawner::spawnSniper()
{
	return TankFactory::CreateTank(TankControlType::AI_SNIPER_CONTROL, _pTarget, _position);;
}

void TankSpawner::setTarget(Tank* pTarget)
{
	_pTarget = pTarget;
}

void TankSpawner::setPosition(const Vect& position)
{
	_position.set(position);
}

const Vect& TankSpawner::getPosition() const
{
	return _position;
}
