#include "TankKillMonitor.h"

#include "TankSpawner.h"
#include "TankFactory.h"
#include "Tank.h"
#include "SpriteString.h"
#include "SpriteFontManager.h"
#include "SceneSwitcher.h"
#include "Wraith.h"
#include "GameController.h"

#include <cstdlib>

const int TankKillMonitor::MAX_NUMBER_OF_ENEMY_TANKS = 5;

TankKillMonitor::TankKillMonitor()
	: _pTarget(nullptr),
	_numberOfActiveEnemyTanks(0),
	_drawText(true)
{
	_pLeftToKillCounter = new SpriteString();

	setLeftToKill(10);
	setMaxNumberOfEnemyTanks(TankKillMonitor::MAX_NUMBER_OF_ENEMY_TANKS);

	_recycleTankStategy.setTankKillMonitor(this);

	submitUpdateRegistration();
	submitDraw2DRegistration();
	submitAlarmRegistration(3.0f, AlarmID::ALARM_0);
}

TankKillMonitor::~TankKillMonitor()
{
	for (TankSpawner* pTankSpawner : _tankSpawners)
	{
		delete pTankSpawner;
	}

	delete _pLeftToKillCounter;
}

#pragma region GameObject Properties

void TankKillMonitor::update()
{
}

void TankKillMonitor::draw2D()
{
	if(_drawText) _pLeftToKillCounter->render();
}

void TankKillMonitor::alarm0()
{
	if (canSpawnTanks())
	{
		spawnTanks();
	}
	submitAlarmRegistration(3.0f, AlarmID::ALARM_0);
}

#pragma endregion

#pragma region Actions

void TankKillMonitor::createTankSpawnerAt(const Vect& position)
{
	TankSpawner* pTankSpawner = new TankSpawner();
	pTankSpawner->setPosition(position);
	pTankSpawner->setTarget(_pTarget);
	_tankSpawners.push_back(pTankSpawner);
}

bool TankKillMonitor::canSpawnTanks() const
{
	return _leftToKill > 0 && _numberOfActiveEnemyTanks < _maxNumberOfEnemyTanks;
}

void TankKillMonitor::spawnTanks()
{
	auto tankSpawnerIterator = _tankSpawners.begin();
	while (canSpawnTanks() && tankSpawnerIterator != _tankSpawners.end())
	{
		TankSpawner* pTankSpawner = *tankSpawnerIterator;
		spawnTankUsing(pTankSpawner);
		++tankSpawnerIterator;
	}
}

void TankKillMonitor::spawnTankUsing(TankSpawner* pTankSpawner)
{
	Vect fromSpawnerToTarget = _pTarget->getTankPosition() - pTankSpawner->getPosition();

	float maxDistance = 120.0f;
	float sqaureDistance = fromSpawnerToTarget.magSqr();
	if (sqaureDistance > (maxDistance * maxDistance)) return;

	Tank* pTank = nullptr;

	int randNum = (std::rand() % 5);
	if (randNum == 0)
	{
		pTank = pTankSpawner->spawnSniper();
	}
	else
	{
		pTank = pTankSpawner->spawnCharger();
	}
	pTank->setRecycleStrategy(&_recycleTankStategy);

	_numberOfActiveEnemyTanks += 1;
}

void TankKillMonitor::recycleDestroyedTank(Tank* pTank)
{
	//Trace::out("TankKillMonitor: Recycled Tank\n");
	TankFactory::RecycleTank(pTank);
	offsetLeftToKill(-1);
	_numberOfActiveEnemyTanks -= 1;
}

void TankKillMonitor::setDrawText(bool drawText)
{
	_drawText = drawText;
}

#pragma endregion

#pragma region Setters/Getters

void TankKillMonitor::setTarget(Tank* pTarget)
{
	_pTarget = pTarget;
}

void TankKillMonitor::setLeftToKill(int leftToKill)
{
	_leftToKill = leftToKill;

	if (_leftToKill <= 0)
	{
		_pGameController->switchToNextScene();
	}

	SpriteFont* pFont = SpriteFontManager::GetSpriteFont("MilitaryGreenFont");
	std::string message = "Tanks To Kill: " + std::to_string(_leftToKill);
	_pLeftToKillCounter->set(pFont, message, 0, 0);
	int positionX = 0, positionY = 0;
	//positionX = Wraith::GetWindowWidth() - _pBuildingLeftCounter->getWidth() - 10;
	positionX = 0;
	positionY = Wraith::GetWindowHeight() - _pLeftToKillCounter->getHeight();
	_pLeftToKillCounter->setPosition(positionX, positionY);
}

void TankKillMonitor::offsetLeftToKill(int offsetLeftToKill)
{
	setLeftToKill(_leftToKill + offsetLeftToKill);
}

void TankKillMonitor::setMaxNumberOfEnemyTanks(int maxNumberOfEnemyTanks)
{
	_maxNumberOfEnemyTanks = maxNumberOfEnemyTanks;
}

#pragma endregion