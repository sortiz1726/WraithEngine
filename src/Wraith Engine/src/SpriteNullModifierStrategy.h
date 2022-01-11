#ifndef _SpriteNullModifierStrategy
#define _SpriteNullModifierStrategy

#include "SpriteModifierStrategy.h"

/**********************************************************************************************//**
 * <summary> A sprite null modifier strategy.</summary>
 *
 * <remarks> Modifies nothing. </remarks>
 **************************************************************************************************/
class SpriteNullModifierStrategy : public SpriteModifierStrategy
{
public:
	SpriteNullModifierStrategy() = default;
	SpriteNullModifierStrategy(const SpriteNullModifierStrategy&) = default;
	SpriteNullModifierStrategy& operator=(const SpriteNullModifierStrategy&) = default;
	SpriteNullModifierStrategy(SpriteNullModifierStrategy&&) = default;
	SpriteNullModifierStrategy& operator=(SpriteNullModifierStrategy&&) = default;
	~SpriteNullModifierStrategy() = default;

	// Inherited via SpriteModifierStrategy

	/**********************************************************************************************//**
	 * <summary> Modifies nothing on given Sprite's World.</summary>
	 *
	 * <remarks> Called by Sprite functions. </remarks>
	 *
	 * <param name="pSprite"> A Sprite pointer.</param>
	 **************************************************************************************************/
	virtual void modify(Sprite* pSprite) override;

};
#endif // !_SpriteNullModifierStrategy

//-----------------------------------------------------------------------------------------------------------------------------
// SpriteNullModifierStrategy Comment Template
//-----------------------------------------------------------------------------------------------------------------------------