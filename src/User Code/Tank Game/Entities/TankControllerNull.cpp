#include "TankControllerNull.h"
#include "Tank.h"
#include "TankControllerNullFactory.h"

const TankControlType TankControllerNull::CONTROL_TYPE = TankControlType::NULL_CONTROL;

void TankControllerNull::initialize()
{
	// Does Nothing
}

void TankControllerNull::deinitialize()
{
	TankControllerNullFactory::RecycleController(this);
}

void TankControllerNull::setTankToControl(Tank* pTank)
{
	pTank->setControlType(TankControllerNull::CONTROL_TYPE);
}
