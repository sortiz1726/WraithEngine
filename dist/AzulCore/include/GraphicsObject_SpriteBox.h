#ifndef GRAPHICS_OBJECT_BOX_H
#define GRAPHICS_OBJECT_BOX_H

#include <sb6.h>
#include "MathEngine.h"
#include "GraphicsObject.h"
#include "Rect.h"

class GraphicsObject_SpriteBox : public GraphicsObject
{
public:
	GraphicsObject_SpriteBox(Model *model, ShaderObject *pShaderObj, Rect *pRect, Vect &Color);
	~GraphicsObject_SpriteBox();

	void SetColor(const Vect& col) { *(this->pColor) = col; }

protected:
	// Rendermaterial contract
	virtual void privSetState() override;
	virtual void privSetDataGPU( Camera *pCam ) override;
	virtual void privDraw() override;
	virtual void privRestoreState() override;

	Vect	*pColor;

public:
	// data:  place uniform instancing here


	float origWidth;
	float origHeight;

	float origPosX;
	float origPosY;

private:
	Matrix  *pMatrix_orig;
};
#endif