#ifndef _TankControllerPlayerFactory
#define _TankControllerPlayerFactory

class TankControllerPlayer;

class TankControllerPlayerFactory
{
private:
	static TankControllerPlayerFactory* pInstance;

	TankControllerPlayerFactory() = default;
	TankControllerPlayerFactory(const TankControllerPlayerFactory&) = delete;
	TankControllerPlayerFactory& operator=(const TankControllerPlayerFactory&) = delete;
	TankControllerPlayerFactory(TankControllerPlayerFactory&&) = delete;
	TankControllerPlayerFactory& operator=(TankControllerPlayerFactory&&) = delete;
	~TankControllerPlayerFactory() = default;

	static TankControllerPlayerFactory& GetInstance();

	TankControllerPlayer* privCreateController();
	void privReycleController(TankControllerPlayer*);

public:
	static TankControllerPlayer* CreateController()
	{
		return GetInstance().privCreateController();
	}

	static void RecycleController(TankControllerPlayer* pController)
	{
		GetInstance().privReycleController(pController);
	}

	static void Terminate();

};
#endif // !_TankControllerPlayerFactory

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerPlayerFactory Comment Template
//-----------------------------------------------------------------------------------------------------------------------------