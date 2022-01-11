#include "CameraController.h"
#include "CameraManager.h"
#include "TimeManager.h"
#include "vmath.h"
#include "ScreenLog.h"

Vect CameraController::CameraUp = Vect(0.0f, 1.0f, 0.0f);
Vect CameraController::mousePosition = Vect(0.0f, 0.0f, 0.0f);
Vect CameraController::mousePositionDelta = Vect(0.0f, 0.0f, 0.0f);
float CameraController::speedPercentage = 1.0f;


CameraController::CameraController()
	: _moveSpeed(50.0f),
	_turnSpeed(100.0f),
	_operationStatus(Status::OPERATIONAL)
{
	Mouse::SetWheel(25);
}

CameraController::~CameraController()
{
	//Trace::out("\n-----------------------------------------\n");
	//Trace::out("CameraController: Destructor Called\n");
}

//-----------------------------------------------------------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------------------------------------------------------
void CameraController::update()
{
	float mouseX, mouseY;
	Mouse::GetCursor(mouseX, mouseY);
	Vect newMousePosition = Vect(mouseX, mouseY, 0.0f);

	CameraController::mousePositionDelta = newMousePosition - CameraController::mousePosition;
	CameraController::mousePosition = newMousePosition;

	float wheel;
	Mouse::GetWheel(wheel);
	if (wheel < 0.0f)
	{
		Mouse::SetWheel(0);
	}
	speedPercentage = wheel / 25.0f;

	updateCamera();

	Vect cameraPos;
	_pCamera->getPos(cameraPos);
	//ScreenLog::Add("Camera Position: (%3.1f, %3.1f, %3.1f)", cameraPos[x], cameraPos[y], cameraPos[z]);
}

