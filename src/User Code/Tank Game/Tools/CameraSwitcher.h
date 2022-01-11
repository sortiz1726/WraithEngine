#ifndef _CameraSwitcher
#define _CameraSwitcher

#include <vector>
#include "GameObject.h"
#include "CameraController.h"

class Camera;

class CameraSwitcher : public GameObject
{
private:
	typedef std::vector<CameraController*> StorageContainer;
public:
	CameraSwitcher();
	CameraSwitcher(const CameraSwitcher&) = default;
	CameraSwitcher& operator=(const CameraSwitcher&) = default;
	CameraSwitcher(CameraSwitcher&&) = default;
	CameraSwitcher& operator=(CameraSwitcher&&) = default;
	~CameraSwitcher();

	void addCamera(CameraController*);
	void addCamera(Camera*, CameraController::Status status = CameraController::Status::NON_OPERATIONAL);
	CameraController* createTemporaryController(Camera* pCamera, CameraController::Status status);

	void setActive(int index);

private:
	// Inputable
	virtual void keyPressed(AZUL_KEY) override;
	void offsetActiveCameraIndex(int offset);
	void useActiveCamera();

private:
	StorageContainer _cameras;
	StorageContainer _temporaryCameraControllers;
	int _activeCameraIndex;
};
#endif // !_CameraSwitcher

//-----------------------------------------------------------------------------------------------------------------------------
// CameraSwitcher Comment Template
//-----------------------------------------------------------------------------------------------------------------------------