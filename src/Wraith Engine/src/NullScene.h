#ifndef _NullScene
#define _NullScene

#include "Scene.h"

class NullScene : public Scene
{
public:
	NullScene() = default;
	NullScene(const NullScene&) = default;
	NullScene& operator=(const NullScene&) = default;
	NullScene(NullScene&&) = default;
	NullScene& operator=(NullScene&&) = default;
	~NullScene() = default;

	// Inherited via Scene
	virtual void initialize() override;
	virtual void sceneEnd() override;
};

#endif // !_NullScene

//-----------------------------------------------------------------------------------------------------------------------------
// NullScene Comment Template
//-----------------------------------------------------------------------------------------------------------------------------