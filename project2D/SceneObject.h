#pragma once
#include "Matrix3.h"
#include "Renderer2D.h"
#include <vector>
#include "DynamicArray.h"
#include <algorithm>

class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject();

	void addChild(SceneObject* child);
	virtual Matrix3<float> getLocalTransform();
	virtual void setLocalTransform(Matrix3<float> mat);
	virtual Matrix3<float> getGlobalTransform();
	virtual void rotate(float angle);
	void updateGlobalTransform();
	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);
	DynamicArray<SceneObject*> getChildrenRecursively();
	virtual void destroy();
	bool isDestroyed();

protected:
	Matrix3<float> m_globalTransform;
	Matrix3<float> m_localTransform;

	SceneObject* m_parent;
	DynamicArray<SceneObject*> m_children;

	bool destroyed;
};