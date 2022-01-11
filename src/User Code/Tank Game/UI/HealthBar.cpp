#include "HealthBar.h"
#include "Wraith.h"
#include "Damagable.h"
#include "Sprite.h"

HealthBar::HealthBar(Damagable* pDamagable)
	: _pBackgroundBarSprite(nullptr), _pHealthBarSprite(nullptr),
	_pDamagable(pDamagable)
{
	_pBackgroundBarSprite = new Sprite("BlackImage");
	_pHealthBarSprite = new Sprite("RedImage");
	_pHealthHeartSprite = new Sprite("HealthImage");

	setWidthAndHeight(100.0f, 15.0f);
	setUniformScale(2.0f);
	setPosition(Wraith::GetWindowWidth() - getImageWidth() - 10.0f, 30.0f);

	submitDraw2DRegistration();
	submitUpdateRegistration();
}

HealthBar::~HealthBar()
{
	delete _pHealthBarSprite;
	delete _pBackgroundBarSprite;
	delete _pHealthHeartSprite;
}

void HealthBar::setDamagable(Damagable* pDamagable)
{
	assert(pDamagable != nullptr);
	_pDamagable = pDamagable;
}

void HealthBar::setWidthAndHeight(float width, float height)
{
	_width = width;
	_height = height;

	updateHealthSprite();
}

float HealthBar::getOriginalWidth() const
{
	return _width;
}

float HealthBar::getImageWidth() const
{
	return getOriginalWidth() * _uniformScale;
}

void HealthBar::setPosition(float positionX, float positionY)
{
	_positionX = positionX;
	_positionY = positionY;

	updateHealthSprite();
}

void HealthBar::setUniformScale(float uniformScale)
{
	_uniformScale = uniformScale;
	updateHealthSprite();
}

void HealthBar::update()
{
	updateHealthSprite();
}

void HealthBar::updateHealthSprite()
{
	_pBackgroundBarSprite->setScaleFactor(_uniformScale, _uniformScale);
	_pHealthBarSprite->setScaleFactor(_uniformScale, _uniformScale);
	_pHealthHeartSprite->setScaleFactor(_uniformScale, _uniformScale);

	float healthPercentage = _pDamagable->getHealthPercentage();
	_pBackgroundBarSprite->setScalePixel(_width, _height);
	_pHealthBarSprite->setScalePixel(_width * healthPercentage, _height);
	_pHealthHeartSprite->setScalePixel(_height * 1.5f, _height * 1.5f);

	_pBackgroundBarSprite->setCenter(-_pBackgroundBarSprite->getWidth() / 2.0f, 0.0f);
	_pHealthBarSprite->setCenter(-_pHealthBarSprite->getWidth() / 2.0f, 0.0f);

	_pBackgroundBarSprite->setPosition(_positionX, _positionY);
	_pHealthBarSprite->setPosition(_positionX, _positionY);
	_pHealthHeartSprite->setPosition(_positionX - _pHealthHeartSprite->getWidth() / 2.0f, _positionY);
}

void HealthBar::draw2D()
{
	_pBackgroundBarSprite->render();
	_pHealthBarSprite->render();
	_pHealthHeartSprite->render();
}