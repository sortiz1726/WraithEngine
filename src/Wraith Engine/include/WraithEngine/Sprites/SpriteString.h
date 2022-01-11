#ifndef _SpriteString
#define _SpriteString

#include <string>
#include <vector>
#include <list>

class SpriteFont;
class Sprite;

/**********************************************************************************************//**
 * <summary> A sprite string that handles 2D text messages on screen</summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/

class SpriteString
{
	typedef std::list<Sprite*> GlyphCollection;

public:
	SpriteString();
	SpriteString(const SpriteString&) = default;
	SpriteString& operator=(const SpriteString&) = default;
	SpriteString(SpriteString&&) = default;
	SpriteString& operator=(SpriteString&&) = default;
	~SpriteString() = default;

	/**********************************************************************************************//**
	 * <summary> Constructor.</summary>
	 * \ingroup SPRITESTRING
	 * <remarks> </remarks>
	 *
	 * <param name="pSpriteFont">  sprite font pointer.</param>
	 * <param name="message">	  The message.</param>
	 * <param name="positionX">   The position x coordinate.</param>
	 * <param name="positionY">   The position y coordinate.</param>
	 **************************************************************************************************/
	SpriteString(SpriteFont* pSpriteFont, const std::string& message, int positionX, int positionY);

	/**********************************************************************************************//**
	 * <summary> Sets sprite string data.</summary>
	 * \ingroup SPRITESTRING
	 * <remarks> </remarks>
	 *
	 * <param name="pSpriteFont">  sprite font pointer.</param>
	 * <param name="message">	  The message.</param>
	 * <param name="positionX">   The position x coordinate.</param>
	 * <param name="positionY">   The position y coordinate.</param>
	 **************************************************************************************************/
	void set(SpriteFont* pSpriteFont, const std::string& message, int positionX, int positionY);

	/**********************************************************************************************//**
	 * <summary> Sets a position.</summary>
	 * \ingroup SPRITESTRING
	 * <remarks> </remarks>
	 *
	 * <param name="positionX"> The position x coordinate.</param>
	 * <param name="positionY"> The position y coordinate.</param>
	 **************************************************************************************************/
	void setPosition(int positionX, int positionY);

	/**********************************************************************************************//**
	 * <summary> Gets position x coordinate.</summary>
	 * \ingroup SPRITESTRING
	 * <remarks> </remarks>
	 *
	 * <returns> The position x coordinate.</returns>
	 **************************************************************************************************/
	int getPositionX() const;

	/**********************************************************************************************//**
	 * <summary> Gets position y coordinate.</summary>
	 * \ingroup SPRITESTRING
	 * <remarks> </remarks>
	 *
	 * <returns> The position y coordinate.</returns>
	 **************************************************************************************************/
	int getPositionY() const;

	/**********************************************************************************************//**
	 * <summary> Gets the width.</summary>
	 * \ingroup SPRITESTRING
	 * <remarks> </remarks>
	 *
	 * <returns> The width.</returns>
	 **************************************************************************************************/
	int getWidth() const;

	/**********************************************************************************************//**
	 * <summary> Gets the height.</summary>
	 * \ingroup SPRITESTRING
	 * <remarks> </remarks>
	 *
	 * <returns> The height.</returns>
	 **************************************************************************************************/
	int getHeight() const;

	/**********************************************************************************************//**
	 * <summary> Renders the sprite string message onto the string.</summary>
	 * \ingroup SPRITESTRING
	 * <remarks> This must be called within GameObject::draw2D() callback. </remarks>
	 **************************************************************************************************/
	void render();

private:
	GlyphCollection _glyphs;
	int _positionX;
	int _positionY;
	int _width;
	int _height;
};
#endif // !_SpriteString

//-----------------------------------------------------------------------------------------------------------------------------
// SpriteString Comment Template
//-----------------------------------------------------------------------------------------------------------------------------