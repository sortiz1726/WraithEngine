#ifndef _BasicCar
#define _BasicCar

#include "GameObject.h"

class BasicCar : public GameObject
{
public:
	BasicCar();
	BasicCar(const BasicCar&) = default;
	BasicCar& operator=(const BasicCar&) = default;
	BasicCar(BasicCar&&) = default;
	BasicCar& operator=(BasicCar&&) = default;
	~BasicCar();

private:
	virtual void update() override;
	virtual void draw() override;

private:
	GraphicsObject_TextureFlat* _pCarGraphicsObject;
};
#endif // !_BasicCar

//-----------------------------------------------------------------------------------------------------------------------------
// BasicCar Comment Template
//-----------------------------------------------------------------------------------------------------------------------------