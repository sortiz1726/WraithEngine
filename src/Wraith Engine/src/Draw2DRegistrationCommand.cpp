#include "Draw2DRegistrationCommand.h"
#include "DrawableAttorney.h"

Draw2DRegistrationCommand::Draw2DRegistrationCommand(Drawable* pDrawable)
	: _pDrawable(pDrawable)
{
	assert(pDrawable != nullptr);
}

void Draw2DRegistrationCommand::execute()
{
	DrawableAttorney::RegistrationAccess::Register2DToScene(_pDrawable);
}
