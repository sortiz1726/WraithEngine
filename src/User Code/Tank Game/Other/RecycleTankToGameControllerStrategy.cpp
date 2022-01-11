#include "RecycleTankToGameControllerStrategy.h"
#include "GameController.h"

void RecycleTankToGameControllerStrategy::recycle(Tank*)
{
	//_pGameController->recycleDestroyedTank(pTank);
}

void RecycleTankToGameControllerStrategy::setGameController(GameController* pGameController)
{
	_pGameController = pGameController;
}
