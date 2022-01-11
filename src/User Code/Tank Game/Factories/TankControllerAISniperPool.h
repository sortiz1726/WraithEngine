#ifndef _TankControllerAISniperPool
#define _TankControllerAISniperPool

#include <stack>

class TankControllerAISniper;

class TankControllerAISniperPool
{
private:
	static TankControllerAISniperPool* pInstance;

	TankControllerAISniperPool() = default;
	TankControllerAISniperPool(const TankControllerAISniperPool&) = delete;
	TankControllerAISniperPool& operator=(const TankControllerAISniperPool&) = delete;
	TankControllerAISniperPool(TankControllerAISniperPool&&) = delete;
	TankControllerAISniperPool& operator=(TankControllerAISniperPool&&) = delete;
	~TankControllerAISniperPool();

	static TankControllerAISniperPool& GetInstance();

	TankControllerAISniper* privGetController();
	void privReturnController(TankControllerAISniper*);

	void deleteControllers();

public:
	static TankControllerAISniper* GetController()
	{
		return GetInstance().privGetController();
	}

	static void ReturnController(TankControllerAISniper* pController)
	{
		GetInstance().privReturnController(pController);
	}

	static void Terminate();

private:
	std::stack<TankControllerAISniper*> _controllers;

};
#endif // !_TankControllerAISniperPool

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerAISniperPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------