#ifndef _OtherCollisionCar
#define _OtherCollisionCar

#include "GameObject.h"

class CollisionCar;

class OtherCollisionCar : public GameObject
{
public:
	OtherCollisionCar();
	OtherCollisionCar(const OtherCollisionCar&) = default;
	OtherCollisionCar& operator=(const OtherCollisionCar&) = default;
	OtherCollisionCar(OtherCollisionCar&&) = default;
	OtherCollisionCar& operator=(OtherCollisionCar&&) = default;
	~OtherCollisionCar();

	void collision(CollisionCar*);

private:
	virtual void draw() override;

private:
	GraphicsObject_TextureFlat* _pCarGraphicsObject;

	bool _hasCollidedDebug;
};
#endif // !_OtherCollisionCar

//-----------------------------------------------------------------------------------------------------------------------------
// OtherCollisionCar Comment Template
//-----------------------------------------------------------------------------------------------------------------------------