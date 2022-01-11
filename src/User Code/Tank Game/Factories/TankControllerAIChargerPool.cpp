#include "TankControllerAIChargerPool.h"
#include "TankControllerAICharger.h"

TankControllerAIChargerPool* TankControllerAIChargerPool::pInstance = nullptr;

TankControllerAIChargerPool& TankControllerAIChargerPool::GetInstance()
{
	if (TankControllerAIChargerPool::pInstance == nullptr)
	{
		TankControllerAIChargerPool::pInstance = new TankControllerAIChargerPool();
	}
	assert(TankControllerAIChargerPool::pInstance != nullptr);
	return *TankControllerAIChargerPool::pInstance;
}

#pragma region Controller Retrival and Storage

TankControllerAICharger* TankControllerAIChargerPool::privGetController()
{
	TankControllerAICharger* pController;

	if (!_controllers.empty())
	{
		pController = _controllers.top();
		_controllers.pop();
	}
	else
	{
		pController = new TankControllerAICharger();
	}

	assert(pController != nullptr);
	return pController;
}

void TankControllerAIChargerPool::privReturnController(TankControllerAICharger* pController)
{
	_controllers.push(pController);
}

#pragma endregion

#pragma region Termination

TankControllerAIChargerPool::~TankControllerAIChargerPool()
{
	deleteControllers();
}

void TankControllerAIChargerPool::deleteControllers()
{
	while (!_controllers.empty())
	{
		delete _controllers.top();
		_controllers.pop();
	}
}

void TankControllerAIChargerPool::Terminate()
{
	delete TankControllerAIChargerPool::pInstance;
	TankControllerAIChargerPool::pInstance = nullptr;
}

#pragma endregion
