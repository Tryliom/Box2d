#include "entity/Entity.h"

#include "Game.h"
#include "animation/TextAnimation.h"
#include "manager/AnimationManager.h"
#include "manager/AudioManager.h"

Entity::Entity(Game& game, const sf::Vector2f position, const sf::Texture& texture,
               const float health, const float maxHealth, 
               const Stats::EntityStats stats, const Group groupIndex) :
	DrawableObject(game.GetNewBody(), position),
	_game(game)
{
	_health = health;
	_maxHealth = maxHealth;

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
	circle.m_radius = Game::PixelToMeter(_shape.getSize().x / 3.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.f;
	fixtureDef.restitution = 1.f;
	fixtureDef.friction = 0.5f;
	fixtureDef.filter.groupIndex = static_cast<int16>(_groupIndex);
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	_body->CreateFixture(&fixtureDef);

	_body->SetLinearDamping(0.5f);
	_body->SetTransform(Game::PixelToMeter(position), Game::DegreeToRad(_shape.getRotation()));
	_body->SetType(b2_dynamicBody);
}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto* module : _modules)
	{
		target.draw(*module, states);
	}

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

void Entity::Update(const sf::Time elapsed)
{
	if (_health < _maxHealth)
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
		_weapon->UpdatePosition(_shape.getPosition());
		_weapon->Update(elapsed);
	}

	if (_weapon != nullptr && _weapon->CanShoot())
	{
		_weapon->Shoot(this, _groupIndex == Group::PLAYER ? Group::PLAYER_PROJECTILE : Group::ENEMY_PROJECTILE);
		_weapon->StartCharging(this);
	}

	for (auto* module : _modules)
	{
		module->Update(elapsed, this);
	}
}

void Entity::Move()
{
	// Add a linear velocity to the body to make it move to the angle it is facing
	if (_body->GetLinearVelocity().Length() < GetTotalStats().GetMaxSpeed())
	{
		_body->SetLinearVelocity(
			_body->GetLinearVelocity() + 
			Game::GetLinearVelocity(GetTotalStats().GetSpeed(), Game::RadToDegree(_body->GetAngle()))
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
	_health -= projectile->GetDamage();

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
	const float collisionDamage = GetTotalStats().GetCollisionDamage(entity->GetTotalStats().GetCollisionDamage());
	_health -= collisionDamage;

	AudioManager::GetInstance().PlaySound(Sound::ENTITY_COLLISION);

	AnimationManager& animationManager = AnimationManager::GetInstance();
	animationManager.AddTextAnimation(DamageTextAnimation(
		_shape.getPosition(),
		std::to_string(static_cast<int>(collisionDamage)),
		_groupIndex == Group::PLAYER ? sf::Color::Red : sf::Color::Yellow
	));

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

void Entity::AddBonusStats(const Stats::EntityStats bonusStats)
{
	_bonusStats += bonusStats;

	if (bonusStats.Size != 0.f)
	{
		const float scale = 1.f + GetTotalStats().Size;

		_shape.setScale(scale, scale);
		_body->GetFixtureList()->GetShape()->m_radius = Game::PixelToMeter(_shape.getSize().x / 3.f * scale);
	}
}

void Entity::AddModule(Module* module)
{
	module->Initialize(this);
	_modules.push_back(module);
}

void Entity::onDeath()
{
	// Play sound according to the group
	if (_groupIndex == Group::ENEMY)
	{
		AudioManager::GetInstance().PlaySound(Sound::ENEMY_DEATH);
	}
	else
	{
		AudioManager::GetInstance().PlayMusic(Music::DEATH);
	}
}
