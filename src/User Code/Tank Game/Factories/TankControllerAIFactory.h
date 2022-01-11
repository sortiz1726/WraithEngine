#ifndef _TankControllerAIFactory
#define _TankControllerAIFactory

class TankControllerAI;

class TankControllerAIFactory
{
private:
	static TankControllerAIFactory* pInstance;

	TankControllerAIFactory() = default;
	TankControllerAIFactory(const TankControllerAIFactory&) = delete;
	TankControllerAIFactory& operator=(const TankControllerAIFactory&) = delete;
	TankControllerAIFactory(TankControllerAIFactory&&) = delete;
	TankControllerAIFactory& operator=(TankControllerAIFactory&&) = delete;
	~TankControllerAIFactory() = default;

	static TankControllerAIFactory& GetInstance();

	TankControllerAI* privCreateController();
	void privReycleController(TankControllerAI*);

public:
	static TankControllerAI* CreateController()
	{
		return GetInstance().privCreateController();
	}

	static void RecycleController(TankControllerAI* pController)
	{
		GetInstance().privReycleController(pController);
	}

	static void Terminate();

};
#endif // !_TankControllerAIFactory

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerAIFactory Comment Template
//-----------------------------------------------------------------------------------------------------------------------------