#ifndef DOOR_H
# define DOOR_H

# include "../core/structures.h"

// ==== Door Updates ====
void	update_doors(t_game *game);

// ==== Door Interactions ====
void	handle_door_interact(t_game *g);
t_door	*get_the_door(t_game *g, int x, int y);

// ==== Door Rendering / Raycasting ====
void	update_ray_door(t_game *game, t_ray *ray, int map_y, int map_x);
void	start_draw_doors(t_game *game, t_ray *ray, int x);

#endif
