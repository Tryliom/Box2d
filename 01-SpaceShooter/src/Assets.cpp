#include "Assets.h"

Assets::Assets()
{
	_textures[static_cast<int>(Texture::BACKGROUND)].loadFromFile("data/images/background.png");
	_textures[static_cast<int>(Texture::SPACE_SHIP)].loadFromFile("data/images/space_ship.png");
	_textures[static_cast<int>(Texture::TRAIL)].loadFromFile("data/images/trail.png");
	_textures[static_cast<int>(Texture::SPARKS)].loadFromFile("data/images/sparks.png");

	_fonts[static_cast<int>(Font::PIXELMIX)].loadFromFile("data/fonts/pixelmix.ttf");

	_sounds[static_cast<int>(Sound::BURST)].loadFromFile("data/sounds/burst.wav");
}

sf::Texture& Assets::GetTexture(const Texture texture)
{
	return _textures[static_cast<int>(texture)];
}

sf::Font& Assets::GetFont(const Font font)
{
	return _fonts[static_cast<int>(font)];
}

sf::SoundBuffer& Assets::GetSound(const Sound sound)
{
	return _sounds[static_cast<int>(sound)];
}

sf::Music& Assets::GetMusic(const Music music)
{
	return _musics[static_cast<int>(music)];
}