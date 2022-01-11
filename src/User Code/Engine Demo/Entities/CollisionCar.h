#ifndef _CollisionCar
#define _CollisionCar

#include "GameObject.h"

class OtherCollisionCar;

class CollisionCar : public GameObject
{
public:
	CollisionCar();
	CollisionCar(const CollisionCar&) = default;
	CollisionCar& operator=(const CollisionCar&) = default;
	CollisionCar(CollisionCar&&) = default;
	CollisionCar& operator=(CollisionCar&&) = default;
	~CollisionCar();

	void collision(OtherCollisionCar*);

private:
	virtual void update() override;
	virtual void draw() override;

private:
	GraphicsObject_TextureFlat* _pCarGraphicsObject;

	bool _hasCollidedDebug;
};
#endif // !_CollisionCar

//-----------------------------------------------------------------------------------------------------------------------------
// CollisionCar Comment Template
//-----------------------------------------------------------------------------------------------------------------------------