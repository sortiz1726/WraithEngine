#include "Wraith.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "SpriteFontManager.h"
#include "TerrainObjectManager.h"

#include "MainMenu.h"
#include "TestScene4Sprites.h"
#include "TestScene.h"
#include "NullScene.h"
#include "Level2.h"
#include "Level3.h"
#include "Level1.h"
#include "MissionFailed.h"

// -----------------------------------------------------------------------------
// To be defined by user (Specific to each game)
// -----------------------------------------------------------------------------
void Wraith::loadResources()
{
	Wraith::PrintTitleMessage("Loading Resources");
	//---------------------------------------------------------------------------------------------------------
	// Load Models
	//---------------------------------------------------------------------------------------------------------

	// Model from file ( .azul format)
	ModelManager::LoadModelAndAssignKey("Axis.azul", "Axis");
	ModelManager::LoadModelAndAssignKey("Plane.azul", "Plane");
	ModelManager::LoadModelAndAssignKey("space_frigate.azul", "SpaceFrigate");
	ModelManager::LoadModelAndAssignKey(Model::PreMadeModels::UnitSphere, "UnitSphere");
	ModelManager::LoadModelAndAssignKey(Model::PreMadeModels::UnitBox_WF, "UnitCube");
	ModelManager::LoadModelAndAssignKey("Car.azul", "Car");

	// Tank Game
	ModelManager::LoadModelAndAssignKey("Tank\\TankBody.azul", "TankBody");
	ModelManager::LoadModelAndAssignKey("Tank\\TankBodyHitBox.azul", "TankBodyHitBox");
	ModelManager::LoadModelAndAssignKey("Tank\\TankTurret.azul", "TankTurret");
	ModelManager::LoadModelAndAssignKey("Tank\\TankBarrel.azul", "TankBarrel");
	ModelManager::LoadModelAndAssignKey("Tank\\Bullet.azul", "Bullet");

	ModelManager::LoadModelAndAssignKey("TurretBase.azul", "TurretBase");
	ModelManager::LoadModelAndAssignKey("TurretHead.azul", "TurretHead");

	ModelManager::LoadModelAndAssignKey("Cottage.azul", "Cottage");
	ModelManager::LoadModelAndAssignKey("Buildings\\Warehouse.azul", "Warehouse");
	ModelManager::LoadModelAndAssignKey("Buildings\\WindMill.azul", "WindMill");
	ModelManager::LoadModelAndAssignKey("Buildings\\Cottage1.azul", "Cottage1");
	ModelManager::LoadModelAndAssignKey("Buildings\\Wall.azul", "Wall");
	ModelManager::LoadModelAndAssignKey("Buildings\\Arch_1.azul", "RoundArch");
	ModelManager::LoadModelAndAssignKey("Buildings\\Arch_2.azul", "FlatArch");

	ModelManager::LoadModelAndAssignKey("Environment\\Campfire.azul", "Campfire");
	ModelManager::LoadModelAndAssignKey("Environment\\Tree.azul", "Tree");

	ModelManager::LoadModelAndAssignKey("Target.azul", "TargetModel");

	//---------------------------------------------------------------------------------------------------------
	// Load Shaders
	//---------------------------------------------------------------------------------------------------------

	ShaderManager::LoadShaderAndAssignKey("colorNoTextureRender", "colorNoTexture");
	//ShaderManager::LoadShaderAndAssignKey("textureFlatRender", "texture");
	//ShaderManager::LoadShaderAndAssignKey("textureLightRender", "textureLight");
	//ShaderManager::LoadShaderAndAssignKey("colorConstantRender", "constantColor");

	//---------------------------------------------------------------------------------------------------------
	// Load Textures
	//---------------------------------------------------------------------------------------------------------
	
	TextureManager::LoadTextureAndAssignKey("space_frigate.tga", "SpaceFrigateTexture");
	TextureManager::LoadTextureAndAssignKey("grid.tga", "GridTexture");
	TextureManager::LoadTextureAndAssignKey(128, 128, 128, "Grey");
	TextureManager::LoadTextureAndAssignKey(254, 0, 0, "Red");
	TextureManager::LoadTextureAndAssignKey(0, 254, 0, "Green");
	TextureManager::LoadTextureAndAssignKey(0, 0, 254, "Blue");
	TextureManager::LoadTextureAndAssignKey("CarTexture.tga", "CarTexture");
	TextureManager::LoadTextureAndAssignKey("CarTexture2.tga", "OtherCarTexture");
	TextureManager::LoadTextureAndAssignKey("HMTest1.tga", "HMTest16");

	// Tank Game
	TextureManager::LoadTextureAndAssignKey("Tank\\TigerTank.tga", "TankTexture");
	TextureManager::LoadTextureAndAssignKey("Tank\\Bullet.tga", "BulletTexture");
	TextureManager::LoadTextureAndAssignKey("TurretTexture.tga", "TurretTexture");

	TextureManager::LoadTextureAndAssignKey("brick-wall.tga", "BrickWallTexture");
	TextureManager::LoadTextureAndAssignKey("RoofTexture.tga", "RoofTexture");
	TextureManager::LoadTextureAndAssignKey("CabinTexture.tga", "CabinTexture");
	TextureManager::LoadTextureAndAssignKey("Chimneytexture.tga", "ChimneyTexture");
	TextureManager::LoadTextureAndAssignKey("Buildings\\Warehouse.tga", "WarehouseTexture");
	TextureManager::LoadTextureAndAssignKey("Buildings\\Cottage1.tga", "Cottage1Texture");
	TextureManager::LoadTextureAndAssignKey("Buildings\\WindMill.tga", "WindMillTexture");
	TextureManager::LoadTextureAndAssignKey("Buildings\\StackedBrick.tga", "StackedBrickTexture");
	TextureManager::LoadTextureAndAssignKey("Buildings\\SlabBrick.tga", "SlabBrickTexture");

	TextureManager::LoadTextureAndAssignKey("GrassDirt.tga", "GrassDirtTexture");
	TextureManager::LoadTextureAndAssignKey("Environment\\GrassSand.tga", "GrassSandTexture");
	TextureManager::LoadTextureAndAssignKey("Environment\\RedSand.tga", "RedSandTexture");
	TextureManager::LoadTextureAndAssignKey("Environment\\GrassSnow.tga", "GrassSnowTexture");
	TextureManager::LoadTextureAndAssignKey("Environment\\Grass.tga", "GrassTexture");
	TextureManager::LoadTextureAndAssignKey("Environment\\Stick.tga", "StickTexture");
	TextureManager::LoadTextureAndAssignKey("Environment\\Stone.tga", "StoneTexture");
	TextureManager::LoadTextureAndAssignKey("Environment\\Tree.tga", "TreeTexture");

	//---------------------------------------------------------------------------------------------------------
	// Load Images
	//---------------------------------------------------------------------------------------------------------

	ImageManager::LoadImageAndAssignKey("stitch.tga", "StitchImage");
	ImageManager::LoadImageAndAssignKey("stitch.tga", new Rect(0.0f, 0.0, 19.4f, 20.05f), "StichImage2");
	ImageManager::LoadImageAndAssignKey(254, 0, 0, "RedImage");
	ImageManager::LoadImageAndAssignKey(0, 0, 254, "BlueImage");
	ImageManager::LoadImageAndAssignKey(0, 0, 0, "BlackImage");
	ImageManager::LoadImageAndAssignKey("HealthImage.tga", "HealthImage");
	ImageManager::LoadImageAndAssignKey("BulletImage.tga", "BulletImage");
	ImageManager::LoadImageAndAssignKey("MainMenu.tga", "MainMenuImage");
	ImageManager::LoadImageAndAssignKey("MissionFailed.tga", "MissionFailedImage");

	ImageManager::LoadImageAndAssignKey("800x600Grid.tga", "GridImage");
	ImageManager::LoadImageAndAssignKey("ColoredCornerSquare.tga", "ColorCornerSquareImage");
	ImageManager::LoadImageAndAssignKey("TankReticle.tga", "TankReticleImage");
	//---------------------------------------------------------------------------------------------------------
	// Load SpriteFont
	//---------------------------------------------------------------------------------------------------------
	SpriteFontManager::LoadSpriteFontAndAssignKey("ArialRoundMTRed", "Font2");
	SpriteFontManager::LoadSpriteFontAndAssignKey("CourierNew", "Font1");
	SpriteFontManager::LoadSpriteFontAndAssignKey("CourierNewBlack", "ScreenLogFont");
	SpriteFontManager::LoadSpriteFontAndAssignKey("StencilOrange", "StencilOrangeFont");
	SpriteFontManager::LoadSpriteFontAndAssignKey("StencilWhite", "StencilWhiteFont");
	SpriteFontManager::LoadSpriteFontAndAssignKey("MilitaryGreen", "MilitaryGreenFont");

	//---------------------------------------------------------------------------------------------------------
	// Load Terrain
	//---------------------------------------------------------------------------------------------------------

	TerrainObjectManager::LoadAndAssignKey("Level1Terrain.tga", 600.0f, 0.75f, -0.375f, "GrassTexture", 100, 100, "Level1Terrain");
	TerrainObjectManager::LoadAndAssignKey("Level1Terrain.tga", 600.0f, 0.75f, -0.375f, "GrassDirtTexture", 100, 100, "Level2Terrain");
	TerrainObjectManager::LoadAndAssignKey("Level3Terrain.tga", 600.0f, 0.75f, -0.375f, "GrassSnowTexture", 100, 100, "Level3Terrain");
	TerrainObjectManager::LoadAndAssignKey("HMtest1.tga", 500.0f, 30.0f, -10.0f, "GridTexture", 1, 1, "TestTerrain");

	//---------------------------------------------------------------------------------------------------------
	// Set Starting Scene
	//---------------------------------------------------------------------------------------------------------

	SceneManager::SetStartScene(new MainMenu());
	//SceneManager::SetStartScene(new Level3());
	//SceneManager::SetStartScene(new BasicDemoScene());
	//SceneManager::SetStartScene(new TestScene4Sprites());
	//SceneManager::SetStartScene(new NullScene());
	//SceneManager::SetStartScene(new TestScene());
	//SceneManager::SetStartScene(new MissionFailed());

	Trace::out("\n");
}
