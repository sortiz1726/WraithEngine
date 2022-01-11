#ifndef _CameraController
#define _CameraController

#include "GameObject.h"

class CameraController : public GameObject
{
public:
	enum class Status
	{
		OPERATIONAL, NON_OPERATIONAL
	};

public:
	CameraController();
	CameraController(const CameraController&) = default;
	CameraController& operator=(const CameraController&) = default;
	CameraController(CameraController&&) = default;
	CameraController& operator=(CameraController&&) = default;
	~CameraController();

	void setCamera(Camera*);
	Camera* getCamera() const;
	void setOperationStatus(Status);

	void activate();
	void deactivate();

private:
	virtual void update() override;
	void updateCamera();
	void updateCameraV2();

private:
	static Vect CameraUp;
	Camera* _pCamera;

	float _moveSpeed;
	float _turnSpeed;

	Status _operationStatus;

	// Internals
	Matrix _cameraRotation;
	Vect _cameraPosition;
	Vect _cameraLookAtOffset;

	static Vect mousePosition;
	static Vect mousePositionDelta;
	static float speedPercentage;
};

#endif // !_CameraController

//-----------------------------------------------------------------------------------------------------------------------------
// CameraController Comment Template
//-----------------------------------------------------------------------------------------------------------------------------