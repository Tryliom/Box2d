#include "weapon/weapons/Sniper.h"

#include "projectile/bullets/PenetrationBullet.h"
#include "Game.h"

Trail::Trail(const sf::Vector2f position, const float angle, const Group group)
{
	const sf::Texture& texture = Assets::GetInstance().GetTexture(Texture::SNIPER_TRAIL);

	_group = group;

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setPosition(position);
	_sprite.setRotation(angle);
	_sprite.setColor(GetColor(group));

	_lifeTime = sf::seconds(0.5f);
	_currentLifeTime = sf::Time::Zero;
}

void Trail::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Trail::Update(const sf::Time elapsed)
{
	_currentLifeTime += elapsed;

	sf::Uint8 alpha = 255 - static_cast<sf::Uint8>(_currentLifeTime.asSeconds() / _lifeTime.asSeconds() * 255);
	sf::Color color = _sprite.getColor();
	color.a = alpha;

	_sprite.setColor(color);
}

Sniper::Sniper(Stats::WeaponStats& userStats) :
	Weapon(Stats::WeaponStats{
		.Damage = 50.f,
		.Speed = 150.f,
		.Spread = 0.f,
		.Range = 1000.f,
		.BulletsPerShot = 1,
		.Cooldown = 1.f,
		.Size = 1.5f
	}, userStats)
{
	_trails = {};
}

void Sniper::shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity,
	const Group bulletGroup)
{
	const Stats::WeaponStats stats = getTotalStats();

	_bullets.push_back(new PenetrationBullet(
		body, position, angle,
		stats.GetSize(), velocity, getLifeTime(),
		stats.GetDamage(), bulletGroup
	));
}

void Sniper::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& trail : _trails)
	{
		target.draw(trail, states);
	}

	Weapon::draw(target, states);
}

void Sniper::Update(const sf::Time elapsed)
{
	Weapon::Update(elapsed);

	for (const auto* bullet : _bullets)
	{
		// Create a new trail for each bullet
		_trails.emplace_back(Trail(Game::MeterToPixel(bullet->GetBody()->GetPosition()), Game::RadToDegree(bullet->GetBody()->GetAngle()), bullet->GetGroup()));
	}

	for (auto& trail : _trails)
	{
		trail.Update(elapsed);
	}

	_trails.erase(std::remove_if(_trails.begin(), _trails.end(), [](const Trail& trail) { return trail.IsDead(); }),_trails.end());
}
