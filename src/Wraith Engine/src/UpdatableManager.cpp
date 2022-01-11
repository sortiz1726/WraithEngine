#include "UpdatableManager.h"
#include "Updatable.h"
#include "UpdatableAttorney.h"

UpdatableManager::~UpdatableManager()
{
	_registeredEntities.clear();
}

void UpdatableManager::registerEntity(Updatable* pUpdatable)
{
	assert(pUpdatable != nullptr);
	StorageListReference deleteReference = _registeredEntities.insert(_registeredEntities.end(), pUpdatable);
	UpdatableAttorney::FieldAccess::SetDeleteReference(pUpdatable, deleteReference);
}

void UpdatableManager::deregisterEntity(Updatable* pUpdatable)
{
	assert(pUpdatable != nullptr);
	StorageListReference deleteReference = UpdatableAttorney::FieldAccess::GetDeleteReference(pUpdatable);
	_registeredEntities.erase(deleteReference);
}

void UpdatableManager::processEntities()
{
	for (Updatable* pUpdatable : _registeredEntities)
	{
		UpdatableAttorney::UpdateAccess::Update(pUpdatable);
	}
}