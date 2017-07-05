#include "Rock.h"

// Initialize static array of rock textures
std::string Rock::rockTextures[] = { "./textures/rock_small.png", "./textures/rock_medium.png", "./textures/rock_large.png" };

Rock::Rock(RockSize s, float x, float y) : SpriteObject(new aie::Texture(Rock::rockTextures[s].c_str()))
{
	// Set position of object
	setLocalTransform(Matrix3<float>(1, 0, 0, 0, 1, 0, x, y, 1));
}

void Rock::destroy()
{
	if (m_texture->getFilename() == Rock::rockTextures[RockSize::Large])
	{
		m_texture->load(Rock::rockTextures[RockSize::Medium].c_str());
	}
	else if (m_texture->getFilename() == Rock::rockTextures[RockSize::Medium])
	{
		m_texture->load(Rock::rockTextures[RockSize::Small].c_str());
	}
	else if (m_texture->getFilename() == Rock::rockTextures[RockSize::Small])
	{
		SceneObject::destroy();
	}
}