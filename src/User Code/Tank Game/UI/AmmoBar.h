#ifndef _AmmoBar
#define _AmmoBar

#include "GameObject.h"

class Tank;
class Sprite;
class SpriteString;

class AmmoBar : public GameObject
{
public:
	AmmoBar();
	AmmoBar(const AmmoBar&) = default;
	AmmoBar& operator=(const AmmoBar&) = default;
	AmmoBar(AmmoBar&&) = default;
	AmmoBar& operator=(AmmoBar&&) = default;
	~AmmoBar();

	void setScreenPosition(float screenPositionX, float screenPositionY);
	void setTank(Tank*);

private:
	virtual void draw2D() override;

	void displayAmmoCount();

private:
	Tank* _pTank;
	Sprite* _pBulletSprite;
	SpriteString* _pAmmoStatus;

	float _screenPositionX;
	float _screenPositionY;

	int dummy = 3;
};
#endif // !_AmmoBar

//-----------------------------------------------------------------------------------------------------------------------------
// AmmoBar Comment Template
//-----------------------------------------------------------------------------------------------------------------------------