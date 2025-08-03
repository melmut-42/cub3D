#include "game.h"

// * Returns the correct wall texture based on the ray's collision side and direction
t_img	*get_wall_texture(t_game *g, t_ray *ray)
{
	if (ray->side == 0 && ray->dir.x > 0)
		return (&g->data.texture.textures[EAST]);
	if (ray->side == 0 && ray->dir.x < 0)
		return (&g->data.texture.textures[WEST]);
	if (ray->side == 1 && ray->dir.y > 0)
		return (&g->data.texture.textures[SOUTH]);
	return (&g->data.texture.textures[NORTH]);
}

// * Calculates the texture X coordinate based on the ray's wall hit position
int	get_texture_x(t_game *g, t_ray *ray, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = g->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = g->player.pos.x + ray->perp_wall_dist * ray->dir.x;

	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);

	if ((ray->side == 0 && ray->dir.x < 0)
		|| (ray->side == 1 && ray->dir.y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
