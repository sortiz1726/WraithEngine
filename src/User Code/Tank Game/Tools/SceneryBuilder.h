#ifndef _SceneryBuilder
#define _SceneryBuilder

#include <vector>

class GameObject;
class Vect;
class Warehouse;

class SceneryBuilder
{
public:
	SceneryBuilder() = default;
	SceneryBuilder(const SceneryBuilder&) = default;
	SceneryBuilder& operator=(const SceneryBuilder&) = default;
	SceneryBuilder(SceneryBuilder&&) = default;
	SceneryBuilder& operator=(SceneryBuilder&&) = default;
	~SceneryBuilder();

	void buildWindMill(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);
	Warehouse* buildWarehouse(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);
	void buildCottage(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);
	
	void buildLeaflessTree(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);
	void buildCampfire(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);

	void buildRoundArch(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);
	void buildFlatArch(const Vect& position, float rotationY = 0.0f, float uniformScale = 1.0f);

private:
	std::vector<GameObject*> _sceneryEntities;
};
#endif // !_SceneryBuilder

//-----------------------------------------------------------------------------------------------------------------------------
// SceneryBuilder Comment Template
//-----------------------------------------------------------------------------------------------------------------------------