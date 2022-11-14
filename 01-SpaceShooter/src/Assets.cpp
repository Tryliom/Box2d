#include "Assets.h"

Assets::Assets()
{
	_textures[static_cast<int>(Texture::BACKGROUND)].loadFromFile("data/images/background.png");
	_textures[static_cast<int>(Texture::BACKGROUND2)].loadFromFile("data/images/background2.png");
	_textures[static_cast<int>(Texture::BACKGROUND3)].loadFromFile("data/images/background3.png");
	_textures[static_cast<int>(Texture::SPACE_SHIP)].loadFromFile("data/images/space_ship.png");
	_textures[static_cast<int>(Texture::TAIL)].loadFromFile("data/images/tail.png");
	_textures[static_cast<int>(Texture::SPARKS)].loadFromFile("data/images/sparks.png");
	_textures[static_cast<int>(Texture::CANON_BULLET)].loadFromFile("data/images/canon_bullet.png");
	_textures[static_cast<int>(Texture::MACHINE_GUN_BULLET)].loadFromFile("data/images/machine_gun_bullet.png");
	_textures[static_cast<int>(Texture::CHARGE_CIRCLE)].loadFromFile("data/images/charge_circle.png");
	_textures[static_cast<int>(Texture::SNIPER_TRAIL)].loadFromFile("data/images/trail.png");
	_textures[static_cast<int>(Texture::ENEMY_CAMPER)].loadFromFile("data/images/enemies/camper.png");
	_textures[static_cast<int>(Texture::ENEMY_IMPERATOR)].loadFromFile("data/images/enemies/imperator.png");
	_textures[static_cast<int>(Texture::ENEMY_ANGEL)].loadFromFile("data/images/enemies/angel.png");

	_fonts[static_cast<int>(Font::PIXELMIX)].loadFromFile("data/fonts/pixelmix.ttf");

	_sounds[static_cast<int>(Sound::BURST)].loadFromFile("data/sounds/burst.wav");
	_sounds[static_cast<int>(Sound::WEAPON_SHOOT)].loadFromFile("data/sounds/weapon_shoot.wav");
	_sounds[static_cast<int>(Sound::LEVEL_UP)].loadFromFile("data/sounds/level_up.wav");
	_sounds[static_cast<int>(Sound::UPGRADE_CHOOSE)].loadFromFile("data/sounds/upgrade_choose.wav");
	_sounds[static_cast<int>(Sound::BOSS_DEATH)].loadFromFile("data/sounds/boss_death.wav");
	_sounds[static_cast<int>(Sound::ENTITY_COLLISION)].loadFromFile("data/sounds/entity_collision.wav");
	_sounds[static_cast<int>(Sound::ENEMY_DEATH)].loadFromFile("data/sounds/enemy_death.wav");

	_musicPaths[static_cast<int>(Music::MAIN_THEME)] = "data/musics/main_theme1.wav";
	_musicPaths[static_cast<int>(Music::MAIN_THEME2)] = "data/musics/main_theme2.wav";
	_musicPaths[static_cast<int>(Music::DEATH)] = "data/musics/death.wav";
	_musicPaths[static_cast<int>(Music::BOSS_THEME)] = "data/musics/boss_theme.wav";

	for (int i = 0; i < _hitAnimationTextures.max_size(); i++)
	{
		_hitAnimationTextures[i].loadFromFile("data/images/hit_animation/0" + std::to_string(i) + ".png");
	}
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

std::string Assets::GetMusicPath(const Music music)
{
	return _musicPaths[static_cast<int>(music)];
}

sf::Texture& Assets::GetHitAnimationTexture(const int index)
{
	return _hitAnimationTextures[index];
}
