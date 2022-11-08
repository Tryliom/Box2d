# TODO

- Apply spread and multiple bullets per shots in weapons
- Create a weapon that shoot regular bullets with short cooldown but low damage and 0.5 size

- Create an enemy space ship (looks like a camper)
	
- Create an enemy class that can charge an attack, shoot it, have a reload time between shots, etc.
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

- Les dégâts des sparks s'adaptent par rapport à la vitesse
- Créer une classe module qui a des event avec Entity en paramètre et déplacer tail et sparks dedans et pouvoir avoir plus de modèles
- Faire que la tail ne fasse pas de damage et soit juste décorative
- Si le group est enemy dans les bullets, set la color en rouge
- Faire une struct TextComponent qui a lui même un vector de struct Text avec couleur et tout pour les interfaces