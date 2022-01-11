#include "TimeManager.h"

TimeManager* TimeManager::pTimeManagerInstance = nullptr;

TimeManager::TimeManager()
    : _previousTimeStamp(0.0f),
    _currentTimeStamp(0.0f),
    _elaspedFrameTime(0.0f)
{}

TimeManager& TimeManager::GetInstance()
{
    if (pTimeManagerInstance == nullptr)
    {
        pTimeManagerInstance = new TimeManager();
    }
    assert(pTimeManagerInstance != nullptr);
    return *pTimeManagerInstance;
}

void TimeManager::privSetCurrentTimeStamp(float currentTimeStamp)
{
    _previousTimeStamp = _currentTimeStamp;
    _currentTimeStamp = _freezeTime.ComputerGameTime(currentTimeStamp);
    _elaspedFrameTime = _currentTimeStamp - _previousTimeStamp;
}

float TimeManager::privGetTimeInSeconds() const
{
    return _currentTimeStamp;
}

float TimeManager::privGetElaspedFrameTimeInSeconds() const
{
    return _elaspedFrameTime;
}

void TimeManager::Delete()
{
    delete pTimeManagerInstance;
    pTimeManagerInstance = nullptr;
}
