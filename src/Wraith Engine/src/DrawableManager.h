#ifndef _DrawableManager
#define _DrawableManager

#include <list>
#include "Drawable2DManager.h"

class Drawable;

class DrawableManager
{
private:
	typedef std::list<Drawable*> StorageList;
public:
	typedef StorageList::iterator StorageListReference;

public:
	DrawableManager() = default;
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;
	DrawableManager(DrawableManager&&) = delete;
	DrawableManager& operator=(DrawableManager&&) = delete;
	~DrawableManager();

	/**********************************************************************************************//**
	 * <summary> Registers a Drawable entity for Drawable::draw(). </summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pDrawable"> a drawable entity pointer.</param>
	 **************************************************************************************************/
	void registerEntity(Drawable* pDrawable);

	/**********************************************************************************************//**
	 * <summary> Deregisters a Drawable entity from Drawable::draw(). </summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pDrawable"> a drawable entity pointer. </param>
	 **************************************************************************************************/
	void deregisterEntity(Drawable* pDrawable);

	/**********************************************************************************************//**
	 * <summary> Registers a Drawable entity for Drawable::draw2D(). </summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pDrawable"> a drawable entity pointer. </param>
	 **************************************************************************************************/
	void register2DEntity(Drawable* pDrawable);

	/**********************************************************************************************//**
	 * <summary> Deregisters a Drawable entity from Drawable::draw2D(). </summary>
	 *
	 * <remarks> </remarks>
	 *
	 * <param name="pDrawable"> a drawable entity pointer. </param>
	 **************************************************************************************************/
	void deregister2DEntity(Drawable* pDrawable);

	/**********************************************************************************************//**
	 * <summary> Process the registered entities.</summary>
	 *
	 * <remarks> Called ONLY by the current Scene in Scene::Update().
	 * 			 Also calls on Drawable2DManager::processEntities() 
	 * 			 after processing its own entities. </remarks>
	 **************************************************************************************************/
	void processEntities();

private:
	StorageList _registeredEntities;

	Drawable2DManager _drawable2DManager;
};

#endif // !_DrawableManager

//-----------------------------------------------------------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------------------------------------------------------