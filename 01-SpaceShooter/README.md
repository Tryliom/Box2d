# TODO

- Add a projectileManager to manage all projectiles in Game and pass Game to Projectile
- Add a AnimationText that display damage taken by any entity going to a random direction from the center of the entity
- Add more variation to hit animation, so add an enum for it in assets
- Add a hit animation on the impact point instead of the projectile position
- Check if the enemy has the time to do an attack or force it to finish his attack
- Add an animation when an entity is destroyed (maybe keep entity shape living while animation is not finished)
- Display hp bar of the boss
- Add more speed to enemy while out of screen
- Make Tail a class that can be assigned to any entities, create a tail for each enemy

- Create experience shards that rotate on themselves and are attracted by the player when a enemy is destroyed
- Make enemies drop xp shards when destroyed
- Add level to player, each level require xp. When level up, he can choose to upgrade his EntityStats or WeaponStats or gain a new module

- Add an enemy that load his attack in 5sec (with an animation) and gain high velocity in the direction his facing
- Faire une struct TextComponent qui a lui même un vector de struct Text avec couleur et tout pour les interfaces