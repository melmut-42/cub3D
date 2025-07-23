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

int	get_texture_x(t_game *g, t_ray *ray, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	// Calculate the X coordinate of the wall texture based on the ray's side
	if (ray->side == 0)
		wall_x = g->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = g->player.pos.x + ray->perp_wall_dist * ray->dir.x;

	// Adjust wall_x to be within the texture width
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);

	// Adjust texture X coordinate based on ray side and direction
	if ((ray->side == 0 && ray->dir.x < 0)
		|| (ray->side == 1 && ray->dir.y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

// * Initializes the column structure for rendering
static void init_column(t_column *col, t_game *g, t_ray *ray, int x)
{
	int win_h;
	int pitch;

	// Initialize the column structure
	win_h = g->mlx->height;
	col->wall_height = (int)(win_h / ray->perp_wall_dist);

	// ! Use pitch-adjusted screen center
	pitch = (int)(g->player.pitch_angle
					+ g->player.vertical.jump_off
					- g->player.vertical.crouch_off);

	col->pixel_top = (win_h - col->wall_height) / 2 + pitch; // adjusted for pitch

	if (col->pixel_top < 0)
		col->pixel_top = 0;

	col->pixel_bottom = (win_h + col->wall_height) / 2 + pitch; // adjusted for pitch

	if (col->pixel_bottom >= win_h)
		col->pixel_bottom = win_h - 1;

	// Set the column texture and texture X coordinate
	col->texture = get_wall_texture(g, ray);
	col->texture_x = get_texture_x(g, ray, col->texture);
	col->screen_x = x;
}

// * Draws the ceiling for a given column
static void draw_ceiling(t_game *g, t_column *col, int color)
{
	int	y;

	y = 0;
	while (y < col->pixel_top)
		ft_put_pixel(&g->mlx->frame_img, col->screen_x, y++, color);
}

// * Draws the floor for a given column
static void draw_floor(t_game *g, t_column *col, int color)
{
	int	y;
	int	win_h;

	win_h = g->mlx->height;
	y = col->pixel_bottom + 1;

	while (y < win_h)
		ft_put_pixel(&g->mlx->frame_img, col->screen_x, y++, color);
}

// * Draws the wall texture for a given column
static void draw_wall(t_game *g, t_column *col)
{
	int		center;
	int		tex_y;
	int		y;
	double	tex_pos;
	double	step;

	// Combine camera look, jump rise and crouch drop
	center = g->mlx->height / 2 + (int)g->player.pitch_angle
		+ (int)g->player.vertical.jump_off - (int)g->player.vertical.crouch_off;

	// Calculate the texture position based on the column's pixel top
	step	= (double)col->texture->height / col->wall_height;
	tex_pos	= (col->pixel_top - center + col->wall_height / 2) * step;
	y		= col->pixel_top;

	while (y <= col->pixel_bottom)
	{
		if (tex_pos >= 0.0 && tex_pos < col->texture->height)
		{
			// Calculate the texture Y coordinate based on the texture position
			tex_y = (int)tex_pos;
			ft_put_pixel(&g->mlx->frame_img, col->screen_x, y,
				*(unsigned int *)(col->texture->addr
				+ tex_y * col->texture->line_len
				+ col->texture_x * (col->texture->bpp / 8)));
		}
		tex_pos += step;
		y++;
	}
}

// * Draws a column of the wall texture based on the ray casting results
void draw_column(t_game *g, t_ray *ray, int x)
{
	t_column	col;
	int			ceil_col;
	int			floor_col;

	init_column(&col, g, ray, x);

	ceil_col = rgb_to_int(
		g->data.texture.ceil_rgb[0],
		g->data.texture.ceil_rgb[1],
		g->data.texture.ceil_rgb[2]);

	floor_col = rgb_to_int(
		g->data.texture.floor_rgb[0],
		g->data.texture.floor_rgb[1],
		g->data.texture.floor_rgb[2]);

	// Draw the ceiling, wall, and floor for the column
	draw_ceiling(g, &col, ceil_col);
	draw_wall(g, &col);
	draw_floor(g, &col, floor_col);
}
