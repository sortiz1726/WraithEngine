#ifndef _Tank
#define _Tank

#include "TankControlTypes.h"
#include "GameObject.h"
#include "Damagable.h"

class TankHull;
class TankTurret;
class TankBarrel;
class TankController;
class RecycleTankStrategy;
class Camera;

#pragma region Collision Foward Declarations

class Bullet;
class Warehouse;
class WindMill;
class Cottage;
class LeaflessTree;
class DebugRegistrationCube;
class Marker;
class Wall;
class RoundArch;

#pragma endregion

class Tank : public GameObject, public Damagable
{
public:
	Tank();
	Tank(const Tank&) = default;
	Tank& operator=(const Tank&) = default;
	Tank(Tank&&) = default;
	Tank& operator=(Tank&&) = default;
	~Tank();

	void initialize(TankController*, const Vect& position, float rotation = 0.0f, float scale = 1.0f);

	// Actions
	void move(float moveValue);
	void turnHull(float turnValue);
	void turnTurret(float turnValue);
	void turnToTarget();
	void turnTo(const Vect& target);
	void fireBullet();
	// ---> Inherited via Damagable
	virtual void applyDamage(float damage) override;
	void reloadBullets();

	// Set Tank Properties
	void setTarget(Tank* target);
	Tank* getTarget() const;
	void setController(TankController*);
	void setControlType(TankControlType);

	void setMoveSpeed(float moveSpeed);
	const Vect& getVelocity() const;
	void setBulletSpeed(float bulletSpeed);
	float getBulletSpeed() const;

	void offsetHealth(float healthOffset);
	void setHealth(float health);
	float getHealth() const;
	// ---> Inherited via Damagable
	virtual float getHealthPercentage() const override;

	void setBulletDamage(float bulletDamage);
	void setBulletCount(int bulletCount);
	int getBulletCount() const;

	// ---> Inherited via Damagable
	virtual void setDestroyMonitor(DestroyMonitor*) override {};

	// ---> World Properties
	Matrix getWorldMatrix() const;

	void setTankPosition(const Vect& position);
	Vect getTankPosition() const;

	void setTankRotation(float rotation);
	void setTankUpAxis(const Vect& axis);

	void setTankScale(float scale);
	float getScale() const;

	Camera* getThirdPersonCamera() const;

	void setRecycleStrategy(RecycleTankStrategy*);

	void collision(Tank*);
	void collision(DebugRegistrationCube*) { Trace::out("Tank_collision: Cube Collided with me \n"); }
	void collision(Bullet*);
	void collision(Warehouse*);
	void collision(WindMill*);
	void collision(Cottage*);
	void collision(RoundArch*);
	void collision(LeaflessTree*);
	void collision(Marker*) {};
	void collision(Wall*) {};
	virtual void terrainCollision() override;

private:
	virtual void update() override;
	virtual void draw() override;
	virtual void alarm1() override;

	void updateTankWorldMatrix();
	void updateTankCamera();

	virtual void sceneEntry() override;
	virtual void sceneExit() override;

	// ---> Action helpers
	Vect getBulletSpawnLocation() const;
	Matrix getBulletSpawnRotation() const;

	// ---> Initial helpers
	void initializeTankParts();
private:
	static const float MAX_HEALTH;
	static const float MAX_SPEED;
	static const int MAX_BULLET_COUNT;

	TankController* _pController;
	Tank* _pTarget;
	float _health;
	int _bulletCount;
	float _bulletDamage;
	float _bulletSpeed;
	Vect _velocity;

	// Tank Components
	TankHull* _pTankHull;
	TankTurret* _pTankTurret;
	TankBarrel* _pTankBarrel;

	// Camera
	Camera* _pThirdPersonCamera;
	Vect _cameraPositionOffset;
	Vect _cameraLookAtOffset;

	// Internal
	float _moveValue;
	bool _hasCollidedDebug;
	TankControlType _controlType;
	RecycleTankStrategy* _pRecycleStrategy;

};
#endif // !_Tank

//-----------------------------------------------------------------------------------------------------------------------------
// Tank Comment Template
//-----------------------------------------------------------------------------------------------------------------------------