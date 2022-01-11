#ifndef _TankControllerAI
#define _TankControllerAI

#include "GameObject.h"
#include "TankController.h"
#include "TankControlTypes.h"

class TankControllerAI : public TankController, public GameObject
{
public:
	TankControllerAI() = default;
	TankControllerAI(const TankControllerAI&) = default;
	TankControllerAI& operator=(const TankControllerAI&) = default;
	TankControllerAI(TankControllerAI&&) = default;
	TankControllerAI& operator=(TankControllerAI&&) = default;
	~TankControllerAI() = default;

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
#endif // !_TankControllerAI

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerAI Comment Template
//-----------------------------------------------------------------------------------------------------------------------------