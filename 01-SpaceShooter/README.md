# TODO

## Now

- Faire un HUDManager pour les �l�ments en jeu
- Faire un EntityManager qui g�re le joueur et les ennemis (passe le joueur aux ennemis lors de l'update)
- Au d�but du jeu, faire spawn le joueur en dehors du bord bas gauche de l'�cran et le faire avancer doucement au milieu de l'�cran o� il va rester tout en utilisant Move()
- Faire un WaveManager qui g�re les wave 
- Faire un HUDManager pour afficher toutes ces infos
- Faire un EnemyManager qui g�re tous les ennemis
- Le wave manager pourra former des groupes d'ennemis � incorporer dans des vagues al�atoirement, genre 3 camper et 1 angel, 5 camper.
- Adapter les ennemis par rapport � la vague
- Mettre dans les modules des EntityStats et WeaponStats � appliquer � l'entity qui peuvent �tre modifi�es � tout moment et utiliser les modules comme upgrade

## Gui 

- Faire une struct TextComponent qui a lui m�me un vector de struct Text avec couleur et tout pour les interfaces
- Display hp bar of the boss
- Make buttons
- Make a menu

## XP

- Create experience shards that rotate on themselves and are attracted by the player when a enemy is destroyed
- Make enemies drop xp shards when destroyed
- Add level to player, each level require xp. When level up, he can choose to upgrade his EntityStats or WeaponStats or gain a new module

## Future

- Add an enemy that load his attack in 5sec (with an animation) and gain high velocity in the direction his facing
- Ajouter un shotgun qui tire � courte distance avec masse bullets
- Make Tail a class that can be assigned to any entities, create a tail for each enemy