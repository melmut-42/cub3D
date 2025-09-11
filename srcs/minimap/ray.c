#include "game.h"


static void			draw_minimap_ray(t_game *g, t_img *img, double angle,
						t_axis_int offset);
static void			draw_ray_dot(t_img *img, t_axis_int pos);
static bool			is_inside_circle(t_axis_int delta);
static t_axis_int	get_ray_screen_pos(t_game *g, double angle, double len,
						t_axis_int offset);

/**
 * @brief Draws all minimap rays representing the player's field of view.
 *
 * @details
 * - Calculates the start angle based on player direction.
 * - Iterates through RAY_COUNT steps across the MINIMAP_FOV.
 * - Calls draw_minimap_ray() for each ray to render its dots.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param img (t_img *): Pointer to the minimap image buffer.
 * @param offset (t_axis_int): Offset for minimap placement on the screen.
 *
 * @return void
 */
void	draw_minimap_rays(t_game *g, t_img *img, t_axis_int offset)
{
	int		i;
	double	start;
	double	step;
	double	angle;

	start = atan2(g->player.dir.y, g->player.dir.x) - deg_to_rad(MINIMAP_FOV
			/ 2.0);
	step = deg_to_rad((double)MINIMAP_FOV / RAY_COUNT);
	i = 0;
	while (i < RAY_COUNT)
	{
		angle = start + i * step;
		draw_minimap_ray(g, img, angle, offset);
		i++;
	}
}

/**
 * @brief Draws a single ray on the minimap at a given angle.
 *
 * @details
 * - Increments length until reaching RAY_MAX_LEN or leaving the minimap circle.
 * - Converts world coordinates to screen coordinates with get_ray_screen_pos().
 * - Draws a small yellow dot for each step in the ray.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param img (t_img *): Pointer to the minimap image buffer.
 * @param angle (double): Current ray angle in radians.
 * @param offset (t_axis_int): Offset for minimap placement on the screen.
 *
 * @return void
 */
static void	draw_minimap_ray(t_game *g, t_img *img, double angle,
		t_axis_int offset)
{
	double		len;
	t_axis_int	pos;
	t_axis_int	delta;

	len = 0.0;
	while (len < RAY_MAX_LEN)
	{
		pos = get_ray_screen_pos(g, angle, len, offset);
		delta.x = pos.x - offset.x - MINIMAP_RADIUS;
		delta.y = pos.y - offset.y - MINIMAP_RADIUS;
		if (!is_inside_circle(delta))
			return ;
		draw_ray_dot(img, pos);
		len += RAY_STEP_SIZE;
	}
}

/**
 * @brief Converts a ray's world position to screen coordinates on the minimap.
 *
 * @details
 * - Uses precomputed cosine/sine tables for efficiency.
 * - Calculates displacement relative to player position.
 * - Scales the result according to MINIMAP_SCALE and applies screen offset.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param angle (double): Ray angle in radians.
 * @param len (double): Current distance along the ray.
 * @param offset (t_axis_int): Offset for minimap placement on the screen.
 *
 * @return (t_axis_int): The screen position of the ray point.
 */
static t_axis_int	get_ray_screen_pos(t_game *g, double angle, double len,
		t_axis_int offset)
{
	t_axis		ray;
	t_axis_int	pos;
	int			idx;

	idx = get_angle_index(angle);
	ray.x = g->player.pos.x + g->data.cos_table[idx] * len;
	ray.y = g->player.pos.y + g->data.sin_table[idx] * len;
	pos.x = offset.x + MINIMAP_RADIUS + (ray.x - g->player.pos.x)
		/ MINIMAP_SCALE;
	pos.y = offset.y + MINIMAP_RADIUS + (ray.y - g->player.pos.y)
		/ MINIMAP_SCALE;
	return (pos);
}

/**
 * @brief Checks if a delta coordinate is within the minimap circle.
 *
 * @details
 * - Uses the circle equation (x² + y² ≤ r²) for boundary check.
 *
 * @param delta (t_axis_int): Delta from minimap center.
 *
 * @return (bool): true if inside the circle, false otherwise.
 */
static bool	is_inside_circle(t_axis_int delta)
{
	return (delta.x * delta.x + delta.y * delta.y <= MINIMAP_RADIUS
		* MINIMAP_RADIUS);
}

/**
 * @brief Draws a small yellow dot at a given position for the minimap ray.
 *
 * @details
 * - Draws a 3x3 square of yellow pixels centered at the given position.
 * - Enhances ray visibility on the minimap.
 *
 * @param img (t_img *): Pointer to the minimap image buffer.
 * @param pos (t_axis_int): Screen position of the ray dot.
 *
 * @return void
 */
static void	draw_ray_dot(t_img *img, t_axis_int pos)
{
	t_axis_int	d;

	d.y = -1;
	while (d.y <= 1)
	{
		d.x = -1;
		while (d.x <= 1)
		{
			ft_put_pixel(img, pos.x + d.x, pos.y + d.y, COLOR_YELLOW);
			d.x++;
		}
		d.y++;
	}
}
