#ifndef _TankControllerNull
#define _TankControllerNull

#include "TankController.h"
#include "TankControlTypes.h"

class TankControllerNull : public TankController
{
public:
	TankControllerNull() = default;
	TankControllerNull(const TankControllerNull&) = default;
	TankControllerNull& operator=(const TankControllerNull&) = default;
	TankControllerNull(TankControllerNull&&) = default;
	TankControllerNull& operator=(TankControllerNull&&) = default;
	~TankControllerNull() = default;

	// Inherited via TankController
	virtual void initialize() override;
	virtual void deinitialize() override;
	virtual void setTankToControl(Tank*) override;

private:
	static const TankControlType CONTROL_TYPE;
};
#endif // !_TankControllerNull

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerNull Comment Template
//-----------------------------------------------------------------------------------------------------------------------------