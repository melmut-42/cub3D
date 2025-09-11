#include "game.h"

/**
 * @brief Retrieves the correct wall texture based on ray direction and side.
 *
 * @details
 * - Returns the door texture if the ray hit a door.
 * - Uses ray side and direction to select between EAST, WEST, SOUTH, or NORTH textures.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param ray (t_ray *): Pointer to the ray that hit the wall.
 *
 * @return (t_img *): Pointer to the appropriate wall texture.
 */
t_img	*get_wall_texture(t_game *g, t_ray *ray)
{
	if (ray->is_door)
		return (&g->data.texture.doors[0]);
	if (ray->side == 0 && ray->dir.x > 0)
		return (&g->data.texture.textures[EAST]);
	if (ray->side == 0 && ray->dir.x < 0)
		return (&g->data.texture.textures[WEST]);
	if (ray->side == 1 && ray->dir.y > 0)
		return (&g->data.texture.textures[SOUTH]);
	return (&g->data.texture.textures[NORTH]);
}

/**
 * @brief Calculates the X-coordinate on a wall texture to sample.
 *
 * @details
 * - Computes wall_x as the exact point where the ray hit the wall.
 * - Converts wall_x to a texture X coordinate based on the texture width.
 * - Flips the texture coordinate for specific ray directions to ensure proper orientation.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param ray (t_ray *): Pointer to the ray that hit the wall.
 * @param tex (t_img *): Pointer to the wall texture.
 *
 * @return (int): X-coordinate on the texture image.
 */
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

/**
 * @brief Performs linear interpolation between two values.
 *
 * @details
 * - Calculates the interpolated value based on the ratio t.
 * - Useful for smooth transitions such as weapon sway or animations.
 *
 * @param start (float): Starting value.
 * @param end (float): Ending value.
 * @param t (float): Interpolation factor (0.0 to 1.0).
 *
 * @return (float): Interpolated value.
 */
float	lerp(float start, float end, float t)
{
	return (start + (end - start) * t);
}
