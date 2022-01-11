#include "TankControllerAIPool.h"
#include "TankControllerAI.h"

TankControllerAIPool* TankControllerAIPool::pInstance = nullptr;

TankControllerAIPool& TankControllerAIPool::GetInstance()
{
	if (TankControllerAIPool::pInstance == nullptr)
	{
		TankControllerAIPool::pInstance = new TankControllerAIPool();
	}
	assert(TankControllerAIPool::pInstance != nullptr);
	return *TankControllerAIPool::pInstance;
}

#pragma region Controller Retrival and Storage

TankControllerAI* TankControllerAIPool::privGetController()
{
	TankControllerAI* pController;

	if (!_controllers.empty())
	{
		pController = _controllers.top();
		_controllers.pop();
	}
	else
	{
		pController = new TankControllerAI();
	}

	assert(pController != nullptr);
	return pController;
}

void TankControllerAIPool::privReturnController(TankControllerAI* pController)
{
	_controllers.push(pController);
}

#pragma endregion

#pragma region Termination

TankControllerAIPool::~TankControllerAIPool()
{
	deleteControllers();
}

void TankControllerAIPool::deleteControllers()
{
	while (!_controllers.empty())
	{
		delete _controllers.top();
		_controllers.pop();
	}
}

void TankControllerAIPool::Terminate()
{
	delete TankControllerAIPool::pInstance;
	TankControllerAIPool::pInstance = nullptr;
}

#pragma endregion
