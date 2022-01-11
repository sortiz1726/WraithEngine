#include "SpriteString.h"
#include "SpriteFont.h"
#include "Sprite.h"
#include "SpriteFontManager.h"
#include "Wraith.h"

SpriteString::SpriteString()
	: SpriteString(SpriteFontManager::GetSpriteFont("ScreenLogFont"), "DEFAULT_MESSAGE", 0, Wraith::GetWindowHeight())
{}

SpriteString::SpriteString(SpriteFont* pSpriteFont, const std::string& message, int positionX, int positionY)
	: _positionX(0), _positionY(0),
	_width(0), _height(0)
{
	set(pSpriteFont, message, positionX, positionY);
}

void SpriteString::set(SpriteFont* pSpriteFont, const std::string& message, int positionX, int positionY)
{
	_glyphs.clear();

	_positionX = positionX;
	_positionY = positionY;
	_width = 0;
	_height = 0;

	for (char character : message)
	{
		SpriteFont::Glyph* pGlyph = pSpriteFont->getGlyph(character);
		_width += static_cast<int>(pGlyph->getWidth());
		_glyphs.push_back(pGlyph);
	}

	_height = static_cast<int>(_glyphs.front()->getHeight());
}

void SpriteString::setPosition(int positionX, int positionY)
{
	_positionX = positionX;
	_positionY = positionY;
}

int SpriteString::getPositionX() const
{
	return _positionX;
}

int SpriteString::getPositionY() const
{
	return _positionY;
}

int SpriteString::getWidth() const
{
	return _width;
}

int SpriteString::getHeight() const
{
	return _height;
}

void SpriteString::render()
{
	int positionX = _positionX;

	for (SpriteFont::Glyph* pGlyph : _glyphs)
	{
		pGlyph->setPosition(static_cast<float>(positionX), static_cast<float>(_positionY));
		pGlyph->render();
		positionX += static_cast<int>(pGlyph->getWidth());
	}
}
