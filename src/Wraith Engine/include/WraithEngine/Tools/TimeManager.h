#ifndef _TimeManager
#define _TimeManager

#include "FreezeTime.h"

/**********************************************************************************************//**
 * <summary> Manager for time related data such as total run time and frame time.
 * 			 </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/

class TimeManager
{
	friend class TimeManagerAttorney;
private:
	static TimeManager* pTimeManagerInstance;

	TimeManager();
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	TimeManager(TimeManager&&) = delete;
	TimeManager& operator=(TimeManager&&) = delete;
	~TimeManager() = default;

	static TimeManager& GetInstance();

	/**********************************************************************************************//**
	 * <summary> Sets current time stamp.</summary>
	 *
	 * <remarks> ONLY called by the Wraith Engine during the Wraith::update().
	 * 			 Internal works with FreezeTime for allowing freeze frame and frame stepping</remarks>
	 *
	 * <param name="currentTimeStamp"> The current time stamp.</param>
	 **************************************************************************************************/
	static void SetCurrentTimeStamp(float currentTimeStamp)
	{
		GetInstance().privSetCurrentTimeStamp(currentTimeStamp);
	}
	void privSetCurrentTimeStamp(float currentTimeStamp);

	float privGetTimeInSeconds() const;
	float privGetElaspedFrameTimeInSeconds() const;

	/**********************************************************************************************//**
	 * <summary> Terminates the TimeManager</summary>
	 *
	 * <remarks> ONLY called by Wraith::gameEnd() through TimeManagerAttorney.</remarks>
	 **************************************************************************************************/
	static void Delete();

public:

	/**********************************************************************************************//**
	 * <summary> Gets time in seconds since the game started.</summary>
	 * \ingroup TIMEMANAGER
	 * <remarks> </remarks>
	 *
	 * <returns> The time in seconds.</returns>
	 **************************************************************************************************/
	static float GetTimeInSeconds()
	{
		return GetInstance().privGetTimeInSeconds();
	}

	/**********************************************************************************************//**
	 * <summary> Gets elasped frame time in seconds (Time between frames).</summary>
	 * \ingroup TIMEMANAGER
	 * <remarks> </remarks>
	 *
	 * <returns> The elasped frame time in seconds.</returns>
	 **************************************************************************************************/
	static float GetElaspedFrameTimeInSeconds()
	{
		return GetInstance().privGetElaspedFrameTimeInSeconds();
	}

private:
	float _previousTimeStamp;
	float _currentTimeStamp;
	float _elaspedFrameTime;

	FreezeTime _freezeTime;

};

#endif // !_TimeManager

//-----------------------------------------------------------------------------------------------------------------------------
// TimeManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------