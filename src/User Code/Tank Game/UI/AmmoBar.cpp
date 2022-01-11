#include "AmmoBar.h"
#include "Tank.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"
#include "Sprite.h"

AmmoBar::AmmoBar()
	: _pTank(nullptr),
	_pBulletSprite(nullptr), _pAmmoStatus(nullptr),
	_screenPositionX(0.0f), _screenPositionY(0.0f)
{
	_pBulletSprite = new Sprite("BulletImage");
	float scaleFactor = 1.0f / 6.0f;
	_pBulletSprite->setScaleFactor(scaleFactor, scaleFactor);
	_pBulletSprite->setCenter(-_pBulletSprite->getWidth() / 2.0f, -_pBulletSprite->getHeight() / 2.0f);

	SpriteFont* _pFont = SpriteFontManager::GetSpriteFont("StencilWhiteFont");
	_pAmmoStatus = new SpriteString(_pFont, "RELOADING", 25, static_cast<int>(_pBulletSprite->getHeight() * (2.0f / 3.0f)));

	submitDraw2DRegistration();
}

AmmoBar::~AmmoBar()
{
	delete _pBulletSprite;
	delete _pAmmoStatus;
}

void AmmoBar::setScreenPosition(float screenPositionX, float screenPositionY)
{
	_screenPositionX = screenPositionX;
	_screenPositionY = screenPositionY;
}

void AmmoBar::setTank(Tank* pTank)
{
	_pTank = pTank;
}

void AmmoBar::draw2D()
{
	displayAmmoCount();
}

void AmmoBar::displayAmmoCount()
{
	if (_pTank == nullptr)
	{
		return;
	}

	if (_pTank->getBulletCount() <= 0)
	{
		_pAmmoStatus->render();
		return;
	}

	float screenPositionX = _screenPositionX;
	for (int i = 0; i < _pTank->getBulletCount(); i++)
	{
		_pBulletSprite->render();
		_pBulletSprite->setPosition(screenPositionX, _screenPositionY);
		screenPositionX += _pBulletSprite->getWidth();
	}
}
