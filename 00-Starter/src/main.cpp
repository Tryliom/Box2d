#include "box2d/b2_body.h"
#include "box2d/b2_world.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"

int main()
{
	const b2Vec2 gravity(0.0f, 9.8f);
	b2World world(gravity);

	// Creating the floor
	b2BodyDef floorDef;
	floorDef.position.Set(0.0f, -10.0f);
	b2Body* floor = world.CreateBody(&floorDef);

	b2PolygonShape floorShape;
	floorShape.SetAsBox(50.0f, 10.0f);
	b2FixtureDef floorFixtureDef;
	floorFixtureDef.shape = &floorShape;
	floor->CreateFixture(&floorFixtureDef);

	// Creating the box
	b2BodyDef boxDef;
	boxDef.type = b2_dynamicBody;
	boxDef.position.Set(0.0f, 4.0f);
	b2Body* box = world.CreateBody(&boxDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(1.0f, 1.0f);
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1.0f;
	boxFixtureDef.friction = 0.3f;
	boxFixtureDef.restitution = 0.5f;
	box->CreateFixture(&boxFixtureDef);

	return 0;
}
