#include "RecycleTankToFactoryStrategy.h"
#include "TankFactory.h"

void RecycleTankToFactoryStrategy::recycle(Tank* pTank)
{
	TankFactory::RecycleTank(pTank);
}
