#ifndef _TankFactory
#define _TankFactory

#include <list>
#include "AzulCore.h"
#include "TankControlTypes.h"

class Tank;
class TankController;

class TankFactory
{
	typedef std::list<Tank*> StorageContainer;

private:
	static TankFactory* pInstance;

	TankFactory() = default;
	TankFactory(const TankFactory&) = delete;
	TankFactory& operator=(const TankFactory&) = delete;
	TankFactory(TankFactory&&) = delete;
	TankFactory& operator=(TankFactory&&) = delete;
	~TankFactory();

	static TankFactory& GetInstance();

	// Tank Creation/Recycle
	Tank* privCreateTank(TankControlType, Tank* pTarget, const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);
	TankController* getTankController(TankControlType) const;
	void privRecycleTank(Tank*);
	void privRecallActiveTanks();

public:
	static Tank* CreateTank(TankControlType controlType, Tank* pTarget, const Vect& position)
	{
		return GetInstance().privCreateTank(controlType, pTarget, position);
	}

	static Tank* CreateTank(TankControlType controlType, const Vect& position)
	{
		return GetInstance().privCreateTank(controlType, nullptr, position);
	}

	static void RecycleTank(Tank* pTank)
	{
		GetInstance().privRecycleTank(pTank);
	}

	static void Termintate();

	static void RecallActiveTanks()
	{
		GetInstance().privRecallActiveTanks();
	}

	static int NumberOfActiveTanks()
	{
		return GetInstance()._activeTanks.size();
	}

private:
	StorageContainer _activeTanks;
};
#endif // !_TankFactory

//-----------------------------------------------------------------------------------------------------------------------------
// TankFactory Comment Template
//-----------------------------------------------------------------------------------------------------------------------------