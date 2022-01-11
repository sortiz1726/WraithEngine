#ifndef _TankBarrel
#define _TankBarrel

#include "GameObject.h"

class TankTurret;

class TankBarrel
{
public:
	TankBarrel();
	TankBarrel(const TankBarrel&) = default;
	TankBarrel& operator=(const TankBarrel&) = default;
	TankBarrel(TankBarrel&&) = default;
	TankBarrel& operator=(TankBarrel&&) = default;
	~TankBarrel();

	// Actions
	//void elevate(float elevateValue);
	void draw(Camera*);

	// Setters/Getters
	// ---> Properties
	void setElevationSpeed(float elevationSpeed);
	void attachToTankTurret(TankTurret*);

	void setBulletSpawnOffset(const Vect& bulletSpawnOffset);
	Vect getBulletSpawnOffset() const;
	Vect getBulletSpawnLocation();

	Matrix getWorldRotationMatrix() const;

	// ---> Internals
	void setLocalPosition(const Vect& localPosition);
	Vect getLocalPosition() const;
	Matrix getLocalPositionMatrix() const;

	void setLocalRotation(const Vect& localRotation);
	Vect getLocalRotation() const;
	Matrix getLocalRotationMatrix() const;

	void setLocalScale(const Vect& localScale);
	Vect getLocalScale() const;
	Matrix getLocalScaleMatrix() const;

	Matrix getLocalWorldMatrix() const;
	Matrix getWorldMatrix() const;
	void updateWorldMatrix();

private:
	// ---> Action helpers
	Vect computeLocal(const Vect&);

private:
	// Properties
	float _elevationSpeed;

	Vect _bulletSpawnOffset;
	TankTurret* _pTankTurret;

	// Internals
	GraphicsObject_TextureLight* _pTankBarrelGraphicsObject;

	Vect _localPosition;
	Vect _localRotation;
	Vect _localScale;
};
#endif // !_TankBarrel

//-----------------------------------------------------------------------------------------------------------------------------
// TankBarrel Comment Template
//-----------------------------------------------------------------------------------------------------------------------------