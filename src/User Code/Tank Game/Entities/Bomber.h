#ifndef _Bomber
#define _Bomber

#include "GameObject.h"

class Tank;

class Bomber : public GameObject
{
public:
	Bomber();
	Bomber(const Bomber&) = default;
	Bomber& operator=(const Bomber&) = default;
	Bomber(Bomber&&) = default;
	Bomber& operator=(Bomber&&) = default;
	~Bomber();

	void setTarget(Tank* pTarget);
	void setTimer(float timer);

private:
	virtual void update() override;
	virtual void draw() override;
	virtual void alarm0();

	void aquirePosition(const Vect& position);
	void fire();

private:
	Tank* _pTarget;
	Vect _targetPosition;
	GraphicsObject_TextureFlat* _pTargetGraphicsObject;
	float _timer;
};
#endif // !_Bomber

//-----------------------------------------------------------------------------------------------------------------------------
// Bomber Comment Template
//-----------------------------------------------------------------------------------------------------------------------------