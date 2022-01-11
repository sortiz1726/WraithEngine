#ifndef _CameraManager
#define _CameraManager

#include "AzulCore.h"

class CameraManager
{
	friend class CameraManagerAttorney;
public:
	// Big Six
	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;
	CameraManager(CameraManager&&) = delete;
	CameraManager& operator=(CameraManager&&) = delete;
	~CameraManager();

	// Setting Current Camera
	void setDefaultCameraAsCurrentCamera();
	void setCurrentCamera(Camera*);
	void setDefault2DCameraAsCurrentCamera();
	void setCurrent2DCamera(Camera*);

	// Getting Camera
	Camera* getDefaultCamera() const;
	Camera* getDefault2DCamera() const;
	Camera* getCurrentCamera() const;
	Camera* getCurrent2DCamera() const;

	// Personal function for creating a quick camera Camera (not neccessarily a essential to the manager)
	static Camera* CreateCamera(const Vect& position, const Vect& lookAt);
	static Camera* Create2DCamera();

private:
	// ---> Initializing Camera Manager helper
	Camera* createDefaultCamera();

private:
	Camera* _pCurrentCamera;
	Camera* _pCurrent2DCamera;

	Camera* _pDefaultCamera;
	Camera* _pDefault2DCamera;
};

#endif _CameraManager

//-----------------------------------------------------------------------------------------------------------------------------
// CamerManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------