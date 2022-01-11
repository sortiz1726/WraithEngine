#ifndef _TankController
#define _TankController

#include "GameObject.h"

class Tank;

class TankController
{
public:
	TankController() = default;
	TankController(const TankController&) = default;
	TankController& operator=(const TankController&) = default;
	TankController(TankController&&) = default;
	TankController& operator=(TankController&&) = default;
	virtual ~TankController() = default;

	virtual void initialize() = 0;
	virtual void deinitialize() = 0;

	virtual void setTankToControl(Tank*) = 0;

};
#endif // !_TankController

//-----------------------------------------------------------------------------------------------------------------------------
// TankController Comment Template
//-----------------------------------------------------------------------------------------------------------------------------