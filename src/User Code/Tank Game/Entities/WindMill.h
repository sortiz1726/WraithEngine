#ifndef _WindMill
#define _WindMill

#include "GameObject.h"

class Tank;
class Bullet;

class WindMill : public GameObject
{
public:
	WindMill();
	WindMill(const WindMill&) = default;
	WindMill& operator=(const WindMill&) = default;
	WindMill(WindMill&&) = default;
	WindMill& operator=(WindMill&&) = default;
	~WindMill();

	void initialize(const Vect& position , float rotationY = 0.0f, float uniformScale = 1.0f);
	void initialize(const Vect& position, const Vect& rotation, const Vect& scale);

	void collision(Tank*);
	void collision(Bullet*);

private:
	virtual void draw() override;

	virtual void keyPressed(AZUL_KEY) override;

	// Setters/Getters
	void setLocalScale(const Vect& localScale);
	Vect getLocalScale() const;
	Matrix getLocalScaleMatrix() const;

	void setLocalRotation(const Vect& localRotation);
	Matrix getLocalRotationMatrix() const;

	void setLocalPosition(const Vect& localPosition);
	Vect getLocalPosition() const;
	Matrix getLocalPositionMatrix() const;

	void InitiailizeWindMillGraphicsObject();
	
private:
	// Internals
	GraphicsObject_TextureLight* _pWindMillGraphicsObject;

	Vect _localScale;
	Matrix _localRotation;
	Vect _localPosition;

	bool _hasCollidedDebug;

	int _renderLevel;

	static const float adjustedScale;
};
#endif // !_WindMill

//-----------------------------------------------------------------------------------------------------------------------------
// WindMill Comment Template
//-----------------------------------------------------------------------------------------------------------------------------