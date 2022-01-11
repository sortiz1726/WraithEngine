#ifndef _SpriteWorldModifierStrategy
#define _SpriteWorldModifierStrategy

#include "SpriteModifierStrategy.h"

/**********************************************************************************************//**
 * <summary> A sprite world modifier strategy.</summary>
 *
 * <remarks> Modifies Sprite world matrix. </remarks>
 **************************************************************************************************/
class SpriteWorldModifierStrategy : public SpriteModifierStrategy
{
public:
	SpriteWorldModifierStrategy() = default;
	SpriteWorldModifierStrategy(const SpriteWorldModifierStrategy&) = default;
	SpriteWorldModifierStrategy& operator=(const SpriteWorldModifierStrategy&) = default;
	SpriteWorldModifierStrategy(SpriteWorldModifierStrategy&&) = default;
	SpriteWorldModifierStrategy& operator=(SpriteWorldModifierStrategy&&) = default;
	~SpriteWorldModifierStrategy() = default;

	// Inherited via SpriteModifierStrategy

	/**********************************************************************************************//**
	 * <summary> Modifies the given Sprite's World.</summary>
	 *
	 * <remarks> Called ONLY by Sprite::render(). </remarks>
	 *
	 * <param name="pSprite"> A Sprite pointer.</param>
	 **************************************************************************************************/
	virtual void modify(Sprite* pSprite) override;

};
#endif // !_SpriteWorldModifierStrategy

//-----------------------------------------------------------------------------------------------------------------------------
// SpriteWorldModifierStrategy Comment Template
//-----------------------------------------------------------------------------------------------------------------------------