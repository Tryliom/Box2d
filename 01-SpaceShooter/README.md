# TODO

## Now

- Faire un HUDManager pour les éléments en jeu
- Faire un EntityManager qui gère le joueur et les ennemis (passe le joueur aux ennemis lors de l'update)
- Au début du jeu, faire spawn le joueur en dehors du bord bas gauche de l'écran et le faire avancer doucement au milieu de l'écran où il va rester tout en utilisant Move()
- Faire un WaveManager qui gère les wave 
- Faire un HUDManager pour afficher toutes ces infos
- Faire un EnemyManager qui gère tous les ennemis
- Le wave manager pourra former des groupes d'ennemis à incorporer dans des vagues aléatoirement, genre 3 camper et 1 angel, 5 camper.
- Adapter les ennemis par rapport à la vague
- Mettre dans les modules des EntityStats et WeaponStats à appliquer à l'entity qui peuvent être modifiées à tout moment et utiliser les modules comme upgrade

## Gui 

- Faire une struct TextComponent qui a lui même un vector de struct Text avec couleur et tout pour les interfaces
- Display hp bar of the boss
- Make buttons
- Make a menu

## XP

- Create experience shards that rotate on themselves and are attracted by the player when a enemy is destroyed
- Make enemies drop xp shards when destroyed
- Add level to player, each level require xp. When level up, he can choose to upgrade his EntityStats or WeaponStats or gain a new module

## Future

- Add an enemy that load his attack in 5sec (with an animation) and gain high velocity in the direction his facing
- Ajouter un shotgun qui tire à courte distance avec masse bullets
- Make Tail a class that can be assigned to any entities, create a tail for each enemy