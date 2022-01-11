#ifndef _TankControllerPlayer
#define _TankControllerPlayer

#include <string>
#include "GameObject.h"
#include "TankController.h"
#include "TankControlTypes.h"

class TankControllerPlayer : public TankController, public GameObject
{
public:
	TankControllerPlayer() = default;
	TankControllerPlayer(const TankControllerPlayer&) = default;
	TankControllerPlayer& operator=(const TankControllerPlayer&) = default;
	TankControllerPlayer(TankControllerPlayer&&) = default;
	TankControllerPlayer& operator=(TankControllerPlayer&&) = default;
	~TankControllerPlayer() = default;

	// Inherited via TankController
	virtual void initialize() override;
	virtual void deinitialize() override;
	virtual void setTankToControl(Tank*) override;

private:
	virtual void update() override;
	virtual void keyPressed(AZUL_KEY) override;
	virtual void sceneEntry() override;
	virtual void sceneExit() override;

	// ---> Update helpers
	void screenLogTankPosition();
	void processHullInputs();
	float computeHullMoveOffset() const;
	float computeHullTurnOffset() const;

	void processTurretInputs();
	float computeTurretTurnOffset() const;

	// ---> Input Helpers
	void processBulletInputs(AZUL_KEY);

	// ---> Scene Exit/Entry Helper
	void registerKeyInputs();
	void deregisterKeyInputs();

private:
	static const TankControlType CONTROL_TYPE;

	static const AZUL_KEY	KEY_HULL_MOVE_FOWARD,
							KEY_HULL_MOVE_BACKWARD, 
							KEY_HULL_TURN_LEFT,
							KEY_HULL_TURN_RIGHT,
							KEY_TURRET_TURN_LEFT,
							KEY_TURRET_TURN_RIGHT,
							KEY_BULLET_FIRE,
							KEY_BULLET_RELOAD;

	Tank* _pTank;

};
#endif // !_TankControllerPlayer

//-----------------------------------------------------------------------------------------------------------------------------
// TankControllerPlayer Comment Template
//-----------------------------------------------------------------------------------------------------------------------------