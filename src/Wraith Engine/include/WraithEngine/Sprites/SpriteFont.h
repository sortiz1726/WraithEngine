#ifndef _SpriteFont
#define _SpriteFont

#include <map>
#include <string>
#include <xmllite.h>

class Sprite;
class Texture;

/**********************************************************************************************//**
 * <summary> A sprite font used for get characters (glyps)
 * 			 from a particular texture.</summary>
 *
 * <remarks> SpriteFonts are created and maintained by tge SpriteFontManager. </remarks>
 **************************************************************************************************/
class SpriteFont
{

public:
	typedef int Key;
	typedef Sprite Glyph;
private:
	typedef std::map< Key, Glyph* > FontMap;

public:
	SpriteFont() = delete;
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;
	SpriteFont(SpriteFont&&) = delete;
	SpriteFont& operator=(SpriteFont&&) = delete;
	~SpriteFont();

	/**********************************************************************************************//**
	 * <summary> Constructor taking in a filePath.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="filePath"> Full pathname of the file of texture and xml file.</param>
	 **************************************************************************************************/
	SpriteFont(const std::string& filePath);

	/**********************************************************************************************//**
	 * <summary> Gets a glyph.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="character"> The character.</param>
	 *
	 * <returns> pointer to a glyph.</returns>
	 **************************************************************************************************/
	Glyph* getGlyph(char character) const;

	/**********************************************************************************************//**
	 * <summary> Gets the name of the font</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <returns> The name.</returns>
	 **************************************************************************************************/

	const std::string & getName() const;

private:

	/**********************************************************************************************//**
	 * <summary> Parses XML file.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="filename"> Filename of the the XML. </param>
	 **************************************************************************************************/
	void parseXMLtoCollection(const std::string& filename);

	/**********************************************************************************************//**
	 * <summary> Converts element text to int.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pReader">  the reader.</param>
	 * <param name="out">	  [in,out] The out.</param>
	 **************************************************************************************************/
	void elementTextToInt(IXmlReader* pReader, int& out);

	/**********************************************************************************************//**
	 * <summary> Creates a sprite.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="parameter1"> The first parameter.</param>
	 * <param name="x">			 The x coordinate.</param>
	 * <param name="y">			 The y coordinate.</param>
	 * <param name="w">			 The width.</param>
	 * <param name="h">			 The height.</param>
	 *
	 * <returns> Null if it fails, else the new sprite.</returns>
	 **************************************************************************************************/
	Sprite* createSprite(Key, int x, int y, int w, int h);

	/**********************************************************************************************//**
	 * <summary> Loads image into image manager.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="x">    The x coordinate.</param>
	 * <param name="y">    The y coordinate.</param>
	 * <param name="w">    The width.</param>
	 * <param name="h">    The height.</param>
	 * <param name="name"> The name.</param>
	 **************************************************************************************************/
	void loadImageIntoImageManager(int x, int y, int w, int h, const std::string& name);

private:
	std::string _name;
	Texture* _pFontTexture;
	FontMap _fontMap;

};
#endif // !_SpriteFont

//-----------------------------------------------------------------------------------------------------------------------------
// SpriteFont Comment Template
//-----------------------------------------------------------------------------------------------------------------------------