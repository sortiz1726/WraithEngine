#include "TankControllerAISniperFactory.h"
#include "TankControllerAISniperPool.h"

TankControllerAISniperFactory* TankControllerAISniperFactory::pInstance = nullptr;

TankControllerAISniperFactory& TankControllerAISniperFactory::GetInstance()
{
	if (TankControllerAISniperFactory::pInstance == nullptr)
	{
		TankControllerAISniperFactory::pInstance = new TankControllerAISniperFactory();
	}
	assert(TankControllerAISniperFactory::pInstance != nullptr);
	return *TankControllerAISniperFactory::pInstance;
}

TankControllerAISniper* TankControllerAISniperFactory::privCreateController()
{
	return TankControllerAISniperPool::GetController();
}

void TankControllerAISniperFactory::privReycleController(TankControllerAISniper* pController)
{
	TankControllerAISniperPool::ReturnController(pController);
}

void TankControllerAISniperFactory::Terminate()
{
	delete TankControllerAISniperFactory::pInstance;
	TankControllerAISniperFactory::pInstance = nullptr;
}
