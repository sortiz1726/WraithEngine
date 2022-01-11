#include "SpriteAttorney.h"
#include "Sprite.h"

void SpriteAttorney::UpdateAccess::UpdateWorld(Sprite* pSprite)
{
	pSprite->updateWorld();
}