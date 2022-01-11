#include "SpaceFrigate.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "TimeManager.h"

#include "Visualizer.h"

SpaceFrigate::SpaceFrigate()
	: _pGraphicsObject_SpaceFrigate(nullptr),
	_pGraphicsObject_BoundingSphere(nullptr),
	_name("defaultName")
{
	//-----------------------------------------------------------------------------------------------------------------------------
	// Space Frigate
	//-----------------------------------------------------------------------------------------------------------------------------
	// Load Assets
	Model* pSpaceFrigateModel = ModelManager::GetModel("SpaceFrigate");
	ShaderObject* pLightedTextureShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::LIGHTED_TEXTURE);
	Texture* pSpaceFrigateTexture = TextureManager::GetTexture("SpaceFrigateTexture");

	// Set Up Lights
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	// Create Graphics Object
	_pGraphicsObject_SpaceFrigate = new GraphicsObject_TextureLight(pSpaceFrigateModel, pLightedTextureShader, pSpaceFrigateTexture, LightColor, LightPos);

	// Set Scale, Rotation, Position
	_shipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	_shipRotation.set(IDENTITY);
	_shipPosition.set(0, 20, 0);

	// Compute World Matrix
	Matrix world = _shipScale * _shipRotation * Matrix(TRANS, _shipPosition);

	// Set World
	_pGraphicsObject_SpaceFrigate->SetWorld(world);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Bounding Sphere
	//-----------------------------------------------------------------------------------------------------------------------------

	// Load Assets
	Model* pUnitSphereModel = ModelManager::GetModel("UnitSphere");
	ShaderObject* pShaderObject_ConstantColor = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::CONSTANT_COLOR);
	
	// Set Color
	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	Vect Red(1.0f, 0.0f, 0.0f);
	// Create Graphics Object
	_pGraphicsObject_BoundingSphere = new GraphicsObject_WireframeConstantColor(pUnitSphereModel, pShaderObject_ConstantColor, Blue);
	_pGraphicsObject_BoundingSphere2 = new GraphicsObject_WireframeConstantColor(pUnitSphereModel, pShaderObject_ConstantColor, Red);
	//-----------------------------------------------------------------------------------------------------------------------------
	// Register to Current Scene
	//-----------------------------------------------------------------------------------------------------------------------------
	submitUpdateRegistration();
	submitDrawRegistration();

	//printCurrentTime();
	//submitAlarmRegistration(1.0f, AlarmID::ALARM_0);
	submitKeyRegistration(AZUL_KEY::KEY_B, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_B, InputEvent::KEY_RELEASE);
	submitKeyRegistration(AZUL_KEY::KEY_N, InputEvent::KEY_PRESS);
	submitKeyRegistration(AZUL_KEY::KEY_N, InputEvent::KEY_RELEASE);

	Model* pModel = _pGraphicsObject_SpaceFrigate->getModel();
	Vect vect = pModel->getCenter();
	Trace::out("SpaceFrigate: Model center (%f, %f, %f)\n", vect.X(), vect.Y(), vect.Z());
	setColliderModel(pModel, VolumeType::BSPHERE);
}

SpaceFrigate::SpaceFrigate(const std::string& name)
	: SpaceFrigate()
{
	_name = name;
}

SpaceFrigate::~SpaceFrigate()
{
	Trace::out("\n-----------------------------------------\n");
	Trace::out("SpaceFrigate: Destructor Called\n");
	delete _pGraphicsObject_SpaceFrigate;
	delete _pGraphicsObject_BoundingSphere;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------------------------------------------------------
void SpaceFrigate::update()
{
	updateSpaceFrigate();
	updateBoundingSphere();
	updateCollisionData(_shipScale * _shipRotation * Matrix(TRANS, _shipPosition));
	

	Visualizer::ShowCollisionVolume(getCollisionVolume());

	// Update BSphere Graphics Object
	//const CollisionVolumeBSphere& BSphere = getCollsionBSphere();
	//Matrix world = Matrix(IDENTITY);
	//
	//Vect uniformScale = Vect(1.0f, 1.0f, 1.0f) * BSphere.getRadius();
	//world *= Matrix(SCALE, uniformScale);
	//
	//world *= Matrix(TRANS, BSphere.getWorldCenter());
	//
	//_pGraphicsObject_BoundingSphere2->SetWorld(world);
}

void SpaceFrigate::updateSpaceFrigate()
{
	// Ship translation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		_shipPosition += Vect(0, 0, 1) * _shipRotation * _shipTransSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		_shipPosition += Vect(0, 0, 1) * _shipRotation * -_shipTransSpeed;
	}

	// Ship Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		_shipRotation *= Matrix(ROT_Y, _shipRotationSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		_shipRotation *= Matrix(ROT_Y, -_shipRotationSpeed);
	}

	// Spaceship adjust matrix
	Matrix world = _shipScale * _shipRotation * Matrix(TRANS, _shipPosition);
	_pGraphicsObject_SpaceFrigate->SetWorld(world);

	/*
	// Placing the camera relative to the spaceship
	Matrix ShipRotPos = ShipRot * Matrix(TRANS, _shipPosition);  // This is the worldmat without scaling
	Vect vNewCamPos = CamLookAt * ShipRotPos;		// This moves the cam position relative to ship's position and rotation
	Vect vNewLookAt = CamShipOffset * ShipRotPos;   // This moves the look-at point relative to ship's position and rotation
	pCam3D->setOrientAndPosition( Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	pCam3D->updateCamera();
	//*/
}

