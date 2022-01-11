#include "DrawRegistrationCommand.h"
#include "DrawableAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* pDrawable)
	: _pDrawable(pDrawable)
{
	assert(pDrawable != nullptr);
}

void DrawRegistrationCommand::execute()
{
	DrawableAttorney::RegistrationAccess::RegisterToScene(_pDrawable);
}
