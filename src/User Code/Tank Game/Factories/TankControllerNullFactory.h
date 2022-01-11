#ifndef _TankControllerNullFactory
#define _TankControllerNullFactory

class TankControllerNull;

class TankControllerNullFactory
{
private:
	static TankControllerNullFactory* pInstance;

	TankControllerNullFactory() = default;
	TankControllerNullFactory(const TankControllerNullFactory&) = delete;
	TankControllerNullFactory& operator=(const TankControllerNullFactory&) = delete;
	TankControllerNullFactory(TankControllerNullFactory&&) = delete;
	TankControllerNullFactory& operator=(TankControllerNullFactory&&) = delete;
	~TankControllerNullFactory() = default;

	static TankControllerNullFactory& GetInstance();

	TankControllerNull* privCreateController();
	void privReycleController(TankControllerNull*);

public:
	static TankControllerNull* CreateController()
	{
		return GetInstance().privCreateController();
	}

	static void RecycleController(TankControllerNull* pController)
	{
		GetInstance().privReycleController(pController);
	}

	static void Terminate();

};
#endif // !_TankControllerNullFactory

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerNullFactory Comment Template
//-----------------------------------------------------------------------------------------------------------------------------