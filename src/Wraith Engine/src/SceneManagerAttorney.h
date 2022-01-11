#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney

#include "SceneManager.h"

/**********************************************************************************************//**
 * <summary> A scene manager attorney for letting specific classes access
 * 			 specific private funcions within SceneManager class.</summary>
 *
 * <remarks> NEVER to be called by the user. </remarks>
 **************************************************************************************************/
class SceneManagerAttorney
{
public:
	SceneManagerAttorney() = default;
	SceneManagerAttorney(const SceneManagerAttorney&) = default;
	SceneManagerAttorney& operator=(const SceneManagerAttorney&) = default;
	SceneManagerAttorney(SceneManagerAttorney&&) = default;
	SceneManagerAttorney& operator=(SceneManagerAttorney&&) = default;
	~SceneManagerAttorney() = default;

public:
	class InitalizationAccess
	{
		friend class Wraith;

		static void InitializeStartScene() { SceneManager::InitializeStartScene(); }
	};

	class GameLoopAccess
	{
		friend class Wraith;

		static void Update() { SceneManager::Update(); }
		static void Draw() { SceneManager::Draw(); }
	};

	class SceneAccess
	{
		friend class SceneChangeCommand;

		static void ChangeScene(Scene* pSceneToChangeTo) { SceneManager::ChangeScene(pSceneToChangeTo); }
	};

	class DeleteAccess
	{
		friend class Wraith;

		static void Delete() { SceneManager::Delete(); }
	};

};
#endif // !_SceneManagerAttorney

//-----------------------------------------------------------------------------------------------------------------------------
// SceneManagerAttorney Comment Template
//-----------------------------------------------------------------------------------------------------------------------------