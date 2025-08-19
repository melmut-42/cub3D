#ifndef INIT_H
# define INIT_H

# include "../core/structures.h"

bool	init_data(t_game *game);
bool	init_player(t_game *game);
bool	is_texture_valid(t_texture *texture);
bool	process_map_data(t_game *game, t_map *map, int fd);
bool	process_texture_data(t_game *game, t_texture *texture, int fd);
void	process_rgb(t_game *game, int rgb[3], char *data);
void	update_colors(t_game *g, t_texture *texture);

#endif
