#ifndef _AlarmCar
#define _AlarmCar

#include "GameObject.h"

class AlarmCar : public GameObject
{
public:
	AlarmCar();
	AlarmCar(const AlarmCar&) = default;
	AlarmCar& operator=(const AlarmCar&) = default;
	AlarmCar(AlarmCar&&) = default;
	AlarmCar& operator=(AlarmCar&&) = default;
	~AlarmCar();

private:
	virtual void draw() override;

	virtual void alarm0() override;
	virtual void alarm1() override;
	virtual void alarm2() override;

private:
	GraphicsObject_TextureFlat* _pCarGraphicsObject;
};
#endif // !_AlarmCar

//-----------------------------------------------------------------------------------------------------------------------------
// AlarmCar Comment Template
//-----------------------------------------------------------------------------------------------------------------------------