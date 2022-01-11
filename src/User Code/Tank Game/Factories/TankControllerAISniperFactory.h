#ifndef _TankControllerAISniperFactory
#define _TankControllerAISniperFactory

class TankControllerAISniper;

class TankControllerAISniperFactory
{
private:
	static TankControllerAISniperFactory* pInstance;

	TankControllerAISniperFactory() = default;
	TankControllerAISniperFactory(const TankControllerAISniperFactory&) = delete;
	TankControllerAISniperFactory& operator=(const TankControllerAISniperFactory&) = delete;
	TankControllerAISniperFactory(TankControllerAISniperFactory&&) = delete;
	TankControllerAISniperFactory& operator=(TankControllerAISniperFactory&&) = delete;
	~TankControllerAISniperFactory() = default;

	static TankControllerAISniperFactory& GetInstance();

	TankControllerAISniper* privCreateController();
	void privReycleController(TankControllerAISniper*);

public:
	static TankControllerAISniper* CreateController()
	{
		return GetInstance().privCreateController();
	}

	static void RecycleController(TankControllerAISniper* pController)
	{
		GetInstance().privReycleController(pController);
	}

	static void Terminate();

};
#endif // !_TankControllerAISniperFactory

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerAISniperFactory Comment Template
//-----------------------------------------------------------------------------------------------------------------------------