#ifndef _Wraith
#define _Wraith

#include "AzulCore.h"
#include <string>

class Wraith: public Engine
{
	friend class WraithAttorney;
private:
	static Wraith* pGameInstance;

	Wraith();
	Wraith(const Wraith&) = delete;
	Wraith& operator=(const Wraith&) = delete;
	Wraith(Wraith&&) = delete;
	Wraith& operator=(Wraith&&) = delete;
	~Wraith() = default;

	// -----------------------------------------------------------------------------
	// To be defined by user (Specific to each game)
	// -----------------------------------------------------------------------------

	/**********************************************************************************************//**
	 * <summary> User defined area where the user loads resources.</summary>
	 * \ingroup RESOURCES
	 * <remarks> This is where the user calls on various asset managers to load in 
	 * 			 various assets into the game before running. </remarks>
	 **************************************************************************************************/
	void loadResources();

	/**********************************************************************************************//**
	 * <summary> User defined are for initializing the game. </summary>
	 * \ingroup GAME_INITALIZE_END
	 * <remarks> Mainly used for window set up. IMPORTANT: Resources should not be load here.
	 * 			 They should be loading within Wraith::loadResources() function.</remarks>
	 **************************************************************************************************/
	void gameInitialize();

	/**********************************************************************************************//**
	 * <summary> User defined function where any clean up by the user is needed.</summary>
	 * \ingroup GAME_INITALIZE_END
	 * <remarks> Mostly used for deleting any user defined manager, factories, and object pools. </remarks>
	 **************************************************************************************************/
	void gameEnd();

	// Getting Wraith Instance
	static Wraith& GetInstance();



	/**********************************************************************************************//**
	 * <summary> Initializes game settings./</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	virtual void Initialize() override;

	/**********************************************************************************************//**
	 * <summary> Loads the game contents such as user resources.</summary>
	 *
	 * <remarks> .</remarks>
	 **************************************************************************************************/
	virtual void LoadContent() override;

	/**********************************************************************************************//**
	 * <summary> Updates Game data such as scene (with its asscoated managers and game object entities).</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	virtual void Update() override;

	/**********************************************************************************************//**
	 * <summary> Draws all graphics object exisiting within a scene.</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	virtual void Draw() override;

	/**********************************************************************************************//**
	 * <summary> Unloads content from the game.</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	virtual void UnLoadContent() override;

	/**********************************************************************************************//**
	 * <summary> Gets time in seconds.</summary>
	 *
	 * <remarks> This a private function that is NEVER called by the user.
	 * 			 Time accessed by the TimeManager</remarks>
	 *
	 * <returns> The time in seconds.</returns>
	 **************************************************************************************************/
	static float GetTimeInSeconds()
	{
		return GetInstance().Engine::GetTimeInSeconds();
	}
	// legacy
	Wraith(const char* windowName, const int Width, const int Height);

public:

	/**********************************************************************************************//**
	 * <summary> Begins and runs the engine.</summary>
	 *
	 * <remarks> Only to be called in main.cpp. </remarks>
	 **************************************************************************************************/
	static void Run()
	{
		GetInstance().run();
	}

	/**********************************************************************************************//**
	 * <summary> Sets window name.</summary>
	 * \ingroup WRAITHENGINE
	 * <remarks> Steven, 2/27/2021.</remarks>
	 *
	 * <param name="windowName"> Name of the window.</param>
	 **************************************************************************************************/
	static void SetWindowName(const char* windowName)
	{
		GetInstance().setWindowName(windowName);
	}

	/**********************************************************************************************//**
	 * <summary> Sets window width and height.</summary>
	 * \ingroup WRAITHENGINE
	 * <remarks> </remarks>
	 *
	 * <param name="windowWidth">  Width of the window.</param>
	 * <param name="windowHeight"> Height of the window.</param>
	 **************************************************************************************************/
	static void SetWindowWidthAndHeight(const int windowWidth, const int windowHeight)
	{
		GetInstance().setWidthHeight(windowWidth, windowHeight);
	}

	/**********************************************************************************************//**
	 * <summary> Sets background color of the window.</summary>
	 * \ingroup WRAITHENGINE
	 * <remarks> </remarks>
	 *
	 * <param name="red">   The red value.</param>
	 * <param name="green"> The green value.</param>
	 * <param name="blue">  The blue value.</param>
	 * <param name="alpha"> The alpha value.</param>
	 **************************************************************************************************/
	static void SetBackgroundColor(const float red, const float green, const float blue, const float alpha)
	{
		GetInstance().SetClearColor(red, green, blue, alpha);
	}

	/**********************************************************************************************//**
	 * <summary> Gets window width.</summary>
	 * \ingroup WRAITHENGINE
	 * <remarks> </remarks>
	 *
	 * <returns> The window width.</returns>
	 **************************************************************************************************/
	static int GetWindowWidth()
	{
		return GetInstance().getWidth();
	}

	/**********************************************************************************************//**
	 * <summary> Gets window height.</summary>
	 * \ingroup WRAITHENGINE
	 * <remarks> </remarks>
	 *
	 * <returns> The window height.</returns>
	 **************************************************************************************************/
	static int GetWindowHeight()
	{
		return GetInstance().getHeight();
	}

	/**********************************************************************************************//**
	 * <summary> Terminates engine and other resources and managers.</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	static void Delete();

private:
	// Personal Printing function 
	static void PrintTitleMessage(const std::string&);
};

#endif // !_Wraith