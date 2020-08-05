#pragma once
#include "resource_holder.hpp"
namespace sf {
    class Texture;
    class Font;
}


namespace Textures {
    enum class ID {
        Fire,
        Leaf,
        Water,
        Grass,
        FireTower,
        WaterTower,
        LeafTower,
        Path,
        TitleScreen,
    };
}

namespace Fonts {
	enum ID {
		Main,
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;