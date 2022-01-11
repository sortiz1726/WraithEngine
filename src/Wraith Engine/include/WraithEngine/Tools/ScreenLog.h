#ifndef _ScreenLog
#define _ScreenLog

#include <string>
#include <list>

class SpriteFont;

/**********************************************************************************************//**
 * <summary> A screen log used for writing messages on the game screen. To be used like a output console
 * 			 for debugging.</summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/
class ScreenLog
{
	friend class ScreenLogAttorney;
	typedef std::list<std::string> MessageCollection;
private:
	static ScreenLog* pScreenLogInstance;

	ScreenLog();
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog& operator=(const ScreenLog&) = delete;
	ScreenLog(ScreenLog&&) = delete;
	ScreenLog& operator=(ScreenLog&&) = delete;
	~ScreenLog() = default;

	static ScreenLog& GetInstance();

	void privSetRenderAnchor(int anchorX, int anchorY);

	/**********************************************************************************************//**
	 * <summary> Renders all messages onto the screen</summary>
	 *
	 * <remarks> ONLY called by  Wraith::Draw() through the ScreenLogAttorney. </remarks>
	 **************************************************************************************************/
	static void Render()
	{
		GetInstance().privRender();
	}
	void privRender();

	/**********************************************************************************************//**
	 * <summary> Terminates Screen Log.</summary>
	 *
	 * <remarks> ONLY called by the Wraith::UnLoadContent() through ScreenLogAttorney.</remarks>
	 **************************************************************************************************/
	static void Delete();

public:

	/**********************************************************************************************//**
	 * <summary> Sets render anchor.</summary>
	 *	\ingroup SCREENLOG
	 * <remarks> </remarks>
	 *
	 * <param name="anchorX"> The anchor x coordinate.</param>
	 * <param name="anchorY"> The anchor y coordinate.</param>
	 **************************************************************************************************/
	static void SetRenderAnchor(int anchorX, int anchorY)
	{
		GetInstance().privSetRenderAnchor(anchorX, anchorY);
	}


	/**********************************************************************************************//**
	 * <summary> Adds format.</summary>
	 * \ingroup SCREENLOG
	 * <remarks> </remarks>
	 *
	 * <param name="format"> describes the string format to use.</param>
	 * <param name="...">    Variable arguments providing additional information of what to print.</param>
	 **************************************************************************************************/
	static void Add(char* format, ...)
	{
		va_list args;

		va_start(args, format);
		vsprintf_s(GetInstance()._debugBuff, format, args);
		va_end(args);

		std::string message = std::string(GetInstance()._debugBuff);
		GetInstance()._messages.push_back(message);
	}

private:
	int _anchorX;
	int _anchorY;
	char _debugBuff[256];

	SpriteFont* _pFont;

	MessageCollection _messages;

};
#endif // !_ScreenLog

//-----------------------------------------------------------------------------------------------------------------------------
// ScreenLog Comment Template
//-----------------------------------------------------------------------------------------------------------------------------