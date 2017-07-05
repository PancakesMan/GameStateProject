#pragma once
#include <memory>
#include "Map.h"

template <class R>
using SharedPtrArray = Map<std::pair<std::string, unsigned short>,std::shared_ptr<R>>;

namespace aie {
	class Texture;
	class Audio;
	class Font;
}

class ResourceManager
{
public:
	ResourceManager() {};
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;
	~ResourceManager() {};

	std::shared_ptr<aie::Texture> getTexture(const std::string& filename);
	std::shared_ptr<aie::Audio> getAudio(const std::string& filename);
	std::shared_ptr<aie::Font> getFont(const std::string& filename, const unsigned short fontHeight);

	int getCount();
	void collectGarbage();

private:
	SharedPtrArray<aie::Texture>  m_textures;
	SharedPtrArray<aie::Audio>    m_sounds;
	SharedPtrArray<aie::Font>     m_fonts;
};

extern ResourceManager resources;