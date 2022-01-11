#include "Drawable2DManager.h"
#include "Drawable.h"
#include "DrawableAttorney.h"

Drawable2DManager::~Drawable2DManager()
{
	_registeredEntities.clear();
}

void Drawable2DManager::registerEntity(Drawable* pDrawable)
{
	assert(pDrawable != nullptr);
	StorageListReference deleteReference = _registeredEntities.insert(_registeredEntities.end(), pDrawable);
	DrawableAttorney::FieldAccess::SetDeleteReference2D(pDrawable, deleteReference);
}

void Drawable2DManager::deregisterEntity(Drawable* pDrawable)
{
	assert(pDrawable != nullptr);
	_registeredEntities.erase(DrawableAttorney::FieldAccess::GetDeleteReference2D(pDrawable));
}

void Drawable2DManager::processEntities()
{
	for (Drawable* pDrawable : _registeredEntities)
	{
		DrawableAttorney::DrawAccess::Draw2D(pDrawable);
	}
}
