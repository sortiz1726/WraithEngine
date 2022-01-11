#include "TankControllerNullFactory.h"
#include "TankControllerNullPool.h"

TankControllerNullFactory* TankControllerNullFactory::pInstance = nullptr;

TankControllerNullFactory& TankControllerNullFactory::GetInstance()
{
	if (TankControllerNullFactory::pInstance == nullptr)
	{
		TankControllerNullFactory::pInstance = new TankControllerNullFactory();
	}
	assert(TankControllerNullFactory::pInstance != nullptr);
	return *TankControllerNullFactory::pInstance;
}

TankControllerNull* TankControllerNullFactory::privCreateController()
{
	return TankControllerNullPool::GetController();
}

void TankControllerNullFactory::privReycleController(TankControllerNull* pController)
{
	TankControllerNullPool::ReturnController(pController);
}

void TankControllerNullFactory::Terminate()
{
	delete TankControllerNullFactory::pInstance;
	TankControllerNullFactory::pInstance = nullptr;
}
