#include "TankPool.h"
#include "Tank.h"

TankPool* TankPool::pTankPoolInstance = nullptr;

TankPool& TankPool::GetInstance()
{
	if (pTankPoolInstance == nullptr)
	{
		pTankPoolInstance = new TankPool();
	}
	assert(pTankPoolInstance != nullptr);
	return *pTankPoolInstance;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Tank Retrival/Return
//-----------------------------------------------------------------------------------------------------------------------------
Tank* TankPool::privGetTank()
{
	Tank* pTank = nullptr;
	if (!_recycledTanks.empty())
	{
		pTank = _recycledTanks.top();
		_recycledTanks.pop();
	}
	else
	{
		pTank = new Tank();
	}
	assert(pTank != nullptr);
	return pTank;
}

void TankPool::privReturnTank(Tank* pTank)
{
	assert(pTank != nullptr);
	_recycledTanks.push(pTank);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Tank Pool Termination
//-----------------------------------------------------------------------------------------------------------------------------
void TankPool::Terminate()
{
	delete pTankPoolInstance;
	pTankPoolInstance = nullptr;
}

TankPool::~TankPool()
{
	deleteTanks();
}

// ---> Tank Pool Termination helper
void TankPool::deleteTanks()
{
	while (!_recycledTanks.empty())
	{
		delete _recycledTanks.top();
		_recycledTanks.pop();
	}
}