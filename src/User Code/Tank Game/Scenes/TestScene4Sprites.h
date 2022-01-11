#ifndef _TestScene4Sprites
#define _TestScene4Sprites

#include "Scene.h"

class TesterObject;

class TestScene4Sprites : public Scene
{
public:
	TestScene4Sprites() = default;
	TestScene4Sprites(const TestScene4Sprites&) = default;
	TestScene4Sprites& operator=(const TestScene4Sprites&) = default;
	TestScene4Sprites(TestScene4Sprites&&) = default;
	TestScene4Sprites& operator=(TestScene4Sprites&&) = default;
	~TestScene4Sprites() = default;

	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;

private:
	TesterObject* _pTesterObject;
};

#endif // !_TestScene4Sprites