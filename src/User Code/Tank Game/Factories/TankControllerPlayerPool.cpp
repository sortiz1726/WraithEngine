#include "TankControllerPlayerPool.h"
#include "TankControllerPlayer.h"

TankControllerPlayerPool* TankControllerPlayerPool::pInstance = nullptr;

TankControllerPlayerPool& TankControllerPlayerPool::GetInstance()
{
	if (TankControllerPlayerPool::pInstance == nullptr)
	{
		TankControllerPlayerPool::pInstance = new TankControllerPlayerPool();
	}
	assert(TankControllerPlayerPool::pInstance != nullptr);
	return *TankControllerPlayerPool::pInstance;
}

#pragma region Controller Retrival and Storage

TankControllerPlayer* TankControllerPlayerPool::privGetController()
{
	TankControllerPlayer* pController;

	if (!_controllers.empty())
	{
		pController = _controllers.top();
		_controllers.pop();
	}
	else
	{
		pController = new TankControllerPlayer();
	}

	assert(pController != nullptr);
	return pController;
}

void TankControllerPlayerPool::privReturnController(TankControllerPlayer* pController)
{
	_controllers.push(pController);
}

#pragma endregion

#pragma region Termination

TankControllerPlayerPool::~TankControllerPlayerPool()
{
	deleteControllers();
}

void TankControllerPlayerPool::deleteControllers()
{
	while (!_controllers.empty())
	{
		delete _controllers.top();
		_controllers.pop();
	}
}

void TankControllerPlayerPool::Terminate()
{
	delete TankControllerPlayerPool::pInstance;
	TankControllerPlayerPool::pInstance = nullptr;
}

#pragma endregion
