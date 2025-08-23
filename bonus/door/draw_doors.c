#include "bonus.h"
#include "game.h"

static int	get_door_texture_x(t_game *g, t_ray *ray, t_img *text);
static void	init_column(t_column *col, t_game *g, t_ray *ray, int x);
static void	draw_doors(t_game *game, t_column *col);

void	start_draw_doors(t_game *game, t_ray *ray, int x)
{
	t_column	col;

	init_column(&col, game, ray, x);
	draw_doors(game, &col);
}

static void	draw_doors(t_game *game, t_column *col)
{
	t_draw_util	draw;
	int			color;

	draw.center = game->mlx->height / 2 + (int)game->player.pitch_angle
		+ (int)game->player.vertical.jump_off
		- (int)game->player.vertical.crouch_off;
	draw.step = (double)col->texture->height / col->wall_height;
	draw.tex_pos = (col->pixel_top - draw.center + col->wall_height / 2)
		* draw.step;
	draw.window_y = col->pixel_top;
	while (draw.window_y <= col->pixel_bottom)
	{
		if (draw.tex_pos >= 0.0 && draw.tex_pos < col->texture->height)
		{
			draw.tex_y = (int)draw.tex_pos;
			color = get_pixel_from_img(col->texture,
					col->texture_x, draw.tex_y);
			if (color != 0)
				ft_put_pixel(&game->mlx->frame_img,
					col->window_x, draw.window_y, color);
		}
		draw.tex_pos += draw.step;
		draw.window_y++;
	}
}

static void	init_column(t_column *col, t_game *g, t_ray *ray, int x)
{
	int	win_h;
	int	pitch;

	win_h = g->mlx->height;
	col->wall_height = (int)(win_h / ray->door_feat.perp_dist);
	pitch = (int)(g->player.pitch_angle + g->player.vertical.jump_off
			- g->player.vertical.crouch_off);
	col->pixel_top = (win_h - col->wall_height) / 2 + pitch;
	if (col->pixel_top < 0)
		col->pixel_top = 0;
	col->pixel_bottom = (win_h + col->wall_height) / 2 + pitch;
	if (col->pixel_bottom >= win_h)
		col->pixel_bottom = win_h - 1;
	col->window_x = x;
	col->texture = get_door_texture(g, ray->door_feat.ptr);
	col->texture_x = get_door_texture_x(g, ray, col->texture);
}

static int	get_door_texture_x(t_game *g, t_ray *ray, t_img *text)
{
	double	wall_x;
	int		tex_x;

	if (ray->door_feat.side == 0)
		wall_x = g->player.pos.y + ray->door_feat.perp_dist * ray->dir.y;
	else
		wall_x = g->player.pos.x + ray->door_feat.perp_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)text->width);
	if ((ray->door_feat.side == 0 && ray->dir.x < 0)
		|| (ray->door_feat.side == 1 && ray->dir.y > 0))
	{
		tex_x = text->width - tex_x - 1;
	}
	return (tex_x);
}
