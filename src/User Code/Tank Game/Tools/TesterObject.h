#ifndef _TesterObject
#define _TesterObject

#include <vector>
#include <string>

#include "GameObject.h"
#include "SpriteFont.h"
#include "SpriteString.h"

class TesterObject : public GameObject
{
public:
	TesterObject();
	TesterObject(const TesterObject&) = default;
	TesterObject& operator=(const TesterObject&) = default;
	TesterObject(TesterObject&&) = default;
	TesterObject& operator=(TesterObject&&) = default;
	~TesterObject();

private:
	virtual void update() override;
	virtual void draw() override;
	virtual void draw2D() override;
	virtual void keyPressed(AZUL_KEY) override;

	void initializeTestModels();
	void initializeTestSprites();
	Sprite* createSprite(const std::string& imageKey);

	void drawModels();
	void drawSprites();

private:
	std::vector<GraphicsObject*> _graphicsObjects;
	std::vector<Sprite*> _sprites;

	Sprite* _pSpriteSquare;
};
#endif // !_TesterObject

//-----------------------------------------------------------------------------------------------------------------------------
// TesterObject Comment Template
//-----------------------------------------------------------------------------------------------------------------------------