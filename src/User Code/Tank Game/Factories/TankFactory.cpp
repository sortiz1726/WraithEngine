#include "TankFactory.h"
#include "TankPool.h"
#include "Tank.h"

#include "TankControllerPlayerFactory.h"
#include "TankControllerAIFactory.h"
#include "TankControllerAISniperFactory.h"
#include "TankControllerAIChargerFactory.h"
#include "TankControllerNullFactory.h"

#include "RecycleTankStrategyCollection.h"

#include "TankControllerPlayer.h"
#include "TankControllerAI.h"
#include "TankControllerAISniper.h"
#include "TankControllerAICharger.h"
#include "TankControllerNull.h"

#include <cassert>

TankFactory* TankFactory::pInstance = nullptr;

TankFactory& TankFactory::GetInstance()
{
	if (TankFactory::pInstance == nullptr)
	{
		TankFactory::pInstance = new TankFactory();
	}
	assert(TankFactory::pInstance != nullptr);
	return *TankFactory::pInstance;
}

Tank* TankFactory::privCreateTank(TankControlType controlType, Tank* pTarget, const Vect& position, float rotationY, float uniformScale)
{
	Tank* pTank = TankPool::GetTank();

	pTank->setTarget(pTarget);
	pTank->initialize(getTankController(controlType), position, rotationY, uniformScale);

	_activeTanks.push_back(pTank);
	return pTank;
}

TankController* TankFactory::getTankController(TankControlType controlType) const
{
	TankController* pController = nullptr;
	switch (controlType)
	{
	case TankControlType::PLAYER_CONTROL:
		pController = TankControllerPlayerFactory::CreateController();
		break;
	case TankControlType::AI_CONTROL:
		pController = TankControllerAIFactory::CreateController();
		break;
	case TankControlType::AI_SNIPER_CONTROL:
		pController = TankControllerAISniperFactory::CreateController();
		break;
	case TankControlType::AI_CHARGER_CONTROL:
		pController = TankControllerAIChargerFactory::CreateController();
		break;
	case TankControlType::NULL_CONTROL:
		pController = TankControllerNullFactory::CreateController();
		break;
	default:
		break;
	}
	
	assert(pController != nullptr);

	return pController;
}

void TankFactory::privRecycleTank(Tank* pTank)
{
	_activeTanks.remove(pTank);
	TankPool::ReturnTank(pTank);
}

void TankFactory::privRecallActiveTanks()
{
	for (Tank* pTank : _activeTanks)
	{
		pTank->setRecycleStrategy(&RecycleTankStrategyCollection::RecycleToFactory);
		pTank->submitSceneExit();
	}
}

void TankFactory::Termintate()
{
	delete TankFactory::pInstance;
	TankFactory::pInstance = nullptr;
	TankPool::Terminate();
}

TankFactory::~TankFactory()
{
	for (Tank* pTank : _activeTanks)
	{
		TankPool::ReturnTank(pTank);
	}
	_activeTanks.clear();
}