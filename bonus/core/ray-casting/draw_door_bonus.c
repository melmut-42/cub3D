#include "game.h"

static double	get_door_perp(t_ray *ray)
{
	if (ray->door.perp > 1e-6)
		return (ray->door.perp);
	return (1e-6);
}

static int	clamp_i(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

static int	get_door_top(t_game *g, t_ray *ray, int h)
{
	double	o;
	int		pitch;

	o = ray->door.open;
	if (o < 0.0)
		o = 0.0;
	else if (o > 1.0)
		o = 1.0;
	pitch = (int)(g->player.pitch_angle
			+ g->player.vertical.jump_off
			- g->player.vertical.crouch_off);
	return ((g->mlx->height - h) / 2 + pitch - (int)(o * h));
}

static int	get_door_tex_x(t_game *g, t_ray *ray, t_img *tex)
{
	double	wall_x;
	int		tx;

	if (ray->door.side == 0)
		wall_x = g->player.pos.y + ray->door.perp * ray->dir.y;
	else
		wall_x = g->player.pos.x + ray->door.perp * ray->dir.x;
	wall_x -= floor(wall_x);
	tx = (int)(wall_x * tex->width);
	if ((ray->door.side == 0 && ray->dir.x < 0)
		|| (ray->door.side == 1 && ray->dir.y > 0))
		tx = tex->width - 1 - tx;
	return (clamp_i(tx, 0, tex->width - 1));
}

static void	draw_door_column(t_game *g, t_column *col)
{
	t_img	*tex;
	int		y;
	int		ty;
	double	step;
	double	tex_y;

	tex = col->texture;
	step = (double)tex->height / col->wall_height;
	tex_y = (clamp_i(col->pixel_top, 0, g->mlx->height - 1)
			- col->pixel_top) * step;
	y = clamp_i(col->pixel_top, 0, g->mlx->height - 1);
	while (y <= clamp_i(col->pixel_bottom, 0, g->mlx->height - 1))
	{
		ty = (int)(tex_y + (y - clamp_i(col->pixel_top, 0,
					g->mlx->height - 1)) * step);
		ft_put_pixel(&g->mlx->frame_img, col->screen_x, y,
			*(unsigned int *)(tex->addr + ty * tex->line_len
				+ col->texture_x * (tex->bpp / 8)));
		y++;
	}
}

void	draw_door_overlay_tex(t_game *g, t_ray *ray, int x)
{
	t_column	col;
	t_img		*tex;
	double		perp;
	int			top;

	tex = g->data.texture.door;
	perp = get_door_perp(ray);
	col.wall_height = (int)(g->mlx->height / perp);
	top = get_door_top(g, ray, col.wall_height);
	col.pixel_top = top;
	col.pixel_bottom = top + col.wall_height;
	col.texture_x = get_door_tex_x(g, ray, tex);
	col.screen_x = x;
	col.texture = tex;
	draw_door_column(g, &col);
}
