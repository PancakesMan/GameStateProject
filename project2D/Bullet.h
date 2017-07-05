#pragma once
#include "SpriteObject.h"

class Bullet : public SpriteObject
{
public:
	Bullet(SceneObject* barrelPoint) : SpriteObject(new aie::Texture("./textures/bullet2.png"))
	{
		// Set position of object
		setLocalTransform(barrelPoint->getGlobalTransform() * Matrix3<float>(1, 0, 0, 0, 1, 0, 0, 50, 1));

		// Set base speed
		baseMoveSpeed = 300.0f;

		// Set extra move speed
		extraMoveSpeed = 0.0f;
	}

	void addToBaseSpeed(float extraSpeed)
	{
		extraMoveSpeed = extraSpeed;
	}

	void update(float deltaTime)
	{
		// Make the bullet move 200 units per second
		m_localTransform *= Matrix3<float>(1, 0, 0, 0, 1, 0, 0, (baseMoveSpeed + extraMoveSpeed) * deltaTime, 1);
		updateGlobalTransform();
		SpriteObject::update(deltaTime);
	}

private:
	float baseMoveSpeed, extraMoveSpeed;
};
