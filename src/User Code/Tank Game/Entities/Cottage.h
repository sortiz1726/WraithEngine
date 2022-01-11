#ifndef _Cottage
#define _Cottage

#include "GameObject.h"

class Tank;
class Bullet;

class Cottage : public GameObject
{
public:
	Cottage();
	Cottage(const Cottage&) = default;
	Cottage& operator=(const Cottage&) = default;
	Cottage(Cottage&&) = default;
	Cottage& operator=(Cottage&&) = default;
	~Cottage();

	void initialize(const Vect& position , float rotationY = 0.0f, float uniformScale = 1.0f);
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

	void InitiailizeCottageGraphicsObject();
	
private:
	// Internals
	GraphicsObject_TextureLight* _pCottageGraphicsObject;

	Vect _localScale;
	Matrix _localRotation;
	Vect _localPosition;

	bool _hasCollidedDebug;

	static const float adjustedScale;
};
#endif // !_Cottage

//-----------------------------------------------------------------------------------------------------------------------------
// Cottage Comment Template
//-----------------------------------------------------------------------------------------------------------------------------