#include "bonus.h"
#include "game.h"

static void	init_column(t_column *col, t_game *g, t_ray *ray, int x)
{
	int	win_h;
	int	pitch;

	win_h = g->mlx->height;
	col->wall_height = (int)(win_h / ray->perp_wall_dist);
	pitch = (int)(g->player.pitch_angle + g->player.vertical.jump_off
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
	int	window_height;

	window_height = g->mlx->height;
	y = col->pixel_bottom + 1;
	while (y < window_height)
		ft_put_pixel(&g->mlx->frame_img, col->window_x, y++, color);
}

static void	draw_wall(t_game *g, t_column *col)
{
	t_draw_util	draw;
	int			color;

	draw.center = g->mlx->height / 2 + (int)g->player.pitch_angle
		+ (int)g->player.vertical.jump_off - (int)g->player.vertical.crouch_off;
	draw.step = (double)col->texture->height / col->wall_height;
	draw.tex_pos = (col->pixel_top - draw.center + col->wall_height / 2)
		* draw.step;
	draw.window_y = col->pixel_top;
	while (draw.window_y <= col->pixel_bottom)
	{
		if (draw.tex_pos >= 0.0 && draw.tex_pos < col->texture->height)
		{
			draw.tex_y = (int)draw.tex_pos;
			color = get_pixel_from_img(col->texture, col->texture_x,
					draw.tex_y);
			ft_put_pixel(&g->mlx->frame_img, col->window_x, draw.window_y,
					color);
		}
		draw.tex_pos += draw.step;
		(draw.window_y)++;
	}
}

void	draw_column(t_game *g, t_ray *ray, int x)
{
	t_column	col;

	init_column(&col, g, ray, x);
	draw_ceiling(g, &col, g->data.texture.ceil_color);
	draw_wall(g, &col);
	draw_floor(g, &col, g->data.texture.floor_color);
	if (ray->door_feat.ptr)
		start_draw_doors(g, ray, x);
}
