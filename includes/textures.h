#ifndef TEXTURES_H
#define TEXTURES_H

#include "game.h"

// Load all textures from their paths
int	load_texture(t_game *game, t_texture *tex, const char *path, enum e_dirs dir);

// Free all loaded texture images
void	free_textures(t_game *game);

// Draw pixel helper (optional, for manual pixel puts)
void	ft_put_pixel(t_img *img, int x, int y, int color);

#endif
