#ifndef _Reticle
#define _Reticle

#include "GameObject.h"

class Sprite;

class Reticle : public GameObject
{
public:
	Reticle();
	Reticle(const Reticle&) = default;
	Reticle& operator=(const Reticle&) = default;
	Reticle(Reticle&&) = default;
	Reticle& operator=(Reticle&&) = default;
	~Reticle();

private:
	virtual void draw2D() override;

private:
	Sprite* _pReticleSprite;

};
#endif // !_Reticle

//-----------------------------------------------------------------------------------------------------------------------------
// Reticle Comment Template
//-----------------------------------------------------------------------------------------------------------------------------