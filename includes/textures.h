#ifndef TEXTURES_H
#define TEXTURES_H

#include "game.h"

// Free all loaded texture images
void	free_textures(t_game *game);

// Draw pixel helper (optional, for manual pixel puts)
void	ft_put_pixel(t_img *img, int x, int y, int color);

int		rgb_to_int(int r, int g, int b);


#endif
