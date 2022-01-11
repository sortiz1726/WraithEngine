#include "TankControllerAISniperPool.h"
#include "TankControllerAISniper.h"

TankControllerAISniperPool* TankControllerAISniperPool::pInstance = nullptr;

TankControllerAISniperPool& TankControllerAISniperPool::GetInstance()
{
	if (TankControllerAISniperPool::pInstance == nullptr)
	{
		TankControllerAISniperPool::pInstance = new TankControllerAISniperPool();
	}
	assert(TankControllerAISniperPool::pInstance != nullptr);
	return *TankControllerAISniperPool::pInstance;
}

#pragma region Controller Retrival and Storage

TankControllerAISniper* TankControllerAISniperPool::privGetController()
{
	TankControllerAISniper* pController;

	if (!_controllers.empty())
	{
		pController = _controllers.top();
		_controllers.pop();
	}
	else
	{
		pController = new TankControllerAISniper();
	}

	assert(pController != nullptr);
	return pController;
}

void TankControllerAISniperPool::privReturnController(TankControllerAISniper* pController)
{
	_controllers.push(pController);
}

#pragma endregion

#pragma region Termination

TankControllerAISniperPool::~TankControllerAISniperPool()
{
	deleteControllers();
}

void TankControllerAISniperPool::deleteControllers()
{
	while (!_controllers.empty())
	{
		delete _controllers.top();
		_controllers.pop();
	}
}

void TankControllerAISniperPool::Terminate()
{
	delete TankControllerAISniperPool::pInstance;
	TankControllerAISniperPool::pInstance = nullptr;
}

#pragma endregion
