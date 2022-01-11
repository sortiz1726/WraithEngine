#include "CameraSwitcher.h"
#include "CameraManager.h"
#include "CameraController.h"
#include "SceneManager.h"

CameraSwitcher::CameraSwitcher()
	: _activeCameraIndex(0)
{
	submitKeyRegistration(AZUL_KEY::KEY_ARROW_LEFT, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_ARROW_RIGHT, InputEvent::KEY_PRESS);
	addCamera(SceneManager::GetCurrentScene()->getDefaultCamera(), CameraController::Status::OPERATIONAL);
	_cameras.at(0)->activate();
}

CameraSwitcher::~CameraSwitcher()
{
	for (CameraController* pCameraController : _temporaryCameraControllers)
	{
		delete pCameraController;
	}
	_cameras.clear();
}

void CameraSwitcher::addCamera(Camera* pCamera, CameraController::Status status)
{
	CameraController* pCameraController = createTemporaryController(pCamera, status);
	_cameras.push_back(pCameraController);
}

CameraController* CameraSwitcher::createTemporaryController(Camera* pCamera, CameraController::Status status)
{
	CameraController* pCameraController = new CameraController();
	pCameraController->setCamera(pCamera);
	pCameraController->setOperationStatus(status);
	_temporaryCameraControllers.push_back(pCameraController);
	return pCameraController;
}

void CameraSwitcher::setActive(int index)
{
	CameraController* pCameraController = _cameras.at(_activeCameraIndex);
	pCameraController->deactivate();

	_activeCameraIndex = index;

	useActiveCamera();
}

void CameraSwitcher::addCamera(CameraController* pCameraController)
{
	_cameras.push_back(pCameraController);
}

void CameraSwitcher::keyPressed(AZUL_KEY key)
{
	switch (key)
	{
	case AZUL_KEY::KEY_ARROW_LEFT:
		offsetActiveCameraIndex(-1);
		break;
	case AZUL_KEY::KEY_ARROW_RIGHT:
		offsetActiveCameraIndex(1);
		break;
	}
}

void CameraSwitcher::offsetActiveCameraIndex(int offset)
{
	CameraController* pCameraController = _cameras.at(_activeCameraIndex);
	pCameraController->deactivate();

	_activeCameraIndex += offset;
	if (_activeCameraIndex == -1)
	{
		_activeCameraIndex = _cameras.size() - 1;
	}
	else
	{
		_activeCameraIndex %= _cameras.size();
	}

	useActiveCamera();
}

void CameraSwitcher::useActiveCamera()
{
	CameraController* pCameraController = _cameras.at(_activeCameraIndex);
	pCameraController->activate();
	Camera* pCamera = pCameraController->getCamera();
	SceneManager::GetCurrentScene()->setCurrentCamera(pCamera);
}
