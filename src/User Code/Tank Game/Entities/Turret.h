#ifndef _Turret
#define _Turret

#include "GameObject.h"
#include "Damagable.h"

class TurretBase;
class TurretHead;

class Bullet;
class Tank;

class Turret : public GameObject, public Damagable
{
public:
	Turret();
	Turret(const Turret&) = default;
	Turret& operator=(const Turret&) = default;
	Turret(Turret&&) = default;
	Turret& operator=(Turret&&) = default;
	// Is it a base class? Should it be virtual?
	~Turret();

	void initialize(const Vect& position, float rotation = 0.0f, float scale = 1.0f);

	void turnTurret(float turnValue);
	void turnToTarget();
	void turnTo(const Vect& target);
	void fireBullet();
	virtual void applyDamage(float damage) override;

	void setTarget(Tank* target);

	void offsetHealth(float healthOffset);
	void setHealth(float health);
	float getHealth() const;
	// ---> Inherited via Damagable
	virtual float getHealthPercentage() const override;

	void setBulletDamage(float bulletDamage);

	// ---> Inherited via Damagable
	virtual void setDestroyMonitor(DestroyMonitor*) override {};

	// ---> World Properties
	Matrix getWorldMatrix() const;

	void setTurretPosition(const Vect& position);
	Vect getTurretPosition() const;

	void setTurretRotation(float rotation);

	void setTurretScale(float scale);
	float getScale() const;

	//void collision(Tank*);
	void collision(Bullet*);

private:
	virtual void update() override;
	virtual void draw() override;
	virtual void alarm1() override;

	void updateTurretWorldMatrix();

	virtual void sceneEntry() override;
	virtual void sceneExit() override;

	// ---> Action helpers
	Vect getBulletSpawnLocation() const;
	Matrix getBulletSpawnRotation() const;

	void initializeTurretParts();

private:
	static const float MAX_HEALTH;
	Tank* _pTarget;
	float _health;
	int _bulletCount;
	float _bulletDamage;

	// Turret Components
	TurretHead* _pTurretHead;
	TurretBase* _pTurretBase;

	bool _hasCollidedDebug;
	bool _canFire;

};
#endif // !_Turret

//-----------------------------------------------------------------------------------------------------------------------------
// Turret Comment Template
//-----------------------------------------------------------------------------------------------------------------------------