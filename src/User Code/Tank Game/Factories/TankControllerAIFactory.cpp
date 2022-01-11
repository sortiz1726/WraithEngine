#include "TankControllerAIFactory.h"
#include "TankControllerAIPool.h"

TankControllerAIFactory* TankControllerAIFactory::pInstance = nullptr;

TankControllerAIFactory& TankControllerAIFactory::GetInstance()
{
	if (TankControllerAIFactory::pInstance == nullptr)
	{
		TankControllerAIFactory::pInstance = new TankControllerAIFactory();
	}
	assert(TankControllerAIFactory::pInstance != nullptr);
	return *TankControllerAIFactory::pInstance;
}

TankControllerAI* TankControllerAIFactory::privCreateController()
{
	return TankControllerAIPool::GetController();
}

void TankControllerAIFactory::privReycleController(TankControllerAI* pController)
{
	TankControllerAIPool::ReturnController(pController);
}

void TankControllerAIFactory::Terminate()
{
	delete TankControllerAIFactory::pInstance;
	TankControllerAIFactory::pInstance = nullptr;
}
