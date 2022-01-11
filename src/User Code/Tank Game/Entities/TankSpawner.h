#ifndef _TankSpawner
#define _TankSpawner

#include "Vect.h"

class Tank;

class TankSpawner
{
public:
	TankSpawner() = default;
	TankSpawner(const TankSpawner&) = default;
	TankSpawner& operator=(const TankSpawner&) = default;
	TankSpawner(TankSpawner&&) = default;
	TankSpawner& operator=(TankSpawner&&) = default;
	~TankSpawner() = default;

	Tank* spawnCharger();
	Tank* spawnSniper();

	void setTarget(Tank*);
	void setPosition(const Vect& position);

	const Vect& getPosition() const;

private:
	Tank* _pTarget;

	Vect _position;
};
#endif // !_TankSpawner

//-----------------------------------------------------------------------------------------------------------------------------
// TankSpawner Comment Template
//-----------------------------------------------------------------------------------------------------------------------------