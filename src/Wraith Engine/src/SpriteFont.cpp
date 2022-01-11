#include "SpriteFont.h"
#include <xmllite.h>
#include <shlwapi.h>
#include "Texture.h"
#include "ImageManager.h"
#include "Sprite.h"
#include "Rect.h"
#include "Wraith.h"

//*********************************************************
// Don't forget to add the associated libs to your project 
// Properties/Linker/Input  -> add these
//		xmllite.lib
//		shlwapi.lib
//*********************************************************

SpriteFont::SpriteFont(const std::string& filePath)
{
	// <Load associate texture into TextureManager>
	_pFontTexture = new Texture((filePath + ".tga").c_str());
	_name = filePath;
	// Parse associated XML file
	parseXMLtoCollection(filePath + ".xml");
}

SpriteFont::~SpriteFont()
{
	delete _pFontTexture;
	for (auto& pair : _fontMap)
	{
		delete pair.second;
	}
}

void SpriteFont::parseXMLtoCollection(const std::string& filename)
{
	IXmlReader* reader = nullptr;
	IStream* readStream = nullptr;
	XmlNodeType nodeType;

	CreateXmlReader(IID_PPV_ARGS(&reader), nullptr);

	SHCreateStreamOnFile(filename.c_str(), STGM_READ, &readStream);

	reader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit);
	reader->SetInput(readStream);

	const wchar_t* stringValue = nullptr;
	unsigned int stringSize = 0;

	int key = 0;	// ASCII value
	int x = 0;		// x, y position of the glyph in texture
	int y = 0;
	int w = 0;		// width and height of the gluth in texture
	int h = 0;

	while (S_OK == reader->Read(&nodeType))
	{
		switch (nodeType)
		{
		case XmlNodeType::XmlNodeType_Element:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);

			if (wcscmp(stringValue, L"character") == 0)
			{
				//Gets ASCII value
				reader->MoveToAttributeByName(L"key", nullptr);
				reader->GetValue(&stringValue, &stringSize);
				key = _wtoi(stringValue);
			}
			else if (wcscmp(stringValue, L"x") == 0)
			{
				elementTextToInt(reader, x);
			}
			else if (wcscmp(stringValue, L"y") == 0)
			{
				elementTextToInt(reader, y);
			}
			else if (wcscmp(stringValue, L"width") == 0)
			{
				elementTextToInt(reader, w);
			}
			else if (wcscmp(stringValue, L"height") == 0)
			{
				elementTextToInt(reader, h);
			}
			else
			{
			}
		} break;

		case XmlNodeType::XmlNodeType_EndElement:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);
			assert(stringValue);

			//If we are at the end of "character", we found everything we need for this char
			if (wcscmp(stringValue, L"character") == 0)
			{
				//************************************************************************
				// You now have all the data for a character: key, x, y, w, h
				//
				// Load the associated image in the ImageManager 
				// (its name could be <font name><key> to insure uniqueness)
				//
				// Create the glyph and add it to the fontmap
				// NB: Consider moving the glyph's origin to the *upper-left* corner...
				//*************************************************************************
				Trace::out("Font %s: creating glyph for ASCII %i\n", _name.c_str(), key);
				
				Sprite* pSprite = createSprite(key, x, y, w, h);

				_fontMap.insert(std::make_pair(key, pSprite));
			}

		} break;

		//Don't care about these
		case XmlNodeType::XmlNodeType_Attribute:
		case XmlNodeType::XmlNodeType_CDATA:
		case XmlNodeType::XmlNodeType_Comment:
		case XmlNodeType::XmlNodeType_DocumentType:
		case XmlNodeType::XmlNodeType_None:
		case XmlNodeType::XmlNodeType_ProcessingInstruction:
		case XmlNodeType::XmlNodeType_Text:
		case XmlNodeType::XmlNodeType_Whitespace:
		case XmlNodeType::_XmlNodeType_Last:
		default:
		{} break;
		}
	}

	//Release COM objects
	if (readStream)
	{
		readStream->Release();
	}

	if (reader)
	{
		reader->Release();
	}
}

void SpriteFont::elementTextToInt(IXmlReader* pReader, int& out)
{
	const wchar_t* stringValue = nullptr;
	UINT stringSize = 0;
	XmlNodeType nodeType;

	while (S_OK == pReader->Read(&nodeType))
	{
		if (nodeType == XmlNodeType::XmlNodeType_Text)
		{
			pReader->GetValue(&stringValue, &stringSize);
			assert(stringValue);

			out = _wtoi(stringValue);
			break;
		}
	}
}

Sprite* SpriteFont::createSprite(Key key, int x, int y, int w, int h)
{
	std::string name = _name + std::to_string(key); // construct a unqiue
	loadImageIntoImageManager(x, y, w, h, name);

	Sprite* pSprite = new Sprite(name);
	pSprite->setCenter(-w / 2.0f, h / 2.0f); // Sets Center to upper left corner
	pSprite->setScalePixel(static_cast<float>(w * 1), static_cast<float>(h * 1));

	return pSprite;
}

void SpriteFont::loadImageIntoImageManager(int x, int y, int w, int h, const std::string& name)
{
	Rect* rectanlge = new Rect(static_cast<float>(x), static_cast<float>(y), 
								static_cast<float>(w), static_cast<float>(h));
	ImageManager::LoadImageAndAssignKey(new Texture(*_pFontTexture), rectanlge, name);
}

SpriteFont::Glyph* SpriteFont::getGlyph(char character) const
{
	return _fontMap.at(character);
}

const std::string& SpriteFont::getName() const
{
	return _name;
}
