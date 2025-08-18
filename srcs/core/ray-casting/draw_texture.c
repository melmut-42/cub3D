#include "game.h"

static void	init_column(t_column *col, t_game *g, t_ray *ray, int x)
{
	int	win_h;
	int	pitch;

	win_h = g->mlx->height;
	col->wall_height = (int)(win_h / ray->perp_wall_dist);
	pitch = (int)(g->player.pitch_angle
			+ g->player.vertical.jump_off
			- g->player.vertical.crouch_off);
	col->pixel_top = (win_h - col->wall_height) / 2 + pitch;
	if (col->pixel_top < 0)
		col->pixel_top = 0;
	col->pixel_bottom = (win_h + col->wall_height) / 2 + pitch;
	if (col->pixel_bottom >= win_h)
		col->pixel_bottom = win_h - 1;
	col->texture = get_wall_texture(g, ray);
	col->texture_x = get_texture_x(g, ray, col->texture);
	col->window_x = x;
}

static void	draw_ceiling(t_game *g, t_column *col, int color)
{
	int	y;

	y = 0;
	while (y < col->pixel_top)
		ft_put_pixel(&g->mlx->frame_img, col->window_x, y++, color);
}

static void	draw_floor(t_game *g, t_column *col, int color)
{
	int	y;
	int	win_h;

	win_h = g->mlx->height;
	y = col->pixel_bottom + 1;
	while (y < win_h)
		ft_put_pixel(&g->mlx->frame_img, col->window_x, y++, color);
}

static void	draw_wall(t_game *g, t_column *col)
{
	int		center;
	int		tex_y;
	int		y;
	double	tex_pos;
	double	step;

	center = g->mlx->height / 2 + (int)g->player.pitch_angle
		+ (int)g->player.vertical.jump_off - (int)g->player.vertical.crouch_off;
	step = (double)col->texture->height / col->wall_height;
	tex_pos = (col->pixel_top - center + col->wall_height / 2) * step;
	y = col->pixel_top;
	while (y <= col->pixel_bottom)
	{
		if (tex_pos >= 0.0 && tex_pos < col->texture->height)
		{
			tex_y = (int)tex_pos;
			ft_put_pixel(&g->mlx->frame_img, col->window_x, y,
				*(unsigned int *)(col->texture->addr
					+ tex_y * col->texture->line_len
					+ col->texture_x * (col->texture->bpp / 8)));
		}
		tex_pos += step;
		y++;
	}
}

void	draw_column(t_game *g, t_ray *ray, int x)
{
	t_column	col;

	init_column(&col, g, ray, x);
	draw_ceiling(g, &col, g->data.texture.ceil_color);
	draw_wall(g, &col);
	draw_floor(g, &col, g->data.texture.floor_color);
}
