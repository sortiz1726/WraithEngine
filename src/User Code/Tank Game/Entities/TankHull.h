#ifndef _TankHull
#define _TankHull

#include "GameObject.h"

class TankHull
{
public:
	TankHull();
	TankHull(const TankHull&) = default;
	TankHull& operator=(const TankHull&) = default;
	TankHull(TankHull&&) = default;
	TankHull& operator=(TankHull&&) = default;
	~TankHull();

	// Actions
	void move(const Vect& direction);
	void turn(float turnValue);
	void turnTo(const Vect& target);
	void draw(Camera*);

	// Setters/Getters
	// ---> Properties
	void setMoveSpeed(float moveSpeed);
	void setTurnSpeed(float turnSpeed);

	// ---> Internals
	Matrix getLocalWorldMatrix() const;
	Matrix getWorldMatrix() const;
	void updateWorldMatrix();
	
	void setLocalPosition(const Vect& localPosition);
	Vect getLocalPosition() const;
	Matrix getLocalPositionMatrix() const;

	void setLocalRotation(const Vect& localRotation);
	void setUpAxis(const Vect& axis);
	Matrix getLocalRotationMatrix() const;
	
	void setLocalScale(const Vect& localScale);
	Vect getLocalScale() const;
	Matrix getLocalScaleMatrix() const;

	Model* getModel() const;

private:
	void initializeTankHullGraphicsObject();
	
	// ---> Action helpers
	Matrix computeRotationMatrixTowards(const Vect& position) const;
	Vect computeDirectionTo(const Vect& position) const;
	float computeRotationAngle(const Vect&, const Vect&) const;
	float computeAngleBetween(const Vect&, const Vect&) const;

	Vect computeLocal(const Vect&) const;

private:
	// Properties
	float _moveSpeed;
	float _turnSpeed;

	// Internals
	GraphicsObject_TextureLight* _pTankHullGraphicsObject;
	
	Vect _localPosition;
	Matrix _localRotation;
	Matrix _rotationAxis;
	Vect _localScale;
};
#endif // !_TankHull

//-----------------------------------------------------------------------------------------------------------------------------
// TankHull Comment Template
//-----------------------------------------------------------------------------------------------------------------------------