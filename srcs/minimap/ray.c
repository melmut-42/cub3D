#include "game.h"


static void			draw_minimap_ray(t_game *g, t_img *img, double angle,
						t_axis_int offset);
static void			draw_ray_dot(t_img *img, t_axis_int pos);
static bool			is_inside_circle(t_axis_int delta);
static t_axis_int	get_ray_screen_pos(t_game *g, double angle, double len,
						t_axis_int offset);

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

static bool	is_inside_circle(t_axis_int delta)
{
	return (delta.x * delta.x + delta.y * delta.y <= MINIMAP_RADIUS
		* MINIMAP_RADIUS);
}

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
