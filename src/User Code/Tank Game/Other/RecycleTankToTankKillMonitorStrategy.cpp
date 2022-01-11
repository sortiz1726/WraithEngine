#include "RecycleTankToTankKillMonitorStrategy.h"
#include "TankKillMonitor.h"

void RecycleTankToTankKillMonitorStrategy::recycle(Tank* pTank)
{
	_pTankKillMonitor->recycleDestroyedTank(pTank);
}

void RecycleTankToTankKillMonitorStrategy::setTankKillMonitor(TankKillMonitor* pTankKillMonitor)
{
	_pTankKillMonitor = pTankKillMonitor;
}
