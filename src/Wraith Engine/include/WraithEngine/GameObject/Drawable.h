#ifndef _Drawable
#define _Drawable

#include "DrawableManager.h"
#include "Drawable2DManager.h"
#include "RegistrationStates.h"

class DrawRegistrationCommand;
class DrawDeregistrationCommand;
class Draw2DRegistrationCommand;
class Draw2DDeregistrationCommand;

class Drawable
{
	friend class DrawableAttorney;
public:
	// Big Six
	Drawable();
	Drawable(const Drawable&) = default;
	Drawable& operator=(const Drawable&) = default;
	Drawable(Drawable&&) = default;
	Drawable& operator=(Drawable&&) = default;
	virtual ~Drawable();

protected:
	// Registration/Deregistration

	/**********************************************************************************************//**
	 * <summary> Submit draw registration to current scene.</summary>
	 * \ingroup DRAW
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void submitDrawRegistration();

	/**********************************************************************************************//**
	 * <summary> Submit draw deregistration to current scene.</summary>
	 * \ingroup DRAW
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void submitDrawDeregistration();

	/**********************************************************************************************//**
	 * <summary> Submit draw 2D registration to current scene.</summary>
	 * \ingroup DRAW
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void submitDraw2DRegistration();

	/**********************************************************************************************//**
	 * <summary> Submit draw 2D deregistration from current scene.</summary>
	 * \ingroup DRAW
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void submitDraw2DDeregistration();

	/**********************************************************************************************//**
	 * <summary> Query if this object is registered for draw.</summary>
	 * \ingroup DRAW
	 * <remarks> </remarks>
	 *
	 * <returns> True if registered for draw, false if not.</returns>
	 **************************************************************************************************/
	bool isRegisteredForDraw() const;

	/**********************************************************************************************//**
	 * <summary> Query if this object is registered for draw 2D.</summary>
	 * \ingroup DRAW
	 * <remarks> </remarks>
	 *
	 * <returns> True if registered for draw2D, false if not.</returns>
	 **************************************************************************************************/
	bool isRegisteredForDraw2D() const;

private:
	// Setter/Getter Terminate Reference
	void setDeleteReference(const DrawableManager::StorageListReference&);
	DrawableManager::StorageListReference getDeleteReference() const;

	void setDeleteReference2D(const Drawable2DManager::StorageListReference&);
	Drawable2DManager::StorageListReference getDeleteReference2D() const;

	//  Register/Deregister
	
	/**********************************************************************************************//**
	 * <summary> Registers to the current scene.</summary>
	 *
	 * <remarks> DELAYED called with a command. NOT called by the user. </remarks>
	 **************************************************************************************************/
	void registerToScene();

	/**********************************************************************************************//**
	 * <summary> Deregisters from the current scene.</summary>
	 *
	 * <remarks> DELAYED called with a command. NOT called by the user. </remarks>
	 **************************************************************************************************/
	void deregisterFromScene();

	/**********************************************************************************************//**
	 * <summary> Registers Draw2D to current scene.</summary>
	 *
	 * <remarks> DELAYED called with a command. NOT called by the user. </remarks>
	 **************************************************************************************************/
	void register2DToScene();

	/**********************************************************************************************//**
	 * <summary> Deregisters Draw2D from current scene.</summary>
	 *
	 * <remarks> </remarks>
	 **************************************************************************************************/
	void deregister2DFromScene();

	/**********************************************************************************************//**
	 * <summary> Draw callback this object.</summary>
	 * \ingroup DRAW
	 * <remarks> To be implemented by user in object derived from GameObject (NOT directly derived from Drawable).
	 * 			 Called ONLY by current active scene.
	 * 			 </remarks>
	 **************************************************************************************************/
	virtual void draw();

	/**********************************************************************************************//**
	 * <summary> Draw2D callback for this object.</summary>
	 * \ingroup DRAW
	 * <remarks> To be implemented by user in object derived from GameObject (NOT directly derived from Drawable).
	 * 			 Called ONLY by current active scene.
	 * 			 NOTE: Used only to render Sprite Entities
	 * 			 </remarks>
	 **************************************************************************************************/
	virtual void draw2D();

private:
	// for 3d rendering
	DrawableManager::StorageListReference _deleteReference;

	DrawRegistrationCommand* _pDrawRegistrationCommand;
	DrawDeregistrationCommand* _pDrawDeregistrationCommand;

	RegistrationState _currentRegistrationState;

	// for 2d rendering
	Drawable2DManager::StorageListReference _deleteReference2D;

	Draw2DRegistrationCommand* _pDraw2DRegistrationCommand;
	Draw2DDeregistrationCommand* _pDraw2DDeregistrationCommand;

	RegistrationState _currentRegistrationState2D;

private:
	// For personal debugging
	static void DebugPrint(const std::string& message);
	static const std::string DEBUG_TITLE_MESSAGE;
};

// For personal debugging
#ifndef Drawable_DEBUG
#define Drawable_DEBUG false
#endif // !Drawable_DEBUG

#endif // !_Drawable

//-----------------------------------------------------------------------------------------------------------------------------
//  DRAWABLE COMMENT TEMPLATE
//-----------------------------------------------------------------------------------------------------------------------------