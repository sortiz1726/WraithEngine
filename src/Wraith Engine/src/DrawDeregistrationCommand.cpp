#include "DrawDeregistrationCommand.h"
#include "DrawableAttorney.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* pDrawable)
	: _pDrawable(pDrawable)
{
	assert(_pDrawable != nullptr);
}

void DrawDeregistrationCommand::execute()
{
	DrawableAttorney::RegistrationAccess::DeregisterFromScene(_pDrawable);
}
