#ifndef _DrawableAttorney
#define _DrawableAttorney

#include "Drawable.h"

class DrawableAttorney
{
private:
	DrawableAttorney() = delete;
	DrawableAttorney(const DrawableAttorney&) = delete;
	DrawableAttorney& operator=(const DrawableAttorney&) = delete;
	DrawableAttorney(DrawableAttorney&&) = delete;
	DrawableAttorney& operator=(DrawableAttorney&&) = delete;
	~DrawableAttorney() = delete;

public:
	class DrawAccess
	{
		friend class DrawableManager;
		friend class Drawable2DManager;

		static void Draw(Drawable* pDrawable) { pDrawable->draw(); }
		static void Draw2D(Drawable* pDrawable) { pDrawable->draw2D(); };
	};

	class RegistrationAccess
	{
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand;
		friend class Draw2DRegistrationCommand;
		friend class Draw2DDeregistrationCommand;

		static void RegisterToScene(Drawable* pDrawable) { pDrawable->registerToScene(); }
		static void DeregisterFromScene(Drawable* pDrawable) { pDrawable->deregisterFromScene(); }
		static void Register2DToScene(Drawable* pDrawable) { pDrawable->register2DToScene(); }
		static void Deregister2DFromScene(Drawable* pDrawable) { pDrawable->deregister2DFromScene(); }
	};

	class FieldAccess
	{
		friend class DrawableManager;
		friend class Drawable2DManager;

		static void SetDeleteReference(Drawable* pDrawable, const DrawableManager::StorageListReference& deleteReference)
		{
			pDrawable->setDeleteReference(deleteReference);
		}

		static DrawableManager::StorageListReference GetDeleteReference(Drawable* pDrawable)
		{
			return pDrawable->getDeleteReference();
		}

		static void SetDeleteReference2D(Drawable* pDrawable, const Drawable2DManager::StorageListReference& deleteReference2D)
		{
			pDrawable->setDeleteReference2D(deleteReference2D);
		}

		static Drawable2DManager::StorageListReference GetDeleteReference2D(Drawable* pDrawable)
		{
			return pDrawable->getDeleteReference2D();
		}
	};

};
#endif // !_DrawableAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// DrawableAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------