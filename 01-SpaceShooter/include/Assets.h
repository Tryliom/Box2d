#pragma once
#include <array>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum class Texture
{
	BACKGROUND, BACKGROUND2, BACKGROUND3, SPACE_SHIP, TAIL, SPARKS, CANON_BULLET, CHARGE_CIRCLE, SNIPER_TRAIL, ENEMY_CAMPER, ENEMY_IMPERATOR, END
};

enum class Font
{
	PIXELMIX, END
};

enum class Sound
{
	BURST, END
};

enum class Music
{
	MAIN_THEME, END
};

class Assets
{
private:
	Assets();

	std::array<sf::Texture, static_cast<int>(Texture::END)> _textures;
	std::array<sf::Font, static_cast<int>(Font::END)> _fonts;
	std::array<sf::SoundBuffer, static_cast<int>(Sound::END)> _sounds;
	std::array<sf::Music, static_cast<int>(Music::END)> _musics;

public:
	Assets(const Assets&) = delete;
	Assets& operator=(const Assets&) = delete;
	Assets(Assets&&) = delete;
	Assets& operator=(Assets&&) = delete;

	sf::Texture& GetTexture(Texture texture);
	sf::Font& GetFont(Font font);
	sf::SoundBuffer& GetSound(Sound sound);
	sf::Music& GetMusic(Music music);

	static auto& GetInstance() {
		static Assets instance;
		return instance;
	}
};