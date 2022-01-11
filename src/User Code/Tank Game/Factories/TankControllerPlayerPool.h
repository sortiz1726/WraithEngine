#ifndef _TankControllerPlayerPool
#define _TankControllerPlayerPool

#include <stack>

class TankControllerPlayer;

class TankControllerPlayerPool
{
private:
	static TankControllerPlayerPool* pInstance;

	TankControllerPlayerPool() = default;
	TankControllerPlayerPool(const TankControllerPlayerPool&) = delete;
	TankControllerPlayerPool& operator=(const TankControllerPlayerPool&) = delete;
	TankControllerPlayerPool(TankControllerPlayerPool&&) = delete;
	TankControllerPlayerPool& operator=(TankControllerPlayerPool&&) = delete;
	~TankControllerPlayerPool();

	static TankControllerPlayerPool& GetInstance();

	TankControllerPlayer* privGetController();
	void privReturnController(TankControllerPlayer*);
	
	void deleteControllers();

public:
	static TankControllerPlayer* GetController()
	{
		return GetInstance().privGetController();
	}

	static void ReturnController(TankControllerPlayer* pController)
	{
		GetInstance().privReturnController(pController);
	}

	static void Terminate();

private:
	std::stack<TankControllerPlayer*> _controllers;

};
#endif // !_TankControllerPlayerPool

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerPlayerPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------