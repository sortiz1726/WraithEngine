#ifndef _Draw2DRegistrationCommand
#define _Draw2DRegistrationCommand

#include "SceneRegistrationCommand.h"

class Drawable;

class Draw2DRegistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	Draw2DRegistrationCommand() = delete;
	Draw2DRegistrationCommand(const Draw2DRegistrationCommand&) = default;
	Draw2DRegistrationCommand& operator=(const Draw2DRegistrationCommand&) = default;
	Draw2DRegistrationCommand(Draw2DRegistrationCommand&&) = default;
	Draw2DRegistrationCommand& operator=(Draw2DRegistrationCommand&&) = default;
	~Draw2DRegistrationCommand() = default;

	Draw2DRegistrationCommand(Drawable*);

	// Inherited via SceneRegistrationCommand
	virtual void execute() override;

private:
	Drawable* _pDrawable;
};
#endif // !_Draw2DRegistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// Draw2DRegistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------