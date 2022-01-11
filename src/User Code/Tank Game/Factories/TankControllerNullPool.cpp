#include "TankControllerNullPool.h"
#include "TankControllerNull.h"

TankControllerNullPool* TankControllerNullPool::pInstance = nullptr;

TankControllerNullPool& TankControllerNullPool::GetInstance()
{
	if (TankControllerNullPool::pInstance == nullptr)
	{
		TankControllerNullPool::pInstance = new TankControllerNullPool();
	}
	assert(TankControllerNullPool::pInstance != nullptr);
	return *TankControllerNullPool::pInstance;
}

#pragma region Controller Retrival and Storage

TankControllerNull* TankControllerNullPool::privGetController()
{
	TankControllerNull* pController;

	if (!_controllers.empty())
	{
		pController = _controllers.top();
		_controllers.pop();
	}
	else
	{
		pController = new TankControllerNull();
	}

	assert(pController != nullptr);
	return pController;
}

void TankControllerNullPool::privReturnController(TankControllerNull* pController)
{
	_controllers.push(pController);
}

#pragma endregion

#pragma region Termination

TankControllerNullPool::~TankControllerNullPool()
{
	deleteControllers();
}

void TankControllerNullPool::deleteControllers()
{
	while (!_controllers.empty())
	{
		delete _controllers.top();
		_controllers.pop();
	}
}

void TankControllerNullPool::Terminate()
{
	delete TankControllerNullPool::pInstance;
	TankControllerNullPool::pInstance = nullptr;
}

#pragma endregion
