#ifndef _Wall
#define _Wall

#include "GameObject.h"

class Tank;
class Bullet;

class Wall : public GameObject
{
public:
	Wall();
	Wall(const Wall&) = default;
	Wall& operator=(const Wall&) = default;
	Wall(Wall&&) = default;
	Wall& operator=(Wall&&) = default;
	~Wall();

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

	void InitiailizeWallGraphicsObject();
	
private:
	// Internals
	GraphicsObject_TextureLight* _pWallGraphicsObject;

	Vect _localScale;
	Matrix _localRotation;
	Vect _localPosition;

	bool _hasCollidedDebug;

	static const float adjustedScale;
};
#endif // !_Wall

//-----------------------------------------------------------------------------------------------------------------------------
// Wall Comment Template
//-----------------------------------------------------------------------------------------------------------------------------