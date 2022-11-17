#pragma once
#include <array>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

constexpr float ANIMATION_DURATION = 1.f / 24.f;

enum class Texture
{
	BACKGROUND, BACKGROUND2, BACKGROUND3, SPACE_SHIP, TAIL, SPARKS, CANON_BULLET, MACHINE_GUN_BULLET, CHARGE_CIRCLE, SNIPER_TRAIL, ENEMY_CAMPER, ENEMY_IMPERATOR, ENEMY_ANGEL,
	XP_SHARD, SHOT_GUN_BULLET, END
};

enum class Font
{
	PIXELMIX, END
};

enum class Sound
{
	BURST, WEAPON_SHOOT, LEVEL_UP, UPGRADE_CHOOSE, ENTITY_COLLISION, ENEMY_DEATH, END
};

enum class Music
{
	MAIN_THEME, MAIN_THEME2, DEATH, BOSS_THEME, END
};

class Assets
{
private:
	Assets();

	std::array<sf::Texture, static_cast<int>(Texture::END)> _textures;
	std::array<sf::Font, static_cast<int>(Font::END)> _fonts;
	std::array<sf::SoundBuffer, static_cast<int>(Sound::END)> _sounds;
	std::array<std::string, static_cast<int>(Music::END)> _musicPaths;
	std::array<sf::Texture, 10> _hitAnimationTextures;
	std::array<sf::Texture, 12> _deathAnimationTextures;

public:
	Assets(const Assets&) = delete;
	Assets& operator=(const Assets&) = delete;
	Assets(Assets&&) = delete;
	Assets& operator=(Assets&&) = delete;

	sf::Texture& GetTexture(Texture texture);
	sf::Font& GetFont(Font font);
	sf::SoundBuffer& GetSound(Sound sound);
	std::string GetMusicPath(Music music);
	sf::Texture& GetHitAnimationTexture(int index);
	sf::Texture& GetDeathAnimationTexture(int index);

	int GetHitAnimationTextureCount() const;
	int GetDeathAnimationTextureCount() const;

	static auto& GetInstance() {
		static Assets instance;
		return instance;
	}
};