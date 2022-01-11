#ifndef _Sprite
#define _Sprite

#include <string>

class Camera;
class GraphicsObject_Sprite;
class SpriteModifierStrategy;
class Matrix;
struct Rect;

/**********************************************************************************************//**
 * <summary> A sprite used to display 2D images.</summary>
 *
 * <remarks> In the constructor, it uses a key assigned in the ImageManager. </remarks>
 **************************************************************************************************/
class Sprite
{
	friend class SpriteAttorney;

public:
	Sprite() = default;
	Sprite(const Sprite&) = default;
	Sprite& operator=(const Sprite&) = default;
	Sprite(Sprite&&) = default;
	Sprite& operator=(Sprite&&) = default;
	~Sprite();

	/**********************************************************************************************//**
	 * <summary> Constructs sprite using image key defined within Image Manager.</summary>
	 *	\ingroup SPRITE
	 * <remarks> The key is one that used to assign a particular image in ImageManager.</remarks>
	 *
	 * <param name="imageKey"> The image key.</param>
	 **************************************************************************************************/
	Sprite(const std::string& imageKey);

	/**********************************************************************************************//**
	 * <summary> Renders this sprite.</summary>
	 * \ingroup SPRITE
	 * <remarks> must be called within GameObject::draw2D() of the user derived GameObject entity.</remarks>
	 **************************************************************************************************/
	void render();

	// Setters/Getters

	/**********************************************************************************************//**
	 * <summary> Sets sprite position.</summary>
	 *	\ingroup SPRITE
	 * <remarks> The (0, 0) position is the lower left corner of the screen. </remarks>
	 *
	 * <param name="positionX"> The position x coordinate.</param>
	 * <param name="positionY"> The position y coordinate.</param>
	 **************************************************************************************************/
	void setPosition(float positionX, float positionY);

	/**********************************************************************************************//**
	 * <summary> Gets position x coordinate.</summary>
	 * \ingroup SPRITE
	 * <remarks> </remarks>
	 *
	 * <returns> The position x coordinate.</returns>
	 **************************************************************************************************/
	float getPositionX() const;

	/**********************************************************************************************//**
	 * <summary> Gets position y coordinate.</summary>
	 *
	 * <remarks> .</remarks>
	 *
	 * <returns> The position y coordinate.</returns>
	 **************************************************************************************************/
	float getPositionY() const;

	/**********************************************************************************************//**
	 * <summary> Sets sprite center.</summary>
	 * \ingroup SPRITE
	 * <remarks> the (0, 0) center is the actual center of the sprite image. </remarks>
	 *
	 * <param name="centerX"> The center x coordinate.</param>
	 * <param name="centerY"> The center y coordinate.</param>
	 **************************************************************************************************/
	void setCenter(float centerX, float centerY);

	/**********************************************************************************************//**
	 * <summary> Sets sprite angle./</summary>
	 * \ingroup SPRITE
	 * <remarks> angle is in radians. </remarks>
	 *
	 * <param name="angle"> The angle.</param>
	 **************************************************************************************************/
	void setAngle(float angle);

	/**********************************************************************************************//**
	 * <summary> Gets the sprite angle.</summary>
	 * \ingroup SPRITE
	 * <remarks> angle is in radians. </remarks>
	 *
	 * <returns> The angle.</returns>
	 **************************************************************************************************/
	float getAngle() const;

	/**********************************************************************************************//**
	 * <summary> Offset sprite angle.</summary>
	 * \ingroup SPRITE
	 * <remarks> angle offset is in radians. </remarks>
	 *
	 * <param name="angleOffset"> The angle offset.</param>
	 **************************************************************************************************/
	void offsetAngle(float angleOffset);

	/**********************************************************************************************//**
	 * <summary> Sets scale factor.</summary>
	 * \ingroup SPRITE
	 * <remarks> </remarks>
	 *
	 * <param name="scaleX"> The X scale factor.</param>
	 * <param name="scaleY"> The Y scale factor.</param>
	 **************************************************************************************************/
	void setScaleFactor(float scaleX, float scaleY);

	/**********************************************************************************************//**
	 * <summary> Sets scale pixel.</summary>
	 * \ingroup SPRITE
	 * <remarks> </remarks>
	 *
	 * <param name="width">  The width.</param>
	 * <param name="height"> The height.</param>
	 **************************************************************************************************/
	void setScalePixel(float width, float height);

	/**********************************************************************************************//**
	 * <summary> Gets the width of the sprite.</summary>
	 * \ingroup SPRITE
	 * <remarks> </remarks>
	 *
	 * <returns> The width.</returns>
	 **************************************************************************************************/
	float getWidth() const;

	/**********************************************************************************************//**
	 * <summary> Gets the height of the sprite.</summary>
	 * \ingroup SPRITE
	 * <remarks> </remarks>
	 *
	 * <returns> The height.</returns>
	 **************************************************************************************************/
	float getHeight() const;

private:
	// ---> Setter/Getter helpers
	void setToUpdateWorld();
	void setToNullModifier();
	
	void updateWorld();
	
	Matrix getCenterMatrix() const;
	Matrix getPositionMatrix() const;
	Matrix getRotationMatrix() const;
	Matrix getScaleMatrix() const;
	Matrix getScalePixelMatrix() const;

private:
	// Properties
	float _positionX;
	float _positionY;
	float _centerX;
	float _centerY;

	float _angle;

	float _scaleX;
	float _scaleY;
	float _width;
	float _height;
	
	GraphicsObject_Sprite* _pSpriteGraphicsObject;

	SpriteModifierStrategy* _pPropertyModifierStrategy;
};
#endif // !_Sprite

//-----------------------------------------------------------------------------------------------------------------------------
// Sprite Comment Template
//-----------------------------------------------------------------------------------------------------------------------------