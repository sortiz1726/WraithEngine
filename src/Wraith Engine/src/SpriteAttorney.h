#ifndef _SpriteAttorney
#define _SpriteAttorney

class Sprite;

/**********************************************************************************************//**
 * <summary> A sprite attorney allowing certain Sprite functions
 * 			 to be called by specified classes. </summary>
 *
 * <remarks> NOT called by the User. </remarks>
 **************************************************************************************************/
class SpriteAttorney
{
private:
	SpriteAttorney() = delete;
	SpriteAttorney(const SpriteAttorney&) = delete;
	SpriteAttorney& operator=(const SpriteAttorney&) = delete;
	SpriteAttorney(SpriteAttorney&&) = delete;
	SpriteAttorney& operator=(SpriteAttorney&&) = delete;
	~SpriteAttorney() = delete;

public:

	/**********************************************************************************************//**
	 * <summary> Allows for Update Access.</summary>
	 *
	 * <remarks>	</remarks>
	 **************************************************************************************************/
	class UpdateAccess
	{
		friend class SpriteWorldModifierStrategy;

		/**********************************************************************************************//**
		 * <summary> Updates the Sprite world matrix.</summary>
		 *
		 * <remarks> Called ONLY by SpriteWorldModifierStrategy::modify(). </remarks>
		 *
		 * <param name="pSprite"> A Sprite Pointer.</param>
		 **************************************************************************************************/
		static void UpdateWorld(Sprite* pSprite);
	};
};
#endif // !_SpriteAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// SpriteAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------