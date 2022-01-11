#include "DrawableManager.h"
#include "Drawable.h"
#include "DrawableAttorney.h"

DrawableManager::~DrawableManager()
{
	_registeredEntities.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------
//  Registration/Deregistration
//-----------------------------------------------------------------------------------------------------------------------------
void DrawableManager::registerEntity(Drawable* pDrawable)
{
	assert(pDrawable != nullptr);
	StorageListReference deleteReference = _registeredEntities.insert(_registeredEntities.end(), pDrawable);
	DrawableAttorney::FieldAccess::SetDeleteReference(pDrawable, deleteReference);
}

void DrawableManager::deregisterEntity(Drawable* pDrawable)
{
	assert(pDrawable != nullptr);
	_registeredEntities.erase(DrawableAttorney::FieldAccess::GetDeleteReference(pDrawable));
}

void DrawableManager::register2DEntity(Drawable* pDrawable)
{
	_drawable2DManager.registerEntity(pDrawable);
}

void DrawableManager::deregister2DEntity(Drawable* pDrawable)
{
	_drawable2DManager.deregisterEntity(pDrawable);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Processing Entities
//-----------------------------------------------------------------------------------------------------------------------------
void DrawableManager::processEntities()
{
	for (Drawable* pDrawable : _registeredEntities)
	{
		DrawableAttorney::DrawAccess::Draw(pDrawable);
	}

	_drawable2DManager.processEntities();
}
