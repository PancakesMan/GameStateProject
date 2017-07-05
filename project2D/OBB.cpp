#include "OBB.h"

OBB::OBB(SpriteObject* obj)
{
	// Set centre of OBB in global space
	position = Vector2<float>(obj->getGlobalTransform()[2][0], obj->getGlobalTransform()[2][1]);

	// Set X axis of obj (Xx, Yx) for rotation
	x = Vector2<float>(obj->getGlobalTransform()[0][0], obj->getGlobalTransform()[1][0]);

	// Set Y axis of obj (Xy, Yy) for rotation
	y = Vector2<float>(obj->getGlobalTransform()[0][1], obj->getGlobalTransform()[1][1]);

	// Set size of OBB
	size = Vector2<float>(obj->getWidth(), obj->getHeight());

	// Left X and right X relative to center
	float lowerX = -0.5f * size[0], upperX = 0.5f * size[0];

	// Up Y and Down Y relative to centre
	float lowerY = -0.5f * size[1], upperY = 0.5f * size[1];

	// Set corner points of the hitbox
	v.topLeft = Vector2<float>(lowerX * x[0] + upperY * x[1] + position[0], lowerX * y[0] + upperY * y[1] + position[1]);
	v.topRight = Vector2<float>(upperX * x[0] + upperY * x[1] + position[0], upperX * y[0] + upperY * y[1] + position[1]);
	v.bottomRight = Vector2<float>(upperX * x[0] + lowerY * x[1] + position[0], upperX * y[0] + lowerY * y[1] + position[1]);
	v.bottomLeft = Vector2<float>(lowerX * x[0] + lowerY * x[1] + position[0], lowerX * y[0] + lowerY * y[1] + position[1]);
}

OBB::OBB(Vector2<float> pos, Vector2<float> a_size)
{
	// Set position and size of unrotated hitbox
	position = pos;
	size = a_size;

	// Set corner points of unrotated hitbox
	v.topLeft = Vector2<float>(pos[0] - size[0] / 2, pos[1] + size[1] / 2);
	v.topRight = Vector2<float>(pos[0] + size[0] / 2, pos[1] + size[1] / 2);
	v.bottomRight = Vector2<float>(pos[0] + size[0] / 2, pos[1] - size[1] / 2);
	v.bottomLeft = Vector2<float>(pos[0] - size[0] / 2, pos[1] - size[1] / 2);
}

OBB::~OBB()
{
}

bool OBB::contains(Vector2<float>& point)
{
	// Collision check with point
	if (point[0] < position[0] - size[0] / 2 || point[0] > position[0] + size[0] / 2) return false;
	if (point[1] < position[1] - size[1] / 2 || point[1] > position[1] + size[1] / 2) return false;
	return true;
}

bool OBB::contains(OBB box)
{
	if (box.getArea() < getArea())
	{
		// tun = this objects unrotated normals
		// bun = box objects unrotated normals
		//std::vector<Vector2<float>> tun = OBB(position, size).getFaceNormals();
		//std::vector<Vector2<float>> bun = OBB(box.position, box.size).getFaceNormals();
		
		//return tun[0][1] > bun[0][1]
			//&& tun[1][0] > bun[1][0]
			//&& tun[2][1] < bun[2][1]
			//&& tun[3][0] < bun[3][0];

		return contains(box.v.topLeft) && contains(box.v.topRight)
			&& contains(box.v.bottomLeft) && contains(box.v.bottomRight);
	}

	return false;
}

bool OBB::collides(OBB& rhs)
{
	// Add the face normals and the corners to an array
	DynamicArray<Vector2<float>> faceNormals = getFaceNormals();
	faceNormals.AddToEnd(v.topLeft);
	faceNormals.AddToEnd(v.topRight);
	faceNormals.AddToEnd(v.bottomRight);
	faceNormals.AddToEnd(v.bottomLeft);

	// Check if any of the points is inside the rhs object
	for (int i = 0; i < faceNormals.Size(); i++) {
		if (rhs.contains(Vector2<float>(faceNormals[i][0], faceNormals[i][1])))
			return true;
	}

	return false;
}

void OBB::draw(aie::Renderer2D* renderer)
{
	renderer->drawLine(v.bottomLeft[0], v.bottomLeft[1], v.topLeft[0], v.topLeft[1], 2.f);
	renderer->drawLine(v.topLeft[0], v.topLeft[1], v.topRight[0], v.topRight[1], 2.f);
	renderer->drawLine(v.topRight[0], v.topRight[1], v.bottomRight[0], v.bottomRight[1], 2.f);
	renderer->drawLine(v.bottomRight[0], v.bottomRight[1], v.bottomLeft[0], v.bottomLeft[1], 2.f);
}

DynamicArray<Vector2<float>> OBB::getFaceNormals()
{
	DynamicArray<Vector2<float>> normals;

	// Center of north face
	normals.AddToEnd(mid(v.topLeft, v.topRight));

	// Center of east face
	normals.AddToEnd(mid(v.topRight, v.bottomRight));

	// Center of south face
	normals.AddToEnd(mid(v.bottomRight, v.bottomLeft));

	// Center of west face
	normals.AddToEnd(mid(v.bottomLeft, v.topLeft));

	return normals;
}

Vector2<float> OBB::mid(Vector2<float>& p1, Vector2<float>& p2)
{
	// Return midpoint between 2 points
	return Vector2<float>((p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2);
}

float OBB::getArea()
{
	// Return area of hitbox
	return size[0] * size[1];
}