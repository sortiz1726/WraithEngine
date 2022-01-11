#ifndef _TurretBase
#define _TurretBase

#include "GameObject.h"

class TurretBase
{
public:
	TurretBase();
	TurretBase(const TurretBase&) = default;
	TurretBase& operator=(const TurretBase&) = default;
	TurretBase(TurretBase&&) = default;
	TurretBase& operator=(TurretBase&&) = default;
	// Is it a base class? Should it be virtual?
	~TurretBase();

	void draw(Camera*);

	void setTurnSpeed(float turnSpeed);

	// ---> Internals
	Matrix getLocalWorldMatrix() const;
	Matrix getWorldMatrix() const;
	void updateWorldMatrix();

	void setLocalPosition(const Vect& localPosition);
	Vect getLocalPosition() const;
	Matrix getLocalPositionMatrix() const;

	void setLocalRotation(const Vect& localRotation);
	Matrix getLocalRotationMatrix() const;

	void setLocalScale(const Vect& localScale);
	Vect getLocalScale() const;
	Matrix getLocalScaleMatrix() const;

	Model* getModel() const;

private:
	void initializeTurretBaseGraphicsObject();

private:
	// Internals
	GraphicsObject_TextureLight* _pTurretBaseGraphicsObject;

	Vect _localPosition;
	Matrix _localRotation;
	Vect _localScale;

};
#endif // !_TurretBase

//-----------------------------------------------------------------------------------------------------------------------------
// TurretBase Comment Template
//-----------------------------------------------------------------------------------------------------------------------------