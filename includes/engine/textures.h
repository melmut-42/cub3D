#ifndef TEXTURES_H
#define TEXTURES_H

# include "../core/structures.h"

void	free_textures(t_game *game);
void	ft_put_pixel(t_img *img, int x, int y, int color);
int		rgb_to_int(int r, int g, int b);
t_img	*get_wall_texture(t_game *g, t_ray *ray);
int		get_texture_x(t_game *g, t_ray *ray, t_img *tex);

#endif
