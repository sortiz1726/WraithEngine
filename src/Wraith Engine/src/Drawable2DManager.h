#ifndef _Drawable2DManager
#define _Drawable2DManager

#include <list>

class Drawable;

class Drawable2DManager
{
private:
	typedef std::list<Drawable*> StorageList;
public:
	typedef StorageList::iterator StorageListReference;

public:
	Drawable2DManager() = default;
	Drawable2DManager(const Drawable2DManager&) = delete;
	Drawable2DManager& operator=(const Drawable2DManager&) = delete;
	Drawable2DManager(Drawable2DManager&&) = delete;
	Drawable2DManager& operator=(Drawable2DManager&&) = delete;
	~Drawable2DManager();

	/**********************************************************************************************//**
	 * <summary> Registers a Drawable entity .</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pDrawable"> a drawable entity.</param>
	 **************************************************************************************************/
	void registerEntity(Drawable* pDrawable);

	/**********************************************************************************************//**
	 * <summary> Deregisters a Drawable entity.</summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pDrawable"> a drawable entity.</param>
	 **************************************************************************************************/
	void deregisterEntity(Drawable* pDrawable);

	/**********************************************************************************************//**
	 * <summary> Process the registered entities.</summary>
	 *
	 * <remarks> Called only by the current Scene in Scene::Update() </remarks>
	 **************************************************************************************************/
	void processEntities();

private:
	StorageList _registeredEntities;
};

#endif // !_Drawable2DManager