void SpaceFrigate::updateBoundingSphere()
{
	//*
// Adjusting the spaceship's bounding sphere
	Vect vBSSize = _pGraphicsObject_SpaceFrigate->getModel()->getRadius() * Vect(1, 1, 1);
	Vect vBSPos = _pGraphicsObject_SpaceFrigate->getModel()->getCenter();
	Matrix world = _pGraphicsObject_SpaceFrigate->getWorld();
	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	_pGraphicsObject_BoundingSphere->SetWorld(worldBS);

	// Toggle the bounding sphere's visibility
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE))
	{
		_boundingSphereToggle = true;
		//DebugMsg::out("Bounding sphere: On\n");
	}
	else
	{
		_boundingSphereToggle = false;
		//DebugMsg::out("Bounding sphere: Off\n");
	}
	//*/
}

void SpaceFrigate::toggleDraw()
{
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_X))
	{
		if (_canToggleDrawRegistration)
		{
			if (_currentlyBeingDrawn)
			{
				submitDrawDeregistration();
				_currentlyBeingDrawn = false;
			}
			else
			{
				submitDrawRegistration();
				_currentlyBeingDrawn = true;
			}
		}

		_canToggleDrawRegistration = false;
	}
	else
	{
		_canToggleDrawRegistration = true;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Draw
//-----------------------------------------------------------------------------------------------------------------------------
void SpaceFrigate::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();

	_pGraphicsObject_SpaceFrigate->Render(pCamera);
	_pGraphicsObject_BoundingSphere2->Render(pCamera);
	if (_boundingSphereToggle)
	{
		_pGraphicsObject_BoundingSphere->Render(pCamera);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Alarm
//-----------------------------------------------------------------------------------------------------------------------------
void SpaceFrigate::alarm0()
{
	printCurrentTime();
	Trace::out("SpaceFrigate: (%s) Alarm0 triggered, will trigger again\n", _name.c_str());
	//toggleUpdate();
	submitAlarmRegistration(4.0f, AlarmID::ALARM_0);
}

void SpaceFrigate::keyPressed(AZUL_KEY key)
{
	switch (key)
	{
	case AZUL_KEY::KEY_B:
		Trace::out("SpaceFrigate: (%s) B Pressed, V key press registered\n", _name.c_str());
		submitKeyRegistration(AZUL_KEY::KEY_V, InputEvent::KEY_PRESS);
		break;
	case AZUL_KEY::KEY_N:
		Trace::out("SpaceFrigate: (%s) N Pressed, V key press deregistered\n", _name.c_str());
		submitKeyDeregistration(AZUL_KEY::KEY_V, InputEvent::KEY_PRESS);
		break;
	case AZUL_KEY::KEY_V:
		Trace::out("SpaceFrigate: (%s) V Pressed\n", _name.c_str());
		break;
	}
}

void SpaceFrigate::keyReleased(AZUL_KEY key)
{
	switch (key)
	{
	case AZUL_KEY::KEY_B:
		Trace::out("SpaceFrigate: (%s) B Released\n", _name.c_str());
		break;
	case AZUL_KEY::KEY_N:
		Trace::out("SpaceFrigate: (%s) N Released\n", _name.c_str());
		break;
	case AZUL_KEY::KEY_V:
		Trace::out("SpaceFrigate: (%s) V Released should not be detected\n", _name.c_str());
		assert(false);
		break;
	}
}

void SpaceFrigate::toggleUpdate()
{
	if (_canUpdate)
	{
		Trace::out("SpaceFrigate: (%s) Deregister Update\n", _name.c_str());
		submitUpdateDeregistration();
		_canUpdate = false;
	}
	else
	{
		Trace::out("SpaceFrigate: (%s) Register Update\n", _name.c_str());
		submitUpdateRegistration();
		_canUpdate = true;
	}
}

void SpaceFrigate::printCurrentTime() const
{
	Trace::out("SpaceFrigate: (%s) current time %f\n", _name.c_str(), TimeManager::GetTimeInSeconds());
}