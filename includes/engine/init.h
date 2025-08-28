#ifndef INIT_H
# define INIT_H

# include "../core/structures.h"

// ==== Game Initialization ====
bool	init_data(t_game *game);
bool	init_player(t_game *game);
bool	init_weapon(t_game *game);
void	weapon_ctor(t_weapon *weapon);
bool	init_doors(t_game *game);

// ==== Texture Validation ====
bool	is_texture_valid(t_texture *texture);

// ==== Map & Texture Processing ====
bool	process_map_data(t_game *game, t_map *map, int fd);
bool	process_texture_data(t_game *game, t_texture *texture, int fd);
void	process_rgb(t_game *game, int rgb[3], char *data);
void	update_colors(t_game *g, t_texture *texture);

#endif