void CameraController::updateCamera()
{
	Camera* pCamera = _pCamera;
	// Get Position Vector
	Vect CurrentCamPos;
	pCamera->getPos(CurrentCamPos);
	//Trace::out("Camera Position: (%f, %f)\n", CurrentCamPos[x], CurrentCamPos[y]);
	// Get Rotation Matrix
	Matrix CurrentCamRot = pCamera->getViewMatrix().getInv();
	CurrentCamRot.set(MatrixRowType::ROW_3, Vect(0, 0, 0));

	Vect CurrentCamDir;
	pCamera->getDir(CurrentCamDir);
	CurrentCamDir *= -1.0f;
	// Compute Position Offset
	Vect CamPosOffset = Vect(0.0f, 0.0f, 0.0f);
	// Camera translation movement
	float moveOffset = _moveSpeed * speedPercentage * TimeManager::GetElaspedFrameTimeInSeconds();
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
	{
		CamPosOffset += Vect(0, 0, 1) * CurrentCamRot * -moveOffset;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
	{
		CamPosOffset += Vect(0, 0, 1) * CurrentCamRot * moveOffset;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
	{
		CamPosOffset += Vect(1, 0, 0) * CurrentCamRot * -moveOffset;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
	{
		CamPosOffset += Vect(1, 0, 0) * CurrentCamRot * moveOffset;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_U))
	{
		//CamRotOffset *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CurrentCamRot, -vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds());
		CamPosOffset += Vect(0, 1, 0) * CurrentCamRot * moveOffset;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_O))
	{
		//CamRotOffset *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CurrentCamRot, vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds());
		CamPosOffset += Vect(0, 1, 0) * CurrentCamRot * -moveOffset;
	}
	// Compute Rotation Offset
	Matrix CamRotOffset = Matrix(IDENTITY);
	//if (Keyboard::GetKeyState(AZUL_KEY::KEY_U))
	//{
	//	CamRotOffset *= Matrix(ROT_Y, vmath::radians(_turnSpeed ) * TimeManager::GetElaspedFrameTimeInSeconds());
	//}
	//else if (Keyboard::GetKeyState(AZUL_KEY::KEY_O))
	//{
	//	CamRotOffset *= Matrix(ROT_Y, -vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds());
	//}

	if (Mouse::GetKeyState(AZUL_MOUSE::BUTTON_LEFT))
	{
		float signX = 0;
		if (mousePositionDelta[x] != 0.0f)
		{
			signX = mousePositionDelta[x] / std::abs(mousePositionDelta[x]);
		}

		Vect localUp = Vect(0.0f, 1.0f, 0.0f) * CurrentCamRot;
		float yawOffset = -2.0f * vmath::radians(_turnSpeed * signX) * speedPercentage * TimeManager::GetElaspedFrameTimeInSeconds();
		CamRotOffset *= Matrix(ROT_AXIS_ANGLE, localUp, yawOffset);
		//CamRotOffset *= Matrix(ROT_Y, vmath::radians(_turnSpeed * signX) * TimeManager::GetElaspedFrameTimeInSeconds());

		float signY = 0;
		if (mousePositionDelta[y] != 0.0f)
		{
			signY = mousePositionDelta[y] / std::abs(mousePositionDelta[Y]);
		}

		Vect localRight = Vect(1.0f, 0.0f, 0.0f) * CurrentCamRot;
		float pitchOffset = -2.0f * vmath::radians(_turnSpeed * signY) * speedPercentage * TimeManager::GetElaspedFrameTimeInSeconds();
		CamRotOffset *= Matrix(ROT_AXIS_ANGLE, localRight, pitchOffset);

		//CamRotOffset *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CurrentCamRot, vmath::radians(_turnSpeed) * TimeManager::GetElaspedFrameTimeInSeconds());
	}

	// Update the camera settings
	Vect CurrentCamLookAt = CurrentCamPos + (CurrentCamDir * CamRotOffset);
	pCamera->setOrientAndPosition(CameraController::CameraUp, CurrentCamLookAt + CamPosOffset, CurrentCamPos + CamPosOffset);
	pCamera->updateCamera();
}

void CameraController::updateCameraV2()
{
	const float deltaTime = TimeManager::GetElaspedFrameTimeInSeconds();
	// Translation offset
	float forwardValue = static_cast<float>(Keyboard::GetKeyState(AZUL_KEY::KEY_K) - Keyboard::GetKeyState(AZUL_KEY::KEY_I));
	float upOffValue = static_cast<float>(Keyboard::GetKeyState(AZUL_KEY::KEY_Y) - Keyboard::GetKeyState(AZUL_KEY::KEY_H));
	float leftValue = static_cast<float>(Keyboard::GetKeyState(AZUL_KEY::KEY_L) - Keyboard::GetKeyState(AZUL_KEY::KEY_J));

	Vect forwardDirection = Vect(0.0f, 0.0f, forwardValue) * _cameraRotation;
	Vect upDirection = Vect(0.0f, upOffValue, 0.0f) * _cameraRotation;
	Vect leftDirection = Vect(leftValue, 0.0f, 0.0f) * _cameraRotation;

	Vect translationDirection = (forwardDirection + upDirection + leftDirection).getNorm();

	Vect translationOffset = translationDirection * _moveSpeed * deltaTime;
	Matrix translationMatrix = Matrix(TRANS, translationOffset);

	_cameraPosition *= translationMatrix;

	// Rotation Offset
	float yawValue = static_cast<float>(Keyboard::GetKeyState(AZUL_KEY::KEY_U) - Keyboard::GetKeyState(AZUL_KEY::KEY_O));
	float pitchValue = static_cast<float>(Keyboard::GetKeyState(AZUL_KEY::KEY_P) - Keyboard::GetKeyState(AZUL_KEY::KEY_SEMICOLON));

	float yawOffset = yawValue * vmath::radians(_turnSpeed) * deltaTime;
	float pitchOffset = pitchValue * vmath::radians(_turnSpeed) * deltaTime;

	//_cameraRotation *= Matrix(ROT_AXIS_ANGLE, upDirection, yawOffset);
	_cameraRotation *= Matrix(ROT_X, pitchOffset);
	_cameraRotation *= Matrix(ROT_Y, yawOffset);

	Vect cameraPosition = Vect(0.0f, 0.0, 0.0f) * _cameraRotation * Matrix(TRANS, _cameraPosition);
	Vect cameraLookAt = _cameraLookAtOffset * _cameraRotation * Matrix(TRANS, _cameraPosition);
	_pCamera->setOrientAndPosition(CameraController::CameraUp, cameraLookAt, cameraPosition);
	_pCamera->updateCamera();
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setters/Getters
//-----------------------------------------------------------------------------------------------------------------------------
void CameraController::setCamera(Camera* pCamera)
{
	assert(pCamera != nullptr);
	_pCamera = pCamera;

	// Get Camera Position
	_cameraPosition;
	pCamera->getPos(_cameraPosition);

	// Get Rotation Matrix
	_cameraRotation = pCamera->getViewMatrix().getInv();
	_cameraRotation.set(MatrixRowType::ROW_3, Vect(0, 0, 0));

	// Update the camera settings
	Vect currentCameraDirection;
	pCamera->getDir(currentCameraDirection);
	_cameraLookAtOffset = _cameraPosition - currentCameraDirection;
	_cameraLookAtOffset *= (_cameraRotation * Matrix(TRANS, _cameraPosition)).getInv();
}

Camera* CameraController::getCamera() const
{
	return _pCamera;
}

void CameraController::setOperationStatus(Status operationStatus)
{
	_operationStatus = operationStatus;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Activation/Deactivation
//-----------------------------------------------------------------------------------------------------------------------------

void CameraController::activate()
{
	if (_operationStatus == Status::OPERATIONAL)
	{
		submitUpdateRegistration();
	}
}

void CameraController::deactivate()
{
	if (_operationStatus == Status::OPERATIONAL)
	{
		submitUpdateDeregistration();
	}
}