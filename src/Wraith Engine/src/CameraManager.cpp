#include "CameraManager.h"
#include "Camera.h"
#include "Wraith.h"

//---------------------------------------------------------------------------------------------------------
// Initializing Camera Manager
//---------------------------------------------------------------------------------------------------------
CameraManager::CameraManager()
{
	_pDefaultCamera = createDefaultCamera();
	_pDefault2DCamera = CameraManager::Create2DCamera();
	setDefaultCameraAsCurrentCamera();
	setDefault2DCameraAsCurrentCamera();
}

// ---> Initializing Camera Manager helper
Camera* CameraManager::createDefaultCamera()
{
	Vect pos3DCam(10.0f, 10.0f, 30.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	return CameraManager::CreateCamera(pos3DCam, lookAt3DCam);
}

//-----------------------------------------------------------------------------------------------------------------------------
// Deinitializing Camera Manager
//-----------------------------------------------------------------------------------------------------------------------------
CameraManager::~CameraManager()
{
	//Trace::out("Camera Manager: Deleting Camera Manager\n");
	delete _pDefaultCamera;
	delete _pDefault2DCamera;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setting Camera
//-----------------------------------------------------------------------------------------------------------------------------
void CameraManager::setDefaultCameraAsCurrentCamera()
{
	setCurrentCamera(_pDefaultCamera);
}

void CameraManager::setCurrentCamera(Camera* pCamera)
{
	_pCurrentCamera = pCamera;
}

void CameraManager::setDefault2DCameraAsCurrentCamera()
{
	setCurrent2DCamera(_pDefault2DCamera);
}

void CameraManager::setCurrent2DCamera(Camera* p2DCamera)
{
	_pCurrent2DCamera = p2DCamera;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getting Camera
//-----------------------------------------------------------------------------------------------------------------------------
Camera* CameraManager::getCurrentCamera() const
{
	return _pCurrentCamera;
}

Camera* CameraManager::getCurrent2DCamera() const
{
	return _pCurrent2DCamera;
}
					   
Camera* CameraManager::getDefaultCamera() const
{
	return _pDefaultCamera;
}

Camera* CameraManager::getDefault2DCamera() const
{
	return _pDefault2DCamera;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Personal function for creating a quick camera Camera (not neccessarily a essential to the manager)
//-----------------------------------------------------------------------------------------------------------------------------
Camera* CameraManager::CreateCamera(const Vect& position, const Vect& lookAt)
{
	Camera* pCamera = new Camera(Camera::Type::PERSPECTIVE_3D);

	// Default settings
	// viewport, perspective, and up direction
	pCamera->setViewport(0, 0, Wraith::GetWindowWidth(), Wraith::GetWindowHeight());
	pCamera->setPerspective(35.0f, float(Wraith::GetWindowWidth()) / float(Wraith::GetWindowHeight()), 1.0f, 5000.0f);
	// Default Orient Camera
	Vect upVector(0.0f, 1.0f, 0.0f);

	pCamera->setOrientAndPosition(upVector, lookAt, position);
	pCamera->updateCamera();  // Note: if the camera moves/changes, we need to call update again

	return pCamera;
}

Camera* CameraManager::Create2DCamera()
{
	Camera* p2DCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D);

	p2DCamera->setViewport(0, 0, Wraith::GetWindowWidth(), Wraith::GetWindowHeight());
	p2DCamera->setOrthographic(-0.5f * Wraith::GetWindowWidth(), 0.5f * Wraith::GetWindowWidth(), 
								-0.5f * Wraith::GetWindowHeight(), 0.5f * Wraith::GetWindowHeight(), 
								1.0f, 1000.0f);

	Vect up(0.0f, 1.0f, 0.0f);
	Vect cameraPosition(0.0f, 0.0f, 0.0f);
	Vect cameraLookAt(0.0f, 0.0f, -1.0f);

	p2DCamera->setOrientAndPosition(up, cameraLookAt, cameraPosition);
	p2DCamera->updateCamera();

	return p2DCamera;
}
