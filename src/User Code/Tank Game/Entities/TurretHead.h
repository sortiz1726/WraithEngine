#ifndef _TurretHead
#define _TurretHead

#include "GameObject.h"

class TurretBase;

class TurretHead
{
public:
	TurretHead();
	TurretHead(const TurretHead&) = default;
	TurretHead& operator=(const TurretHead&) = default;
	TurretHead(TurretHead&&) = default;
	TurretHead& operator=(TurretHead&&) = default;
	// Is it a base class? Should it be virtual?
	~TurretHead();

	// Actions
	void turn(float turnValue);
	void turnTo(const Vect& target);
	void draw(Camera*);

	// Setters/Getters
	// ---> Properties
	void setTurnSpeed(float turnSpeed);
	void attachToTurretBase(TurretBase*);

	void setBulletSpawnOffset(const Vect& bulletSpawnOffset);
	Vect getBulletSpawnOffset() const;
	Vect getBulletSpawnLocation();


	Matrix getWorldRotationMatrix();

	// ---> Internals
	void setLocalPosition(const Vect& localPosition);
	Vect getLocalPosition() const;
	Matrix getLocalPositionMatrix() const;

	void setLocalRotation(const Vect& localRotation);
	Matrix getLocalRotationMatrix() const;

	void setLocalScale(const Vect& localScale);
	Vect getLocalScale() const;
	Matrix getLocalScaleMatrix() const;

	Matrix getLocalWorldMatrix() const;
	Matrix getWorldMatrix() const;
	void updateWorldMatrix();

private:
	void initializeTurretHeadGraphicsObject();

	// ---> Action helpers
	Matrix computeRotationMatrixTowards(const Vect& position) const;
	Vect computeDirectionTo(const Vect& position) const;
	float computeRotationAngle(const Vect&, const Vect&) const;
	float computeAngleBetween(const Vect&, const Vect&) const;

	Vect computeLocal(const Vect&) const;

private:
	// Properties
	float _turnSpeed;
	TurretBase* _pTurretBase;
	Vect _bulletSpawnOffset;

	// Internals
	GraphicsObject_TextureLight* _pTurretHeadGraphicsObject;

	Vect _localPosition;
	Matrix _localRotation;
	Vect _localScale;

};
#endif // !_TurretHead

//-----------------------------------------------------------------------------------------------------------------------------
// TurretHead Comment Template
//-----------------------------------------------------------------------------------------------------------------------------