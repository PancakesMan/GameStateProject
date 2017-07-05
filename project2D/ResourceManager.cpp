#pragma once
#include "ResourceManager.h"
#include <Font.h>
#include <Texture.h>
#include <Audio.h>

ResourceManager resources;

std::shared_ptr<aie::Texture> ResourceManager::getTexture(const std::string& filename)
{
	if (m_textures.find({ filename, 0 }) == -1)
		m_textures[{filename, 0}] = std::shared_ptr<aie::Texture>(new aie::Texture(filename.c_str()));
	return m_textures[{filename, 0}];
}

std::shared_ptr<aie::Audio> ResourceManager::getAudio(const std::string& filename)
{
	if (m_sounds.find({ filename, 0 }) == -1)
		m_sounds[{filename, 0}] = std::shared_ptr<aie::Audio>(new aie::Audio(filename.c_str()));
	return m_sounds[{filename, 0}];
}

std::shared_ptr<aie::Font> ResourceManager::getFont(const std::string& filename, const unsigned short fontHeight)
{
	if (m_fonts.find({ filename, fontHeight }) == -1)
		m_fonts[{filename, fontHeight}] = std::shared_ptr<aie::Font>(new aie::Font(filename.c_str(), fontHeight));
	return m_fonts[{filename, fontHeight}];
}

int ResourceManager::getCount()
{
	return m_textures.size() + m_sounds.size() + m_fonts.size();
}

void ResourceManager::collectGarbage()
{
	// Remove the unused textures
	for (auto it = m_textures.begin(); it != m_textures.end();)
	{
		if ( it->value.use_count() == 1)
			m_textures.remove(it->key);
		else
			++it;
	}

	// Remove the unused sounds
	for (auto it = m_sounds.begin(); it != m_sounds.end();)
	{
		if (it->value.use_count() == 1)
			m_sounds.remove(it->key);
		else
			++it;
	}

	// Remove the unused fonts
	for (auto it = m_fonts.begin(); it != m_fonts.end();)
	{
		if (it->value.use_count() == 1)
			m_fonts.remove(it->key);
		else
			++it;
	}
}