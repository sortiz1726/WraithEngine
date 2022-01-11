#include "GroundPlane.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"

const int GroundPlane::UV_LENGTH = 5;
const int GroundPlane::SQUARE_LENGTH = 1000;

GroundPlane::GroundPlane()
	: GroundPlane("GrassDirtTexture")
{}

GroundPlane::GroundPlane(const std::string& textureName)
	: GroundPlane(textureName, 
		GroundPlane::SQUARE_LENGTH, 
		GroundPlane::SQUARE_LENGTH / UV_LENGTH, 
		GroundPlane::SQUARE_LENGTH / UV_LENGTH)
{}

GroundPlane::GroundPlane(const std::string& textureName, int size, int Urepeat, int Vrepeat)
	: _pGroundPlaneGraphicsObject(nullptr)
{
	Model* pPlaneModel = new Model(size, Urepeat, Vrepeat);
	ShaderObject* pTextureShader = ShaderManager::GetDefaultShader(ShaderManager::DefaultShader::TEXTURE);
	Texture* pPlaneTexture = TextureManager::GetTexture(textureName);

	_pGroundPlaneGraphicsObject = new GraphicsObject_TextureFlat(pPlaneModel, pTextureShader, pPlaneTexture);

	Matrix world = Matrix(IDENTITY);
	_pGroundPlaneGraphicsObject->SetWorld(world);

	submitDrawRegistration();
}

GroundPlane::~GroundPlane()
{
	delete _pGroundPlaneGraphicsObject->getModel();
	delete _pGroundPlaneGraphicsObject;
}

void GroundPlane::draw()
{
	Camera* pCamera = SceneManager::GetCurrentScene()->getCurrentCamera();
	_pGroundPlaneGraphicsObject->Render(pCamera);
}
