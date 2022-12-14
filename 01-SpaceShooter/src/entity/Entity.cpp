#include "entity/Entity.h"

#include <iostream>

#include "Game.h"
#include "animation/TextAnimation.h"
#include "entity/Player.h"
#include "manager/AnimationManager.h"
#include "manager/AudioManager.h"

Entity::Entity(Game& game, const sf::Vector2f position, const sf::Texture& texture,
               const float maxHealth, 
               const Stats::EntityStats stats, const Group groupIndex) :
	DrawableObject(game.GetNewBody(), position),
	_game(game)
{
	_health = maxHealth;
	_maxHealth = maxHealth;
	_lastHealth = maxHealth;

	_stats = stats;
	_bonusStats = {};
	_weaponStats = {};

	_groupIndex = groupIndex;
	_weapon = nullptr;
	_modules = {};

	const float scale = 1.f + GetTotalStats().Size;
	_shape.setTexture(&texture);
	_shape.setSize(sf::Vector2f(texture.getSize()));
	_shape.setOrigin(_shape.getSize() / 2.f);
	_shape.setPosition(position);
	_shape.setScale(scale, scale);
	
	_shape.setFillColor(GetColor(_groupIndex));

	b2CircleShape circle;
	circle.m_radius = Game::PixelToMeter(_shape.getSize().x * _shape.getScale().x / 3.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.f;
	fixtureDef.restitution = 1.f;
	fixtureDef.friction = 0.5f;
	fixtureDef.filter.groupIndex = static_cast<int16>(_groupIndex);
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	_body->CreateFixture(&fixtureDef);

	_body->SetLinearDamping(0.8f);
	_body->SetTransform(Game::PixelToMeter(position), Game::DegreeToRad(_shape.getRotation()));
	_body->SetType(b2_dynamicBody);
}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	if (_weapon != nullptr)
	{
		target.draw(*_weapon, states);
	}
	
	target.draw(_shape, states);
}

float Entity::getDeltaAngle(const float angle) const
{
	const float currentAngle = Game::RadToDegree(_body->GetAngle());
	float difference = angle - currentAngle;

	while (difference < -180.f)
	{
		difference += 360.f;
	}

	while (difference > 180.f)
	{
		difference -= 360.f;
	}

	return difference + 90.f;
}

void Entity::rotate(float angle) const
{
	const float rotationSpeed = GetTotalStats().GetRotationSpeed();
	angle = getDeltaAngle(angle);

	if (angle > rotationSpeed)
	{
		angle = rotationSpeed;
	}
	else if (angle < -rotationSpeed)
	{
		angle = -rotationSpeed;
	}

	_body->SetAngularVelocity(Game::DegreeToRad(angle * 10.f));
}

void Entity::updateHealthDifference()
{
	const float healthDifference = _lastHealth - _health;

	if (static_cast<int>(healthDifference) != 0)
	{
		if (healthDifference > 0.f)
		{
			AnimationManager& animationManager = AnimationManager::GetInstance();
			animationManager.AddTextAnimation(DamageTextAnimation(
				_shape.getPosition(),
				std::to_string(static_cast<int>(healthDifference)),
				_groupIndex == Group::PLAYER ? sf::Color::Red : sf::Color::White
			));
		}
		else if (healthDifference < 0.f)
		{
			AnimationManager& animationManager = AnimationManager::GetInstance();
			animationManager.AddTextAnimation(DamageTextAnimation(
				_shape.getPosition(),
				std::to_string(static_cast<int>(healthDifference * -1.f)),
				sf::Color::Green
			));
		}
	}

	_healthDifferenceTime = sf::Time::Zero;
	_lastHealth = _health;
}

void Entity::Update(const sf::Time elapsed)
{
	_healthDifferenceTime += elapsed;

	if (_healthDifferenceTime >= sf::seconds(.5f))
	{
		updateHealthDifference();
	}

	if (_health < _maxHealth && !IsDead())
	{
		_health += GetTotalStats().GetHealthRegeneration() * elapsed.asSeconds();
	}

	if (_health > _maxHealth)
	{
		_health = _maxHealth;
	}

	// Update the position of the shape
	_shape.setPosition(Game::MeterToPixel(_body->GetPosition()));

	// Update the rotation of the shape
	_shape.setRotation(Game::RadToDegree(_body->GetAngle()));

	if (_weapon != nullptr)
	{
		_weapon->UpdatePosition(this);
		_weapon->Update(elapsed);
	}

	if (_weapon != nullptr && _weapon->CanShoot())
	{
		if (_groupIndex == Group::PLAYER)
		{
			const auto player = dynamic_cast<Player*>(this);

			if (player->IsCopilot() || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				_weapon->Shoot(this, GetProjectileGroup());

				ChargeWeapon();
			}
		}
		else
		{
			_weapon->Shoot(this, GetProjectileGroup());
		}
	}

	for (auto* module : _modules)
	{
		module->Update(elapsed, this);
	}
}

