// FreezeTime
// Andre Berthiaume, Jan 2016

#ifndef _FreezeTime
#define _FreezeTime

#include "AzulCore.h"

class FreezeTime
{
private:
	static const AZUL_KEY FREEZE_KEY = AZUL_KEY::KEY_F10;
	static const AZUL_KEY SINGLE_FRAME_KEY = AZUL_KEY::KEY_F9;
	static const float DEAD_TIME_THRESHOLD;
	static const float DEFAULT_FRAME_TIME;

	float totalFrozenTime;
	bool freeze_mode_active;

	bool HackedKeyRelease(AZUL_KEY k);
	void TestForFreezeKeys();

public:
	FreezeTime();
	~FreezeTime(){};
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

	float ComputerGameTime(float prev_time);
};

#endif _FreezeTime