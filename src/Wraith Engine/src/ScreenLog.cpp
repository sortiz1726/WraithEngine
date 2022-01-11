#include "ScreenLog.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"
#include "Wraith.h"

ScreenLog* ScreenLog::pScreenLogInstance = nullptr;

ScreenLog& ScreenLog::GetInstance()
{
	if (ScreenLog::pScreenLogInstance == nullptr)
	{
		ScreenLog::pScreenLogInstance = new ScreenLog();
	}
	assert(ScreenLog::pScreenLogInstance != nullptr);
	return *ScreenLog::pScreenLogInstance;
}

ScreenLog::ScreenLog()
{
	privSetRenderAnchor(0, Wraith::GetWindowHeight());
	_pFont = SpriteFontManager::GetSpriteFont("ScreenLogFont");
}

void ScreenLog::privSetRenderAnchor(int anchorX, int anchorY)
{
	_anchorX = anchorX;
	_anchorY = anchorY;
}

void ScreenLog::privRender()
{
	SpriteString spriteString = SpriteString();

	int positionX = _anchorX;
	int positionY = _anchorY;
	for (const std::string& message : _messages)
	{
		spriteString.set(_pFont, message, positionX, positionY);
		spriteString.render();
		positionY -= spriteString.getHeight();
	}

	_messages.clear();
}

void ScreenLog::Delete()
{
	delete ScreenLog::pScreenLogInstance;
	ScreenLog::pScreenLogInstance = nullptr;
}
