
#include "game.h"

static int	get_door_texture_x(t_game *g, t_ray *ray, t_img *text);
static void	init_column(t_column *col, t_game *g, t_ray *ray, int x);
static void	draw_doors(t_game *game, t_column *col);

/**
 * @brief Entry point for rendering a door slice at a specific screen column.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param ray (t_ray *): Pointer to the ray that intersected a door.
 * @param x (int): Current screen column (x-coordinate) to render.
 *
 * @return void
 */
void	start_draw_doors(t_game *game, t_ray *ray, int x)
{
	t_column	col;

	init_column(&col, game, ray, x);
	draw_doors(game, &col);
}

/**
 * @brief Draws a single vertical slice of a door on the screen.
 *
 * @details
 * - Calculates vertical center, step size for texture sampling, and start position.
 * - Iterates over each pixel in the slice from top to bottom.
 * - Fetches the corresponding texture pixel and plots it if not transparent.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param col (t_column *): Pointer to the column containing rendering parameters.
 *
 * @return void
 */
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

/**
 * @brief Initializes a rendering column for drawing a door slice.
 *
 * @details
 * - Calculates wall height based on perpendicular distance.
 * - Computes top and bottom pixel positions, clamping to screen height.
 * - Determines which texture and texture x-coordinate to use.
 *
 * @param col (t_column *): Pointer to the column data structure to initialize.
 * @param g (t_game *): Pointer to the main game structure.
 * @param ray (t_ray *): Pointer to the ray that hit the door.
 * @param x (int): Current screen column (x-coordinate).
 *
 * @return void
 */
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

/**
 * @brief Calculates the x-coordinate on the door texture to sample.
 *
 * @details
 * - Determines the exact horizontal hit position on the door surface.
 * - Converts the fractional wall coordinate into a texture x-index.
 * - Flips the texture coordinate for certain ray directions and sides.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param ray (t_ray *): Pointer to the ray containing door hit data.
 * @param text (t_img *): Pointer to the door texture image.
 *
 * @return (int): The x-coordinate on the door texture.
 */
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
