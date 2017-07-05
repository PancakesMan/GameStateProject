#include "Tank.h"
#include <iostream>

Tank::Tank(TankColor c, float x, float y) : SceneObject()
{
	if (c == TankColor::Red)
	{
		// Create a Red Tank
		bodyTexture = new aie::Texture("./textures/tankRed.png");
		barrelTexture = new aie::Texture("./textures/barrelRed.png");
	}
	else if (c == TankColor::Green)
	{
		// Create a Green Tank
		bodyTexture = new aie::Texture("./textures/tankGreen.png");
		barrelTexture = new aie::Texture("./textures/barrelGreen.png");
	}
	else if (c == TankColor::Blue)
	{
		// Create a Blue Tank
		bodyTexture = new aie::Texture("./textures/tankBlue.png");
		barrelTexture = new aie::Texture("./textures/barrelBlue.png");
	}
	else if (c == TankColor::Beige)
	{
		// Create a Beige Tank
		bodyTexture = new aie::Texture("./textures/tankBeige.png");
		barrelTexture = new aie::Texture("./textures/barrelBeige.png");
	}

	// Create the body sprite object and
	// set it's position
	body = new SpriteObject(bodyTexture);
	body->setLocalTransform(Matrix3<float>(1, 0, 0, 0, 1, 0, x, y, 1));

	// Create Barrel rotate point and
	// Bullet Collection sub heirarchy
	barrelPoint = new SceneObject();
	bulletCollection = new SceneObject();

	// Create barrel sprite object and
	// set it's position relative to the rank body
	barrel = new SpriteObject(barrelTexture);
	barrel->setLocalTransform(Matrix3<float>(1, 0, 0, 0, 1, 0, 0, 25, 1));

	// Add objects as children to
	// appropriate parents
	addChild(body);
	addChild(bulletCollection);
	body->addChild(barrelPoint);
	barrelPoint->addChild(barrel);

	updateGlobalTransform();

	moveSpeed = 0;
}

Matrix3<float> Tank::getLocalTransform()
{
	return body->getLocalTransform();
}

void Tank::setLocalTransform(Matrix3<float> m)
{
	body->setLocalTransform(m);
}

void Tank::rotate(float angle)
{
	body->rotate(angle);
}

void Tank::rotateBarrel(float angle)
{
	barrelPoint->rotate(angle);

	if (acos(barrelPoint->getLocalTransform()[0][0]) > 2.2f)
	{
		Matrix3<float> oldTransform, newTransform;
		newTransform.setRotateZ(2.199f * (angle < 0 ? -1 : 1));
		oldTransform = barrelPoint->getLocalTransform();

		newTransform[2][0] = oldTransform[2][0];
		newTransform[2][1] = oldTransform[2][1];
		
		barrelPoint->setLocalTransform(newTransform);
	}
}

void Tank::moveForward()
{
	if (moveSpeed < 150) moveSpeed += 1;
}

void Tank::moveBackwards()
{
	if (moveSpeed > -150) moveSpeed -= 1;
}

void Tank::moveAlongY(float distance)
{
	setLocalTransform(getLocalTransform() * Matrix3<float>(1, 0, 0, 0, 1, 0, 0, distance, 1));
}

void Tank::moveAlongX(float distance)
{
	setLocalTransform(getLocalTransform() * Matrix3<float>(1, 0, 0, 0, 1, 0, distance, 0, 1));
}

void Tank::fire()
{
	Bullet* b = new Bullet(barrelPoint);
	b->addToBaseSpeed(moveSpeed);
	bulletCollection->addChild(b);
}

void Tank::update(float deltaTime)
{
	SceneObject::update(deltaTime);

	if (moveSpeed > 0) moveSpeed -= 0.5f;
	if (moveSpeed < 0) moveSpeed += 0.5f;

	moveAlongY(deltaTime * moveSpeed);
	// If the tank body or the barrel gets destroyed
	// then the tank is destroyed
	if (barrel->isDestroyed() || body->isDestroyed())
	{
		barrel->destroy();
		barrelPoint->destroy();
		body->destroy();
		destroy();
	}
}

void Tank::draw(aie::Renderer2D* renderer)
{
	//Vector3<float> direction = barrelPoint->getGlobalTransform()[1].normalised();

	//Vector3<float> endPoint = direction * 2000.0f + barrelPoint->getGlobalTransform()[2];
	//renderer->setRenderColour(1, 1, 1, 0.5);
	//renderer->drawLine(barrelPoint->getGlobalTransform()[2][0], barrelPoint->getGlobalTransform()[2][1], endPoint[0], endPoint[1], 1.0f, 11.0f);
	//renderer->setRenderColour(1, 1, 1, 1);
	SceneObject::draw(renderer);
}