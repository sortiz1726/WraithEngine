#ifndef _TankPool
#define _TankPool

#include <stack>

class Tank;

class TankPool
{
private:
	typedef std::stack<Tank*> StorageContainer;
private:
	static TankPool* pTankPoolInstance;

	TankPool() = default;
	TankPool(const TankPool&) = delete;
	TankPool& operator=(const TankPool&) = delete;
	TankPool(TankPool&&) = delete;
	TankPool& operator=(TankPool&&) = delete;
	~TankPool();

	static TankPool& GetInstance();

	// Tank Retrival/Return
	Tank* privGetTank();
	void privReturnTank(Tank*);

	// --> Tank Termintation helpers
	void deleteTanks();

public:
	static Tank* GetTank()
	{
		return GetInstance().privGetTank();
	}

	static void ReturnTank(Tank* pTank)
	{
		GetInstance().privReturnTank(pTank);
	}

	static void Terminate();

private:
	StorageContainer _recycledTanks;
};
#endif // !_TankPool

//-----------------------------------------------------------------------------------------------------------------------------
// TankPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------