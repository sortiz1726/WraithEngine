#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "SceneRegistrationCommand.h"

class Drawable;

class DrawDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// Big Six
	DrawDeregistrationCommand() = delete;
	DrawDeregistrationCommand(const DrawDeregistrationCommand&) = default;
	DrawDeregistrationCommand& operator=(const DrawDeregistrationCommand&) = default;
	DrawDeregistrationCommand(DrawDeregistrationCommand&&) = default;
	DrawDeregistrationCommand& operator=(DrawDeregistrationCommand&&) = default;
	~DrawDeregistrationCommand() = default;

	DrawDeregistrationCommand(Drawable*);

	// Inherited via SceneRegistrationCommand
	virtual void execute() override;

private:
	Drawable* _pDrawable;
};
#endif // !_DrawDeregistrationCommand

//-----------------------------------------------------------------------------------------------------------------------------
// DrawDeregistrationCommand Comment Template
//-----------------------------------------------------------------------------------------------------------------------------