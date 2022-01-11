#include "FreezeTime.h"
#include "WraithAttorney.h"
#include "TimeManager.h"



#include <stdio.h> 

const float FreezeTime::DEAD_TIME_THRESHOLD = 0.1f;
const float FreezeTime::DEFAULT_FRAME_TIME = 1.0f / 60;

FreezeTime::FreezeTime()
{
	assert(DEFAULT_FRAME_TIME < DEAD_TIME_THRESHOLD);

	freeze_mode_active = false;
	totalFrozenTime = 0;
}

float FreezeTime::ComputerGameTime(float prev_gametime)
{
	TestForFreezeKeys(); // system time may pass here if freeze mode activated

	// Adjust system time to actual game time based cumulative frozen time so far
	float curr_gametime = WraithAttorney::TimeAccess::GetTimeInSeconds() - totalFrozenTime;

	// Determines if any extra frozen time (freeze keys, break points, etc.) occured since prev_gametime
	float frametime = curr_gametime - prev_gametime;
	// Any frametime > DEAD_TIME_THRESHOLD means extra frozen time to accumulated
	if (frametime > DEAD_TIME_THRESHOLD)
	{
		float extraFrozenTime = frametime - DEFAULT_FRAME_TIME; // Extra frozen time incurred since last frame

		totalFrozenTime += extraFrozenTime;	// tally frozen time total
		curr_gametime -= extraFrozenTime;	// correct curr_gametime with the extra frozen time

		DebugMsg::out("Game time frozen for %f secs (forcing frame time to %f)\n", extraFrozenTime, curr_gametime - prev_gametime);
	}

	return curr_gametime; // New current game time
}

void FreezeTime::TestForFreezeKeys()
{
	// Test whether we should enter freeze-frame mode:
	// Either we activated the freeze-time mode or 
	// we are returning after a single frame request
	if (HackedKeyRelease(FREEZE_KEY) || freeze_mode_active)
	{
		DebugMsg::out("FREEZE FRAME at time %f (last frame: %f) ", TimeManager::GetTimeInSeconds(), TimeManager::GetElaspedFrameTimeInSeconds());

		freeze_mode_active = true;				// Freeze mode active
		bool single_frame_requested = false;	// No single frame request yet

		// Freeze loop: Loop until freeze-time is cancelled or a single frame is requested
		while (freeze_mode_active && !single_frame_requested)
		{
			if (HackedKeyRelease(FREEZE_KEY))
			{
				freeze_mode_active = false;		// Cancel both freeze modes
				single_frame_requested = false;
			}
			else if (HackedKeyRelease(SINGLE_FRAME_KEY))
			{
				single_frame_requested = true;	// Process a single frame and freeze again
			}

			glfwPollEvents();  // We force GLFW to rescan the keyboard
		}
	}
}

// Helper function to detect a key press-and-release event
// Very hacky: The loop to wait for a release is resource intensive.
// Only good because we are freeze-framing the engine.
bool FreezeTime::HackedKeyRelease(AZUL_KEY k)
{
	bool keyPressedAndReleased = false;

	if (Keyboard::GetKeyState(k)) // Is the key pressed?
	{
		while (Keyboard::GetKeyState(k))	// Poll keyboard until k is released
			glfwWaitEvents();				// loop until something happens (typically, k is released)

		keyPressedAndReleased = true;  // Key k was pressed and released.
	}

	return keyPressedAndReleased;
}