#include "game.h"

static void	draw_minimap_ray(t_game *g, t_img *img, double angle);

void	draw_minimap_rays(t_game *g, t_img *img)
{
	int		i;
	double	start;
	double	step;
	double	angle;

	start = atan2(g->player.dir.y, g->player.dir.x)
		- deg_to_rad(MINIMAP_FOV / 2.0);
	step = deg_to_rad((double)MINIMAP_FOV / RAY_COUNT);
	i = 0;
	while (i < RAY_COUNT)
	{
		angle = start + i * step;
		draw_minimap_ray(g, img, angle);
		i++;
	}
}

static void	draw_minimap_ray(t_game *g, t_img *img, double angle)
{
	double		len;
	t_axis		ray;
	t_axis_int	delta;
	t_axis_int	pos;
	int			index;

	index = get_angle_index(angle);
	len = 0.0;
	while (len < RAY_MAX_LEN)
	{
		ray.x = g->player.pos.x + g->data.cos_table[index] * len;
		ray.y = g->player.pos.y + g->data.sin_table[index] * len;
		delta.x = (ray.x - g->player.pos.x) / MINIMAP_SCALE;
		delta.y = (ray.y - g->player.pos.y) / MINIMAP_SCALE;
		pos.x = MINIMAP_RADIUS + delta.x;
		pos.y = MINIMAP_RADIUS + delta.y;
		if (delta.x * delta.x + delta.y * delta.y > MINIMAP_RADIUS * MINIMAP_RADIUS)
			return ;
		for (int dx = -1; dx <= 1; dx++)
			for (int dy = -1; dy <= 1; dy++)
				ft_put_pixel(img, pos.x + dx, pos.y + dy, 0xCCCC66);
		len += RAY_STEP_SIZE;
	}
}
