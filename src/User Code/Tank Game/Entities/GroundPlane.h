#ifndef _GroundPlane
#define _GroundPlane

#include "GameObject.h"

class GroundPlane : public GameObject
{
public:
	GroundPlane();
	GroundPlane(const GroundPlane&) = default;
	GroundPlane& operator=(const GroundPlane&) = default;
	GroundPlane(GroundPlane&&) = default;
	GroundPlane& operator=(GroundPlane&&) = default;
	~GroundPlane();

	GroundPlane(const std::string& textureName);
	GroundPlane(const std::string& textureName, int size, int Urepeat, int Vrepeat);

private:
	virtual void draw() override;

private:
	GraphicsObject_TextureFlat* _pGroundPlaneGraphicsObject;

	const static int UV_LENGTH;
	const static int SQUARE_LENGTH;
};
#endif // !_GroundPlane

//-----------------------------------------------------------------------------------------------------------------------------
// GroundPlane Comment Template
//-----------------------------------------------------------------------------------------------------------------------------