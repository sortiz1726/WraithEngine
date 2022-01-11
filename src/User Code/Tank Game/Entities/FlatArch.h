#ifndef _FlatArch
#define _FlatArch

#include "GameObject.h"

class Tank;
class Bullet;

class FlatArch : public GameObject
{
public:
	FlatArch();
	FlatArch(const FlatArch&) = default;
	FlatArch& operator=(const FlatArch&) = default;
	FlatArch(FlatArch&&) = default;
	FlatArch& operator=(FlatArch&&) = default;
	~FlatArch();

	void initialize(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);
	void initialize(const Vect& position, const Vect& rotation, const Vect& scale);

	void collision(Tank*);
	void collision(Bullet*);

private:
	virtual void draw() override;

	// Setters/Getters
	void setLocalScale(const Vect& localScale);
	Vect getLocalScale() const;
	Matrix getLocalScaleMatrix() const;

	void setLocalRotation(const Vect& localRotation);
	Matrix getLocalRotationMatrix() const;

	void setLocalPosition(const Vect& localPosition);
	Vect getLocalPosition() const;
	Matrix getLocalPositionMatrix() const;

	void InitiailizeFlatArchGraphicsObject();

private:
	// Internals
	GraphicsObject_TextureLight* _pFlatArchGraphicsObject;

	Vect _localScale;
	Matrix _localRotation;
	Vect _localPosition;

	bool _hasCollidedDebug;

};
#endif // !_FlatArch

//-----------------------------------------------------------------------------------------------------------------------------
// FlatArch Comment Template
//-----------------------------------------------------------------------------------------------------------------------------