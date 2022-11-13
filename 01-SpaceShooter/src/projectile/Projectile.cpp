#include "projectile/Projectile.h"

#include "Game.h"
#include "manager/AnimationManager.h"

Projectile::Projectile(b2Body* body, const sf::Vector2f position, 
                       const sf::Texture& texture, ShapeType shapeType,
                       const float angle, float size, const b2Vec2 velocity, const sf::Time lifeTime,
                       const float damage, const bool canPierce, const Group groupIndex, bool trail) :
	DrawableObject(body, position)
{
	_lifeTime = lifeTime;
	_currentLifeTime = sf::Time::Zero;

	_size = size;
	_damage = damage;
	_canPierce = canPierce;
	_groupIndex = groupIndex;
	_trail = trail;

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setRotation(angle);
	_sprite.setScale(size, size);
	_sprite.setPosition(position);

	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circleShape;

	if (shapeType == ShapeType::RECTANGLE)
	{
		dynamicBox.SetAsBox(Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f), Game::PixelToMeter(_sprite.getGlobalBounds().height / 2.f));

		fixtureDef.shape = &dynamicBox;
	}
	else
	{
		circleShape.m_radius = Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f);

		fixtureDef.shape = &circleShape;
	}

	fixtureDef.density = 0.f;
	fixtureDef.restitution = 0.f;
	fixtureDef.friction = 0.f;
	fixtureDef.filter.groupIndex = static_cast<int16>(_groupIndex);
	fixtureDef.isSensor = true;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	_body->CreateFixture(&fixtureDef);

	_body->SetTransform(Game::PixelToMeter(position), Game::DegreeToRad(_sprite.getRotation()));
	_body->SetType(b2_dynamicBody);
	_body->SetLinearVelocity(velocity);
}

void Projectile::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Projectile::Update(const sf::Time elapsed)
{
	_currentLifeTime += elapsed;

	float scale = _size * (1.f - _currentLifeTime.asSeconds() / _lifeTime.asSeconds());

	if (scale < 0.f)
	{
		scale = 0.f;
	}

	_sprite.setScale(scale, scale);
	_sprite.setPosition(Game::MeterToPixel(_body->GetPosition()));
	_sprite.setRotation(Game::RadToDegree(_body->GetAngle()));
	_sprite.setColor(GetColor(_groupIndex));

	_body->GetFixtureList()->GetShape()->m_radius = Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f);

	if (_trail)
	{
		AnimationManager::GetInstance().AddTrail({Game::MeterToPixel(_body->GetPosition()), Game::RadToDegree(_body->GetAngle()), _groupIndex});
	}
}

void Projectile::OnImpact(const sf::Vector2f impactPoint)
{
	if (!_canPierce)
	{
		_currentLifeTime = _lifeTime;
	}

	AnimationManager& animationManager = AnimationManager::GetInstance();
	animationManager.AddHitAnimation(impactPoint);
	animationManager.AddTextAnimation(DamageTextAnimation(
		impactPoint, 
		std::to_string(static_cast<int>(_damage)),
		_groupIndex == Group::ENEMY_PROJECTILE ? sf::Color::Red : sf::Color::Yellow
	));
}

bool Projectile::IsDead() const
{
	return _currentLifeTime >= _lifeTime;
}
