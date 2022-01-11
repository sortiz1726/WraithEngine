#ifndef MODEL_H
#define MODEL_H

class Vect;
struct TriangleIndex;
struct VertexStride_VUN;

class Model
{
private:
	Vect *pVect;
	TriangleIndex *pTriList;

	char *textNames;

	unsigned int vao;
	unsigned int vbo[2];

	// Model information
	int numTextures;
	int numVerts;
	int numTris;

	// Bounding Sphere: bounding volume
	Vect *center;
	float radius;

	// AABB: axis aligned bounding box
	// Specifies the minimum extent of this AABB in the world space x, y and z axes.
	Vect *minPointAABB;
	// Specifies the maximum extent of this AABB in the world space x, y and z axes
	Vect *maxPointAABB;

	void privCreateVAO(VertexStride_VUN *pVerts, int nverts, TriangleIndex *pTriList, int ntri);
	void privCreateVAOFromFile(const char * const _modelName);
	void privBindAndLoadGPU(VertexStride_VUN *pVerts, int nverts, TriangleIndex *pTriList, int ntri);
	void privSetExtraData(Vect* MinAABB, Vect* MaxAABB, Vect* c, float r, int tex_num, char *texturenames, int size_texnames);

public:

	enum class PreMadeModels {
		UnitSquareXY,
		UnitBox_WF,
		UnitSphere
	};

	Model(const char * const _modelName);
	Model(VertexStride_VUN *pVerts, int nverts, TriangleIndex *pTriList, int ntri);
	Model(PreMadeModels pm);
	Model(int vertical_slices, int hor_slices);
	Model(int sizeXZ, int repeatU, int repeatV);

	Model(VertexStride_VUN *pVerts, int nverts, TriangleIndex *pTriList, int ntri, Vect* MinAABB, Vect* MaxAABB, Vect* c, float r, int tex_num, char *texturenames, int size_texnames);

	virtual ~Model();

	// Get the texture name
	char *getTextureName(int index);

	// Get access
	Vect* getVectList(void) const;
	int getVectNum() const
	{ 
		return numVerts; 
	}
	TriangleIndex *getTriangleList(void) const;
	int getTriNum() const
	{ 
		return numTris; 
	};
	int getTextureNum() const
	{ 
		return numTextures; 
	};
	unsigned int getvao() const { return vao; }

	Vect& getCenter() const { return *center; }
	float getRadius() const { return radius; }
	Vect& getMinAABB() const { return *minPointAABB; }
	Vect& getMaxAABB() const { return *maxPointAABB; }

};


#endif