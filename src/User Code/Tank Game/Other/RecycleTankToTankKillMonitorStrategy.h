#ifndef _RecycleTankToTankKillMonitorStrategy
#define _RecycleTankToTankKillMonitorStrategy

#include "RecycleTankStrategy.h"

class TankKillMonitor;

class RecycleTankToTankKillMonitorStrategy : public RecycleTankStrategy
{
public:
	RecycleTankToTankKillMonitorStrategy() = default;
	RecycleTankToTankKillMonitorStrategy(const RecycleTankToTankKillMonitorStrategy&) = default;
	RecycleTankToTankKillMonitorStrategy& operator=(const RecycleTankToTankKillMonitorStrategy&) = default;
	RecycleTankToTankKillMonitorStrategy(RecycleTankToTankKillMonitorStrategy&&) = default;
	RecycleTankToTankKillMonitorStrategy& operator=(RecycleTankToTankKillMonitorStrategy&&) = default;
	~RecycleTankToTankKillMonitorStrategy() = default;

	// Inherited via RecycleTankStrategy
	virtual void recycle(Tank*) override;

	void setTankKillMonitor(TankKillMonitor*);

private:
	TankKillMonitor* _pTankKillMonitor;
};

#endif // !_RecycleTankToTankKillMonitorStrategy

//-----------------------------------------------------------------------------------------------------------------------------
// RecycleTankToTankKillMonitorStrategy Comment Template
//-----------------------------------------------------------------------------------------------------------------------------