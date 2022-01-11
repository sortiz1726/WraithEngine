#ifndef _Bullet
#define _Bullet

#include "GameObject.h"

class Tank;
class Turret;
class Warehouse;
class WindMill;
class Cottage;
class LeaflessTree;
class DebugRegistrationCube;
class Wall;
class RoundArch;
class FlatArch;

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const Bullet&) = default;
	Bullet& operator=(const Bullet&) = default;
	Bullet(Bullet&&) = default;
	Bullet& operator=(Bullet&&) = default;
	~Bullet();

	void initialize(const Vect& position, float rotation, float scale = 1.0f);
	void initialize(const Vect& position, const Matrix& rotation, float scale = 1.0f);
	void updateBulletWorldMatrix();

	// Collision
	void collision(Tank*);
	void collision(Turret*);
	void collision(DebugRegistrationCube*) { Trace::out("Bullet_collision: Cube Collided with me \n"); }
	void collision(Bullet*);
	void collision(Warehouse*);
	void collision(WindMill*);
	void collision(Cottage*);
	void collision(LeaflessTree*);
	void collision(Wall*);
	void collision(RoundArch*);
	void collision(FlatArch*);

	virtual void terrainCollision() override;
	
	// Setter/Getters

	// ---> Bullet Properties
	void setDamage(float damage);
	void setTankOwner(Tank*);
	void setSpeed(float speed);
	float getSpeed() const;

	// ---> World Properties
	void setBulletPosition(const Vect& position);
	Vect getBulletPosition() const;

	void setBulletScale(float scale);
	
	void setBulletRotation(float rotation);
	void setBulletRotation(const Matrix& rotation);
	
private:
	virtual void update() override;
	virtual void draw() override;
	virtual void alarm0() override;
	
	virtual void sceneEntry() override;
	virtual void sceneExit() override;

	// --> Update helper
	void moveForward();

private:
	static const float MAX_LIFESPAN;
	static const float ADJUSTED_SCALE;
	
	// Bullet Properties
	float _speed;
	float _damage;
	Tank* _pTankOwner;

	// internals
	GraphicsObject_TextureLight* _pBulletGraphicsObject;

	Vect _localPosition;
	Matrix _localRotation;
	Matrix _localScale;

	bool _hasCollidedDebug;

};
#endif // !_Bullet

//-----------------------------------------------------------------------------------------------------------------------------
// Bullet Comment Template
//-----------------------------------------------------------------------------------------------------------------------------