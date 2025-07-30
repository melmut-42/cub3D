#ifndef RENDER_H
# define RENDER_H

# include "../core/structures.h"

void	cast_ray(t_game *game, t_ray *ray, int x);
void	draw_texture(t_game *game, t_ray *ray, int x);
void	draw_column(t_game *game, t_ray *ray, int x);
void	rotate_vector(t_data *data, t_axis *vec, double angle);

#endif
