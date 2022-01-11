#include "TankControllerPlayer.h"
#include "Tank.h"
#include "TankControllerPlayerFactory.h"

#include "ScreenLog.h"

const TankControlType TankControllerPlayer::CONTROL_TYPE = TankControlType::PLAYER_CONTROL;

#pragma region Key Inputs Settings

const AZUL_KEY TankControllerPlayer::KEY_HULL_MOVE_FOWARD = AZUL_KEY::KEY_W;
const AZUL_KEY TankControllerPlayer::KEY_HULL_MOVE_BACKWARD = AZUL_KEY::KEY_S;
const AZUL_KEY TankControllerPlayer::KEY_HULL_TURN_LEFT = AZUL_KEY::KEY_A;
const AZUL_KEY TankControllerPlayer::KEY_HULL_TURN_RIGHT = AZUL_KEY::KEY_D;
									 
const AZUL_KEY TankControllerPlayer::KEY_TURRET_TURN_LEFT = AZUL_KEY::KEY_L;
const AZUL_KEY TankControllerPlayer::KEY_TURRET_TURN_RIGHT = AZUL_KEY::KEY_J;
									 
const AZUL_KEY TankControllerPlayer::KEY_BULLET_FIRE = AZUL_KEY::KEY_SPACE;
const AZUL_KEY TankControllerPlayer::KEY_BULLET_RELOAD = AZUL_KEY::KEY_R;

#pragma endregion

void TankControllerPlayer::initialize()
{
	submitSceneEntry();
}

void TankControllerPlayer::deinitialize()
{
	submitSceneExit();
}

void TankControllerPlayer::setTankToControl(Tank* pTank)
{
	_pTank = pTank;
	_pTank->setControlType(TankControllerPlayer::CONTROL_TYPE);
}

#pragma region Update

void TankControllerPlayer::update()
{
	screenLogTankPosition();
	processHullInputs();
	processTurretInputs();
}

// ---> Update helpers
void TankControllerPlayer::screenLogTankPosition()
{
	Vect tankPosition = _pTank->getTankPosition();
	ScreenLog::Add("PlayerTank (Position): (%3.1f, %3.1f, %3.1f)", tankPosition[x], tankPosition[y], tankPosition[z]);
}

void TankControllerPlayer::processHullInputs()
{
	_pTank->move(computeHullMoveOffset());
	_pTank->turnHull(computeHullTurnOffset());
}

float TankControllerPlayer::computeHullMoveOffset() const
{
	float foward = static_cast<float>(Keyboard::GetKeyState(TankControllerPlayer::KEY_HULL_MOVE_FOWARD));
	float backward = static_cast<float>(Keyboard::GetKeyState(TankControllerPlayer::KEY_HULL_MOVE_BACKWARD));

	float moveOffset = foward - backward;

	return moveOffset;
}

float TankControllerPlayer::computeHullTurnOffset() const
{
	float turnLeft = static_cast<float>(Keyboard::GetKeyState(TankControllerPlayer::KEY_HULL_TURN_LEFT));
	float turnRight = static_cast<float>(Keyboard::GetKeyState(TankControllerPlayer::KEY_HULL_TURN_RIGHT));

	float turnOffset = turnLeft - turnRight;

	return turnOffset;
}

void TankControllerPlayer::processTurretInputs()
{
	_pTank->turnTurret(computeTurretTurnOffset());
}

float TankControllerPlayer::computeTurretTurnOffset() const
{
	float turnLeft = static_cast<float>(Keyboard::GetKeyState(TankControllerPlayer::KEY_TURRET_TURN_LEFT));
	float turnRight = static_cast<float>(Keyboard::GetKeyState(TankControllerPlayer::KEY_TURRET_TURN_RIGHT));

	float turnOffset = turnRight - turnLeft;

	return turnOffset;
}

#pragma endregion

#pragma region Inputs

void TankControllerPlayer::keyPressed(AZUL_KEY key)
{
	processBulletInputs(key);
}

// ---> Input Helpers
void TankControllerPlayer::processBulletInputs(AZUL_KEY key)
{
	switch (key)
	{
	case TankControllerPlayer::KEY_BULLET_FIRE:
		_pTank->fireBullet();
		break;
	case TankControllerPlayer::KEY_BULLET_RELOAD:
		_pTank->reloadBullets();
		break;
	}
}

#pragma endregion

#pragma region Scene Entry and Exit

void TankControllerPlayer::sceneEntry()
{
	submitUpdateRegistration();
	registerKeyInputs();
}

void TankControllerPlayer::registerKeyInputs()
{
	submitKeyRegistration(TankControllerPlayer::KEY_BULLET_FIRE, InputEvent::KEY_PRESS);
	submitKeyRegistration(TankControllerPlayer::KEY_BULLET_RELOAD, InputEvent::KEY_PRESS);
}

void TankControllerPlayer::sceneExit()
{
	submitUpdateDeregistration();
	deregisterKeyInputs();

	_pTank = nullptr;

	TankControllerPlayerFactory::RecycleController(this);
}

void TankControllerPlayer::deregisterKeyInputs()
{
	submitKeyDeregistration(TankControllerPlayer::KEY_BULLET_FIRE, InputEvent::KEY_PRESS);
	submitKeyDeregistration(TankControllerPlayer::KEY_BULLET_RELOAD, InputEvent::KEY_PRESS);
}

#pragma endregion
