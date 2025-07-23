#ifndef PLAYER_H
# define PLAYER_H

# include "../core/structures.h"

void	update_player_movement(t_game *game, t_player *p, t_map *map);
void	stand_up(t_player *p, double dt);
void	jump_event(t_player *p, double dt);

#endif
