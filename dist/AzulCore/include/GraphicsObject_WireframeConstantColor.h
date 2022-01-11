#ifndef GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H
#define GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H

#include "GraphicsObject.h"

class GraphicsObject_WireframeConstantColor :public GraphicsObject
{
public:
	GraphicsObject_WireframeConstantColor(Model *model, ShaderObject *pShaderObj, Vect &wireColor);
	~GraphicsObject_WireframeConstantColor();

	void SetColor(const Vect& col) { *(this->pWireColor) = col; }

protected:
	// Rendermaterial contract
	virtual void privSetState() override;
	virtual void privSetDataGPU( Camera *pCam ) override;	
	virtual void privDraw() override;
	virtual void privRestoreState() override;

// data:  place uniform instancing here
	Vect *pWireColor;

	GraphicsObject_WireframeConstantColor() = delete;

};
#endif