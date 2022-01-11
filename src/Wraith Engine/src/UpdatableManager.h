
#ifndef _UpdatableManager
#define _UpdatableManager

#include <list>

class Updatable;

class UpdatableManager
{
private:
	typedef std::list<Updatable*> StorageList;
public:
	typedef StorageList::iterator StorageListReference;
public:
	// Big Six
	UpdatableManager() = default;
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator=(const UpdatableManager&) = delete;
	UpdatableManager(UpdatableManager&&) = delete;
	UpdatableManager& operator=(UpdatableManager&&) = delete;
	~UpdatableManager();

	/**********************************************************************************************//**
	 * <summary> Registers an Updatable entity.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pUpdatable"> the entity updatable.</param>
	 **************************************************************************************************/
	void registerEntity(Updatable* pUpdatable);

	/**********************************************************************************************//**
	 * <summary> Deregisters an Updatable entity.</summary>
	 *
	 * <remarks> .</remarks>
	 *
	 * <param name="pUpdatable"> the updatable entity.</param>
	 **************************************************************************************************/
	void deregisterEntity(Updatable* pUpdatable);

	/**********************************************************************************************//**
	 * <summary> Process the registered entities.</summary>
	 *
	 * <remarks> Called only by the current Scene in Scene::Update()</remarks>
	 **************************************************************************************************/
	void processEntities();

private:
	StorageList _registeredEntities;
};

#endif // !_UpdatableManager