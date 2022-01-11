#include "TankControllerPlayerFactory.h"
#include "TankControllerPlayerPool.h"

TankControllerPlayerFactory* TankControllerPlayerFactory::pInstance = nullptr;

TankControllerPlayerFactory& TankControllerPlayerFactory::GetInstance()
{
	if (TankControllerPlayerFactory::pInstance == nullptr)
	{
		TankControllerPlayerFactory::pInstance = new TankControllerPlayerFactory();
	}
	assert(TankControllerPlayerFactory::pInstance != nullptr);
	return *TankControllerPlayerFactory::pInstance;
}

TankControllerPlayer* TankControllerPlayerFactory::privCreateController()
{
	return TankControllerPlayerPool::GetController();
}

void TankControllerPlayerFactory::privReycleController(TankControllerPlayer* pController)
{
	TankControllerPlayerPool::ReturnController(pController);
}

void TankControllerPlayerFactory::Terminate()
{
	delete TankControllerPlayerFactory::pInstance;
	TankControllerPlayerFactory::pInstance = nullptr;
}
