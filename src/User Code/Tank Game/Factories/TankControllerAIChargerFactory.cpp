#include "TankControllerAIChargerFactory.h"
#include "TankControllerAIChargerPool.h"

TankControllerAIChargerFactory* TankControllerAIChargerFactory::pInstance = nullptr;

TankControllerAIChargerFactory& TankControllerAIChargerFactory::GetInstance()
{
	if (TankControllerAIChargerFactory::pInstance == nullptr)
	{
		TankControllerAIChargerFactory::pInstance = new TankControllerAIChargerFactory();
	}
	assert(TankControllerAIChargerFactory::pInstance != nullptr);
	return *TankControllerAIChargerFactory::pInstance;
}

TankControllerAICharger* TankControllerAIChargerFactory::privCreateController()
{
	return TankControllerAIChargerPool::GetController();
}

void TankControllerAIChargerFactory::privReycleController(TankControllerAICharger* pController)
{
	TankControllerAIChargerPool::ReturnController(pController);
}

void TankControllerAIChargerFactory::Terminate()
{
	delete TankControllerAIChargerFactory::pInstance;
	TankControllerAIChargerFactory::pInstance = nullptr;
}
