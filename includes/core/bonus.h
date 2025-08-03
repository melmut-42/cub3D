#ifndef BONUS_H
# define BONUS_H

#include "structures.h"

void	draw_hud(t_game *game);
void	mlx_out_txt(void *mlx, void *win, int x, int y, int color, char *str);
void	draw_minimap(t_game *game);
void	draw_minimap_rays(t_game *g, t_img *img, t_axis_int offset); 

#endif
