#include "Reticle.h"
#include "Wraith.h"
#include "Sprite.h"

Reticle::Reticle()
	: _pReticleSprite(nullptr)
{
	_pReticleSprite = new Sprite("TankReticleImage");
	_pReticleSprite->setScaleFactor(0.25f, 0.25f);
	_pReticleSprite->setPosition(Wraith::GetWindowWidth() * 0.5f, Wraith::GetWindowHeight() * 0.60f);
	submitDraw2DRegistration();
}

Reticle::~Reticle()
{
	delete _pReticleSprite;
}


void Reticle::draw2D()
{
	_pReticleSprite->render();
}