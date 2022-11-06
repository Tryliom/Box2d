# TODO

- Create a weapon class for any entity, using a specific bullet
- Create a basic bullet and a bullet class (only animated by code, not texture):
	- Create a bullet creation animation (charge) (2sec)
	- Create a bullet destruction animation
	- Create a bullet hit animation (spawn little particules when hit)
	- Create a bullet launch animation (after charge, send little particule backward)
- Assign it to entity in order to test it with the player
- Create an enemy space ship (looks like a camper)
	
- Add in entity class a weapon (that can be null)
- Create an enemy class that can charge an attack, shoot it, etc.
- Create basic enemy (camper) that move slowly in the direction of the player and charge attacks every 5sec that shoot a projectile with an animation, charge sound, shoot sound

- Create experience shards that rotate on themselves and are attracted by the player when a enemy is destroyed
- Manage contact with projectiles and player/enemies to apply damages
- Make enemies drop xp shards when destroyed

- Add level to player, each level require xp. When level up, he can choose to upgrade his:
	- Health
	- Speed
	- Rotation speed
	- Number of sparks per seconds
	- Health regen
	- Lifetime of sparks
	- damagePerSecond

- Add an enemy that load his attack in 5sec (with an animation) and gain high velocity in the direction his facing
- Add a AnimationText that display damage taken by any entity going to a random direction from the center of the entity