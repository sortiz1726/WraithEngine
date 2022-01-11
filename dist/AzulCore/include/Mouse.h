#ifndef MOUSE_H
#define MOUSE_H

#include <GL/glfw.h>

// Wrapper to buffer users from the internal glfw driver
// Converted to enumeration for type safety - yeah!

enum AZUL_MOUSE
{
	BUTTON_1 = 0,
	BUTTON_2 = 1,
	BUTTON_3 = 2,
	BUTTON_4 = 3,
	BUTTON_5 = 4,
	BUTTON_6 = 5,
	BUTTON_7 = 6,
	BUTTON_8 = 7,
	BUTTON_LEFT = GLFW_MOUSE_BUTTON_1,
	BUTTON_RIGHT = GLFW_MOUSE_BUTTON_2,
	BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_3
};

class Mouse
{
private:
	Mouse();
	~Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse operator=(const Mouse&) = delete;

	static Mouse *GetInstance();

public:
	// Use this to read mouse buttons
	static bool GetKeyState(AZUL_MOUSE button);

	// Get cursor
	static void GetCursor(float &xPos, float &yPos);

	// Mouse wheel position
	static void GetWheel(float& pos);
	static void SetWheel(int pos);



};

#endif