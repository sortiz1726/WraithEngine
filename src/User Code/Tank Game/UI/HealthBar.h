#ifndef _HealthBar
#define _HealthBar

#include "GameObject.h"

class Sprite;
class Damagable;

class HealthBar : public GameObject
{
public:
	HealthBar() = delete;
	HealthBar(const HealthBar&) = default;
	HealthBar& operator=(const HealthBar&) = default;
	HealthBar(HealthBar&&) = default;
	HealthBar& operator=(HealthBar&&) = default;
	~HealthBar();

	HealthBar(Damagable*);

	void setDamagable(Damagable*);

	void setWidthAndHeight(float width, float height);
	float getOriginalWidth() const;
	float getImageWidth() const;

	void setPosition(float positionX, float positionY);
	void setUniformScale(float uniformScale);

private:
	virtual void update() override;
	virtual void draw2D() override;

	void updateHealthSprite();

private:
	Sprite* _pBackgroundBarSprite;
	Sprite* _pHealthBarSprite;
	Sprite* _pHealthHeartSprite;

	Damagable* _pDamagable;
	// Internals
	float _width;
	float _height;

	float _positionX;
	float _positionY;

	float _uniformScale;
};
#endif // !_HealthBar

//-----------------------------------------------------------------------------------------------------------------------------
// HealthBar Comment Template
//-----------------------------------------------------------------------------------------------------------------------------