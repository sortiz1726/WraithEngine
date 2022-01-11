#ifndef _TankControllerAISniper
#define _TankControllerAISniper

#include "GameObject.h"
#include "TankController.h"
#include "TankControlTypes.h"

class TankControllerAISniper : public TankController, public GameObject
{
public:
	TankControllerAISniper() = default;
	TankControllerAISniper(const TankControllerAISniper&) = default;
	TankControllerAISniper& operator=(const TankControllerAISniper&) = default;
	TankControllerAISniper(TankControllerAISniper&&) = default;
	TankControllerAISniper& operator=(TankControllerAISniper&&) = default;
	~TankControllerAISniper() = default;

	// Inherited via TankController
	virtual void initialize() override;
	virtual void deinitialize() override;
	virtual void setTankToControl(Tank*) override;

	void setFireDelay(float fireDelay);

private:
	virtual void update() override;
	virtual void alarm0() override;
	virtual void sceneEntry() override;
	virtual void sceneExit() override;

	// ---> Fire Bullet Alarm 0 helper
	void resetFireBulletAlarm();
	void cancelFireBulletAlarm();

	Vect computeAimPosition(const Vect& targetPosition, const Vect& targetVelocity, 
		const Vect& projectilePosition, const Vect& projectileVelocity) const;

private:
	static const TankControlType CONTROL_TYPE;

	Tank* _pTank;
	float _fireDelay;

};
#endif // !_TankControllerAISniper

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerAISniper Comment Template
//-----------------------------------------------------------------------------------------------------------------------------