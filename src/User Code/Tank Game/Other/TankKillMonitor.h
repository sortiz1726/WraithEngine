#ifndef _TankKillMonitor
#define _TankKillMonitor

#include "GameObject.h"
#include "ObjectiveMonitor.h"
#include "RecycleTankToTankKillMonitorStrategy.h"

class Tank;
class TankSpawner;
class Scene;
class SceneSwitcher;
class SpriteString;

class TankKillMonitor : public GameObject, public ObjectiveMonitor
{
public:
	TankKillMonitor();
	TankKillMonitor(const TankKillMonitor&) = default;
	TankKillMonitor& operator=(const TankKillMonitor&) = default;
	TankKillMonitor(TankKillMonitor&&) = default;
	TankKillMonitor& operator=(TankKillMonitor&&) = default;
	~TankKillMonitor();

	void setTarget(Tank*);
	void createTankSpawnerAt(const Vect& position);

	void setLeftToKill(int leftToKill);
	void offsetLeftToKill(int offsetLeftToKill);

	void setMaxNumberOfEnemyTanks(int maxNumberOfEnemyTanks);

	void recycleDestroyedTank(Tank*);

	void setDrawText(bool);

private:
	virtual void update() override;
	virtual void draw2D() override;
	virtual void alarm0() override;

	bool canSpawnTanks() const;
	void spawnTanks();
	void spawnTankUsing(TankSpawner*);

private:
	static const int MAX_NUMBER_OF_ENEMY_TANKS;

	Tank* _pTarget;

	int _leftToKill;
	SpriteString* _pLeftToKillCounter;
	int _numberOfActiveEnemyTanks;

	std::vector<TankSpawner*> _tankSpawners;
	int _maxNumberOfEnemyTanks;

	RecycleTankToTankKillMonitorStrategy _recycleTankStategy;

	bool _drawText;
};
#endif // !_TankKillMonitor

//-----------------------------------------------------------------------------------------------------------------------------
// TankKillMonitor Comment Template
//-----------------------------------------------------------------------------------------------------------------------------