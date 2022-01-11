#ifndef _Marker
#define _Marker

#include "GameObject.h"

class Tank;
class DestinationMonitor;

class Marker : public GameObject
{
public:
	Marker();
	Marker(const Marker&) = default;
	Marker& operator=(const Marker&) = default;
	Marker(Marker&&) = default;
	Marker& operator=(Marker&&) = default;
	~Marker();

	void initialize(const Vect& position, float rotation = 0, float scale = 1.0f);
	void initialize(const Vect& position, const Matrix& rotation, float scale = 1.0f);
	void updateMarkerWorldMatrix();

	// Collision
	void collision(Tank*);
	
	// Setter/Getters
	void setDestinationMonitor(DestinationMonitor*);

	// ---> World Properties
	void setMarkerPosition(const Vect& position);
	Vect getMarkerPosition() const;

	void setMarkerScale(float scale);
	
	void setMarkerRotation(float rotation);
	void setMarkerRotation(const Matrix& rotation);
	
	void setColorGreen();
	void setColorRed();

private:
	virtual void draw() override;
	
	virtual void sceneEntry() override;
	virtual void sceneExit() override;

private:
	DestinationMonitor* _pDestinationMonitor;

	// internals
	GraphicsObject_TextureLight* _pMarkerGraphicsObject_Red;
	GraphicsObject_TextureLight* _pMarkerGraphicsObject_Green;
	GraphicsObject_TextureLight* _pMarkerGraphicsObject;

	Vect _localPosition;
	Matrix _localRotation;
	Matrix _localScale;

};
#endif // !_Marker

//-----------------------------------------------------------------------------------------------------------------------------
// Marker Comment Template
//-----------------------------------------------------------------------------------------------------------------------------