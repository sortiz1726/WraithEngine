#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "SceneRegistrationCommand.h"

class Drawable;

class DrawRegistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	DrawRegistrationCommand() = delete;
	DrawRegistrationCommand(const DrawRegistrationCommand&) = default;
	DrawRegistrationCommand& operator=(const DrawRegistrationCommand&) = default;
	DrawRegistrationCommand(DrawRegistrationCommand&&) = default;
	DrawRegistrationCommand& operator=(DrawRegistrationCommand&&) = default;
	~DrawRegistrationCommand() = default;

	DrawRegistrationCommand(Drawable*);

	// Inherited via SceneRegistrationCommand
	virtual void execute() override;

private:
	Drawable* _pDrawable;
};
#endif // !_DrawRegistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// DrawRegistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------