#ifndef _TankControllerAIChargerPool
#define _TankControllerAIChargerPool

#include <stack>

class TankControllerAICharger;

class TankControllerAIChargerPool
{
private:
	static TankControllerAIChargerPool* pInstance;

	TankControllerAIChargerPool() = default;
	TankControllerAIChargerPool(const TankControllerAIChargerPool&) = delete;
	TankControllerAIChargerPool& operator=(const TankControllerAIChargerPool&) = delete;
	TankControllerAIChargerPool(TankControllerAIChargerPool&&) = delete;
	TankControllerAIChargerPool& operator=(TankControllerAIChargerPool&&) = delete;
	~TankControllerAIChargerPool();

	static TankControllerAIChargerPool& GetInstance();

	TankControllerAICharger* privGetController();
	void privReturnController(TankControllerAICharger*);

	void deleteControllers();

public:
	static TankControllerAICharger* GetController()
	{
		return GetInstance().privGetController();
	}

	static void ReturnController(TankControllerAICharger* pController)
	{
		GetInstance().privReturnController(pController);
	}

	static void Terminate();

private:
	std::stack<TankControllerAICharger*> _controllers;

};
#endif // !_TankControllerAIChargerPool

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerAIChargerPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------