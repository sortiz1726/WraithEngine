#include "SpriteWorldModifierStrategy.h"
#include "SpriteAttorney.h"

void SpriteWorldModifierStrategy::modify(Sprite* pSprite)
{
	SpriteAttorney::UpdateAccess::UpdateWorld(pSprite);
}