void Entity::Move(const sf::Time elapsed)
{
	// Add a linear velocity to the body to make it move to the angle it is facing
	if (_body->GetLinearVelocity().Length() < GetTotalStats().GetMaxSpeed())
	{
		float speed = GetTotalStats().GetSpeed() * elapsed.asSeconds();

		if (_body->GetLinearVelocity().Length() < GetTotalStats().GetSpeed() * 2.f)
		{
			speed *= 2.f;
		}


		_body->SetLinearVelocity(
			_body->GetLinearVelocity() + 
			Game::GetLinearVelocity(speed, Game::RadToDegree(_body->GetAngle()))
		);
	}

	for (auto* module : _modules)
	{
		module->OnEntityMove(this);
	}
}

sf::Vector2f Entity::GetPosition() const
{
	return Game::MeterToPixel(_body->GetPosition());
}

void Entity::SetPosition(const sf::Vector2f position)
{
	_body->SetTransform(Game::PixelToMeter(position), _body->GetAngle()); _shape.setPosition(position);
}

bool Entity::IsDead() const
{
	return _health <= 0.f;
}

Group Entity::GetProjectileGroup() const
{
	return _groupIndex == Group::PLAYER ? Group::PLAYER_PROJECTILE : Group::ENEMY_PROJECTILE;
}

void Entity::TakeDamage(Projectile* projectile)
{
	if (!_invincible)
	{
		_health -= projectile->GetDamage();
	}

	for (auto* module : _modules)
	{
		module->OnEntityHit(this, projectile);
	}

	if (IsDead())
	{
		onDeath();
	}
}

void Entity::TakeDamage(Entity* entity)
{
	if (!_invincible)
	{
		const float collisionDamage = GetTotalStats().GetCollisionDamage(entity->GetTotalStats().GetCollisionDamage());
		_health -= collisionDamage;
	}

	AudioManager::GetInstance().PlaySound(Sound::ENTITY_COLLISION);

	for (auto* module : _modules)
	{
		module->OnEntityHit(this, entity);
	}

	if (IsDead())
	{
		onDeath();
	}
}

void Entity::ChargeWeapon()
{
	if (_weapon != nullptr)
	{
		_weapon->StartCharging(this);
	}
}

void Entity::StopChargingWeapon() const
{
	if (_weapon != nullptr)
	{
		_weapon->StopCharging();
	}
}

sf::Vector2f Entity::GetWeaponPosition() const
{
	const sf::Vector2f size = _shape.getSize();
	const sf::Vector2f scale = _shape.getScale();
	const sf::Vector2f position = _shape.getPosition();
	const float angle = _shape.getRotation() + 90.f;

	const float x = position.x - (size.x * scale.x / 2.f) * std::cos(Game::DegreeToRad(angle));
	const float y = position.y - (size.y * scale.y / 2.f) * std::sin(Game::DegreeToRad(angle));

	return { x, y };
}

void Entity::AddBonusStats(const Stats::EntityStats bonusStats)
{
	_bonusStats += bonusStats;

	updateSize();
}

void Entity::AddBonusStats(const Stats::WeaponStats bonusStats)
{
	_weaponStats += bonusStats;
}

Stats::EntityStats Entity::GetTotalStats() const
{
	Stats::EntityStats totalStats = _stats + _bonusStats;

	for (const auto* module : _modules)
	{
		totalStats += module->GetStats();
	}

	return totalStats;
}

Stats::WeaponStats Entity::GetWeaponStats() const
{
	Stats::WeaponStats totalStats = _weaponStats;

	for (const auto* module : _modules)
	{
		totalStats += module->GetWeaponStats();
	}

	return totalStats;
}

void Entity::AddModule(Module* module)
{
	module->Initialize(this);
	_modules.push_back(module);

	updateSize();
}

void Entity::ChangeWeapon(Weapon* weapon)
{
	_weapon = weapon;
}

void Entity::updateSize()
{
	const float scale = 1.f + GetTotalStats().Size;

	_shape.setScale(scale, scale);
	_body->GetFixtureList()->GetShape()->m_radius = Game::PixelToMeter(_shape.getSize().x * scale / 3.f);
}

void Entity::onDeath()
{
	AnimationManager::GetInstance().AddDeathAnimation(DeathAnimation(_shape.getPosition()));

	updateHealthDifference();

	// Set the entity to sensor to not collide with other entities
	_body->GetFixtureList()->SetSensor(true);

	// Play sound according to the group
	if (_groupIndex == Group::ENEMY)
	{
		AudioManager::GetInstance().PlaySound(Sound::ENEMY_DEATH);
	}
	else
	{
		_weapon->StopCharging();
		_game.SetState(GameState::DEAD);
	}
}
