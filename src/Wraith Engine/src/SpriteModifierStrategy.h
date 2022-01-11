#ifndef _SpriteModifierStrategy
#define _SpriteModifierStrategy

class Sprite;

/**********************************************************************************************//**
 * <summary> A sprite modifier strategy.</summary>
 *
 * <remarks> Used INTERNALLY by Sprite. </remarks>
 **************************************************************************************************/
class SpriteModifierStrategy
{
public:
	SpriteModifierStrategy() = default;
	SpriteModifierStrategy(const SpriteModifierStrategy&) = default;
	SpriteModifierStrategy& operator=(const SpriteModifierStrategy&) = default;
	SpriteModifierStrategy(SpriteModifierStrategy&&) = default;
	SpriteModifierStrategy& operator=(SpriteModifierStrategy&&) = default;
	virtual ~SpriteModifierStrategy() = default;

	/**********************************************************************************************//**
	 * <summary> Modifies the given Sprite.</summary>
	 *
	 * <remarks> Called ONLY by Sprite functions</remarks>
	 *
	 * <param name="pSprite"> A Sprite pointer.</param>
	 **************************************************************************************************/
	virtual void modify(Sprite* pSprite) = 0;

};
#endif // !_SpriteModifierStrategy

//-----------------------------------------------------------------------------------------------------------------------------
// SpriteModifierStrategy Comment Template
//-----------------------------------------------------------------------------------------------------------------------------