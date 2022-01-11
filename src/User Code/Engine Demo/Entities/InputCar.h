#ifndef _InputCar
#define _InputCar

#include "GameObject.h"

class InputCar : public GameObject
{
public:
	InputCar();
	InputCar(const InputCar&) = default;
	InputCar& operator=(const InputCar&) = default;
	InputCar(InputCar&&) = default;
	InputCar& operator=(InputCar&&) = default;
	~InputCar();

private:
	virtual void draw() override;

	virtual void keyPressed(AZUL_KEY) override;
	virtual void keyReleased(AZUL_KEY) override;

private:
	GraphicsObject_TextureFlat* _pCarGraphicsObject;
};
#endif // !_InputCar

//-----------------------------------------------------------------------------------------------------------------------------
// InputCar Comment Template
//-----------------------------------------------------------------------------------------------------------------------------