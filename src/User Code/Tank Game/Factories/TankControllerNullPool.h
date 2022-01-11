#ifndef _TankControllerNullPool
#define _TankControllerNullPool

#include <stack>

class TankControllerNull;

class TankControllerNullPool
{
private:
	static TankControllerNullPool* pInstance;

	TankControllerNullPool() = default;
	TankControllerNullPool(const TankControllerNullPool&) = delete;
	TankControllerNullPool& operator=(const TankControllerNullPool&) = delete;
	TankControllerNullPool(TankControllerNullPool&&) = delete;
	TankControllerNullPool& operator=(TankControllerNullPool&&) = delete;
	~TankControllerNullPool();

	static TankControllerNullPool& GetInstance();

	TankControllerNull* privGetController();
	void privReturnController(TankControllerNull*);

	void deleteControllers();

public:
	static TankControllerNull* GetController()
	{
		return GetInstance().privGetController();
	}

	static void ReturnController(TankControllerNull* pController)
	{
		GetInstance().privReturnController(pController);
	}

	static void Terminate();

private:
	std::stack<TankControllerNull*> _controllers;

};
#endif // !_TankControllerNullPool

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerNullPool Comment Template
//-----------------------------------------------------------------------------------------------------------------------------