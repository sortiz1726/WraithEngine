#ifndef _TankTurret
#define _TankTurret

#include "GameObject.h"

class TankHull;

class TankTurret
{
public:
	TankTurret();
	TankTurret(const TankTurret&) = default;
	TankTurret& operator=(const TankTurret&) = default;
	TankTurret(TankTurret&&) = default;
	TankTurret& operator=(TankTurret&&) = default;
	~TankTurret();

	// Actions
	void turn(float turnValue);
	void turnTo(const Vect& target);
	void draw(Camera*);

	// Setters/Getters
	// ---> Properties
	void setTurnSpeed(float turnSpeed);
	void attachToTankHull(TankHull*);

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
	void initializeTankTurretGraphicsObject();
	
	// ---> Action helpers
	Matrix computeRotationMatrixTowards(const Vect& position) const;
	Vect computeDirectionTo(const Vect& position) const;
	float computeRotationAngle(const Vect&, const Vect&) const;
	float computeAngleBetween(const Vect&, const Vect&) const;

	Vect computeLocal(const Vect&) const;

private:
	// Properties
	float _turnSpeed;
	TankHull* _pTankHull;

	// Internals
	GraphicsObject_TextureLight* _pTankTurretGraphicsObject;

	Vect _localPosition;
	Matrix _localRotation;
	Vect _localScale;

};
#endif // !_TankTurret

//-----------------------------------------------------------------------------------------------------------------------------
// TankTurret Comment Template
//-----------------------------------------------------------------------------------------------------------------------------