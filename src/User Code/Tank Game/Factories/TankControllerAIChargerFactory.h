#ifndef _TankControllerAIChargerFactory
#define _TankControllerAIChargerFactory

class TankControllerAICharger;

class TankControllerAIChargerFactory
{
private:
	static TankControllerAIChargerFactory* pInstance;

	TankControllerAIChargerFactory() = default;
	TankControllerAIChargerFactory(const TankControllerAIChargerFactory&) = delete;
	TankControllerAIChargerFactory& operator=(const TankControllerAIChargerFactory&) = delete;
	TankControllerAIChargerFactory(TankControllerAIChargerFactory&&) = delete;
	TankControllerAIChargerFactory& operator=(TankControllerAIChargerFactory&&) = delete;
	~TankControllerAIChargerFactory() = default;

	static TankControllerAIChargerFactory& GetInstance();

	TankControllerAICharger* privCreateController();
	void privReycleController(TankControllerAICharger*);

public:
	static TankControllerAICharger* CreateController()
	{
		return GetInstance().privCreateController();
	}

	static void RecycleController(TankControllerAICharger* pController)
	{
		GetInstance().privReycleController(pController);
	}

	static void Terminate();

};
#endif // !_TankControllerAIChargerFactory

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerAIChargerFactory Comment Template
//-----------------------------------------------------------------------------------------------------------------------------