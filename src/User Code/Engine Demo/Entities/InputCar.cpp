#include "InputCar.h"

// include Resource Managers header files
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

// include Scene Manager and Scene header files
#include "SceneManager.h"
#include "Scene.h"

InputCar::InputCar()
{
	// Get Resources from Managers using user defined keys.
	Model* pCarModel = ModelManager::GetModel("Car");
	// Shader Manager takes in keys and enums for shaders. (Enums are for preloaded shaders)
	ShaderObject* pCarShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pCarTexture = TextureManager::GetTexture("CarTexture");

	// Initialize a Graphics Object 
	_pCarGraphicsObject = new GraphicsObject_TextureFlat(pCarModel, pCarShader, pCarTexture);

	// Initialize world matrix.
	Matrix scale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix rotation = Matrix(IDENTITY);
	Matrix translation = Matrix(TRANS, 0.0f, 0.0f, 0.0f);

	Matrix world = scale * rotation * translation;

	_pCarGraphicsObject->SetWorld(world);

	// Submit Registrations
	submitDrawRegistration();

	// Submit key registrations. In this case both key pressed and released events
	submitKeyRegistration(AZUL_KEY::KEY_W, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_W, InputEvent::KEY_RELEASE);

	submitKeyRegistration(AZUL_KEY::KEY_A, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_A, InputEvent::KEY_RELEASE);

	submitKeyRegistration(AZUL_KEY::KEY_S, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_S, InputEvent::KEY_RELEASE);

	submitKeyRegistration(AZUL_KEY::KEY_D, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_D, InputEvent::KEY_RELEASE);
}

InputCar::~InputCar()
{
	delete _pCarGraphicsObject;
}

void InputCar::draw()
{
	// Get Camera for drawing graphics object
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();

	// Then for every graphics object call render and pass in the camera
	_pCarGraphicsObject->Render(pCamera);
}

void InputCar::keyPressed(AZUL_KEY key)
{
	// Setting position depending on key.
	Matrix translation(TRANS, 0.0f, 0.0f, 0.0f);

	// using switch statement to test which key was released
	switch (key)
	{
	case AZUL_KEY::KEY_W:
		Trace::out("InputCar: W pressed\n");
		translation = Matrix(TRANS, 0.0f, 0.0f, 5.0f);
		break;
	case AZUL_KEY::KEY_A:
		Trace::out("InputCar: A pressed\n");
		translation = Matrix(TRANS, -5.0f, 0.0f, 0.0f);
		break;
	case AZUL_KEY::KEY_S:
		Trace::out("InputCar: S pressed\n");
		translation = Matrix(TRANS, 0.0f, 0.0f, -5.0f);
		break;
	case AZUL_KEY::KEY_D:
		Trace::out("InputCar: D pressed\n");
		translation = Matrix(TRANS, 5.0f, 0.0f, 0.0f);
		break;
	default:
		break;
	}

	_pCarGraphicsObject->SetWorld(translation);
}

void InputCar::keyReleased(AZUL_KEY key)
{
	// Setting position depending on key.
	Matrix translation(TRANS, 0.0f, 0.0f, 0.0f);

	// using switch statement to test which key was released
	switch (key)
	{
	case AZUL_KEY::KEY_W:
		Trace::out("InputCar: W released\n");
		translation = Matrix(TRANS, 0.0f, 0.0f, 1.0f);
		break;
	case AZUL_KEY::KEY_A:
		Trace::out("InputCar: A released\n");
		translation = Matrix(TRANS, -1.0f, 0.0f, 0.0f);
		break;
	case AZUL_KEY::KEY_S:
		Trace::out("InputCar: S released\n");
		translation = Matrix(TRANS, 0.0f, 0.0f, -1.0f);
		break;
	case AZUL_KEY::KEY_D:
		Trace::out("InputCar: W released\n");
		translation = Matrix(TRANS, 1.0f, 0.0f, 0.0f);
		break;
	default:
		break;
	}

	_pCarGraphicsObject->SetWorld(translation);
}
