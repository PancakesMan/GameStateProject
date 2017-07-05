#pragma once
#include <algorithm>
#include "SpriteObject.h"
#include "Bullet.h"

enum TankColor { Red, Green, Blue, Beige };

class Tank : public SceneObject
{
public:
	Tank(TankColor c, float x, float y);

	Matrix3<float> getLocalTransform();
	void setLocalTransform(Matrix3<float> m);
	void rotate(float angle);
	void rotateBarrel(float angle);
	void moveForward();
	void moveBackwards();
	void fire();
	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);

private:
	aie::Texture* bodyTexture;
	aie::Texture* barrelTexture;

	SpriteObject* body;
	SceneObject*  barrelPoint;
	SceneObject*  bulletCollection;
	SpriteObject* barrel;

	float moveSpeed;

	void moveAlongY(float distance);
	void moveAlongX(float distance);
};