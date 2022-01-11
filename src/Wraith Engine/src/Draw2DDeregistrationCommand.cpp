#include "Draw2DDeregistrationCommand.h"
#include "DrawableAttorney.h"

Draw2DDeregistrationCommand::Draw2DDeregistrationCommand(Drawable* pDrawable)
	: _pDrawable(pDrawable)
{
	assert(_pDrawable != nullptr);
}

void Draw2DDeregistrationCommand::execute()
{
	DrawableAttorney::RegistrationAccess::Deregister2DFromScene(_pDrawable);
}
