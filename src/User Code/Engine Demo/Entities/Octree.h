#ifndef _Octree
#define _Octree

#include <array>
#include "GameObject.h"

class Octree
{
public:
	Octree();
	Octree(const Octree&) = default;
	Octree& operator=(const Octree&) = default;
	Octree(Octree&&) = default;
	Octree& operator=(Octree&&) = default;
	~Octree();

	void setColliderModel(Model* pModel, int depth = 1);
	void render(Camera*);
	void render(Camera*, int depth);

	void update(const Matrix& worldMatrix);

private:
	void computeData(Model* pModel, const Matrix& world, int depth);
	void setColliderModel(const Vect& vertex, Model* pModel, const Matrix world, int depth);
	
	Octree(Model* pModel, const Matrix& world);
	int computeOctantIndex(const Vect&, const Vect& minVect, const Vect& maxVect);
	Octree* createOctantAtIndex(int index, Model* pModel, const Matrix& world);
	void generateMoreOctrees(const Vect& vect, int depth);

	void initialize(Model* pModel, const Matrix& world);

	bool doesBoxContainModel() const;
	bool isPointWithin(const Vect&) const;

	void setMinAndMax(const Vect& min, const Vect& max);
private:
	GraphicsObject_WireframeConstantColor* _pBoxGraphicsObject;
	std::array<Octree*, 8> _octrees;
	Matrix _matrix;
	Matrix _originalWorld;
	Model* _pColliderModel;
	Vect _maxVert;
	Vect _minVert;
};
#endif // !_Octree

//-----------------------------------------------------------------------------------------------------------------------------
// Octree Comment Template
//-----------------------------------------------------------------------------------------------------------------------------