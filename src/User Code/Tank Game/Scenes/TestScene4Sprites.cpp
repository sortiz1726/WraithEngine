#include "TestScene4Sprites.h"
#include "TesterObject.h"

void TestScene4Sprites::initialize()
{
	_pTesterObject = new TesterObject();
}

void TestScene4Sprites::sceneEnd()
{
	delete _pTesterObject;
}
