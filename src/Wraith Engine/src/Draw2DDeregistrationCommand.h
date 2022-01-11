#ifndef _Draw2DDeregistrationCommand
#define _Draw2DDeregistrationCommand

#include "SceneRegistrationCommand.h"

class Drawable;

class Draw2DDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	Draw2DDeregistrationCommand() = delete;
	Draw2DDeregistrationCommand(const Draw2DDeregistrationCommand&) = default;
	Draw2DDeregistrationCommand& operator=(const Draw2DDeregistrationCommand&) = default;
	Draw2DDeregistrationCommand(Draw2DDeregistrationCommand&&) = default;
	Draw2DDeregistrationCommand& operator=(Draw2DDeregistrationCommand&&) = default;
	~Draw2DDeregistrationCommand() = default;

	Draw2DDeregistrationCommand(Drawable*);

	// Inherited via SceneRegistrationCommand
	virtual void execute() override;

private:
	Drawable* _pDrawable;
};
#endif // !_Draw2DDeregistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// Draw2DDeregistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------