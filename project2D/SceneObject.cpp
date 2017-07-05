#include "SceneObject.h"

SceneObject::SceneObject() : m_parent(nullptr)
{
	destroyed = false;
}

SceneObject::~SceneObject()
{
	for (auto child : m_children)
		delete child;
}

void SceneObject::addChild(SceneObject* child)
{
	if (child->m_parent == nullptr)
	{
		child->m_parent = this;
		m_children.AddToEnd(child);
	}
}

Matrix3<float> SceneObject::getLocalTransform() {
	return m_localTransform;
}

void SceneObject::setLocalTransform(Matrix3<float> mat) {
	m_localTransform = mat;
	updateGlobalTransform();
}

Matrix3<float> SceneObject::getGlobalTransform() {
	return m_globalTransform;
}

void SceneObject::rotate(float angle)
{
	Matrix3<float> m;
	m.setRotateZ(angle);

	m_localTransform *= m;
	updateGlobalTransform();
}

void SceneObject::updateGlobalTransform() {
	if (m_parent != nullptr)
		m_globalTransform = m_parent->m_globalTransform * m_localTransform;
	else
		m_globalTransform = m_localTransform;
	for (auto child : m_children)
		child->updateGlobalTransform();
};

void SceneObject::update(float deltaTime)
{
	for (auto child : m_children)
		child->update(deltaTime);

	// Remove children if they have been destroyed
	//m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [](SceneObject* so) { return so->isDestroyed(); }), m_children.end());
	for (int i = 0; i < m_children.Size();) {
		if (m_children[i]->isDestroyed())
			m_children.Remove(i);
		else
			i++;
	}

}

void SceneObject::draw(aie::Renderer2D* renderer)
{
	for (auto child : m_children)
		child->draw(renderer);
}

DynamicArray<SceneObject*> SceneObject::getChildrenRecursively()
{
	DynamicArray<SceneObject*> result;
	//result.insert(result.end(), m_children.begin(), m_children.end());
	for (int i = 0; i < m_children.Size(); i++)
		result.AddToEnd(m_children[i]);
	for (auto obj : m_children)
	{
		DynamicArray<SceneObject*> children = obj->getChildrenRecursively();
		//result.insert(result.end(), children.begin(), children.end());
		for (int i = 0; i < children.Size(); i++)
			result.AddToEnd(children[i]);
	}

	return result;
}

void SceneObject::destroy()
{
	destroyed = true;
}

bool SceneObject::isDestroyed()
{
	return destroyed;
}