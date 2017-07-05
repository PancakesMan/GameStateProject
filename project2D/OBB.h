#pragma once
#include "Vector2.h"
#include "SpriteObject.h"

class OBB
{
public:
	// Create OBB from Sprite Object
	OBB(SpriteObject* obj);

	// Create OBB without rotation from position and size
	OBB(Vector2<float> pos, Vector2<float> size);
	~OBB();

	// Check if OBB contains a point
	bool contains(Vector2<float>& point);

	// Check if OBB contains another OBB
	bool contains(OBB box);

	// Check if OBB collides with another OBB
	bool collides(OBB& rhs);
	
	void draw(aie::Renderer2D* renderer);
private:
	Vector2<float> position;
	Vector2<float> size;
	Vector2<float> x;
	Vector2<float> y;

	union verts
	{
		verts() {}
		struct { Vector2<float> corners[4]; };
		struct { Vector2<float> topLeft, topRight, bottomRight, bottomLeft; };
	}v;

	DynamicArray<Vector2<float>> getFaceNormals();
	Vector2<float> mid(Vector2<float>& p1, Vector2<float>& p2);
	float getArea();
};