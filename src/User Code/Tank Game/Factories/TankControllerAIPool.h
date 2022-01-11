#ifndef _TankControllerAIPool
#define _TankControllerAIPool

#include <stack>

class TankControllerAI;

class TankControllerAIPool
{
private:
	static TankControllerAIPool* pInstance;

	TankControllerAIPool() = default;
	TankControllerAIPool(const TankControllerAIPool&) = delete;
	TankControllerAIPool& operator=(const TankControllerAIPool&) = delete;
	TankControllerAIPool(TankControllerAIPool&&) = delete;
	TankControllerAIPool& operator=(TankControllerAIPool&&) = delete;
	~TankControllerAIPool();

	static TankControllerAIPool& GetInstance();

	TankControllerAI* privGetController();
	void privReturnController(TankControllerAI*);

	void deleteControllers();

public:
	static TankControllerAI* GetController()
	{
		return GetInstance().privGetController();
	}

	static void ReturnController(TankControllerAI* pController)
	{
		GetInstance().privReturnController(pController);
	}

	static void Terminate();

private:
	std::stack<TankControllerAI*> _controllers;

};
#endif // !_TankControllerAIPool

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerAIPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------