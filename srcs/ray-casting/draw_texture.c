#include "game.h"

static t_img	*get_wall_texture(t_game *g, t_ray *ray);
static void		draw_texture_line(t_game *g, t_column *d);
static int		get_texture_x(t_game *g, t_ray *ray, t_img *tex);

void	draw_column(t_game *g, t_ray *ray, int x)
{
	t_column	c;
	int			ceiling_color;
	int			floor_color;
	int			y;

	c.wall_height = (int)(g->mlx->height / ray->perp_wall_dist);
	c.pixel_top = (g->mlx->height - c.wall_height) / 2;
	if (c.pixel_top < 0)
		c.pixel_top = 0;
	c.pixel_bottom = (g->mlx->height + c.wall_height) / 2;
	if (c.pixel_bottom >= g->mlx->height)
		c.pixel_bottom = g->mlx->height - 1;
	c.texture = get_wall_texture(g, ray);
	c.texture_x = get_texture_x(g, ray, c.texture);
	c.screen_x = x;
	ceiling_color = rgb_to_int(
		g->data.texture.ceil_rgb[0],
		g->data.texture.ceil_rgb[1],
		g->data.texture.ceil_rgb[2]);
	floor_color = rgb_to_int(
		g->data.texture.floor_rgb[0],
		g->data.texture.floor_rgb[1],
		g->data.texture.floor_rgb[2]);
	y = 0;
	while (y < c.pixel_top)
		ft_put_pixel(&g->mlx->frame_img, x, y++, ceiling_color);
	draw_texture(g, ray, x);
	y = c.pixel_bottom + 1;
	while (y < g->mlx->height)
		ft_put_pixel(&g->mlx->frame_img, x, y++, floor_color);
}

void	draw_texture(t_game *g, t_ray *ray, int x)
{
	t_column	col;

	col.wall_height = (int)(g->mlx->height / ray->perp_wall_dist);
	col.pixel_bottom = (g->mlx->height - col.wall_height) / 2;
	if (col.pixel_bottom < 0)
		col.pixel_bottom = 0;
	col.pixel_top = (g->mlx->height + col.wall_height) / 2;
	if (col.pixel_top >= g->mlx->height)
		col.pixel_top = g->mlx->height - 1;
	col.texture = get_wall_texture(g, ray);
	col.texture_x = get_texture_x(g, ray, col.texture);
	col.screen_x = x;
	draw_texture_line(g, &col);
}

static t_img	*get_wall_texture(t_game *g, t_ray *ray)
{
	if (ray->side == 0 && ray->dir.x > 0)
		return (&g->data.texture.textures[EAST]);
	if (ray->side == 0 && ray->dir.x < 0)
		return (&g->data.texture.textures[WEST]);
	if (ray->side == 1 && ray->dir.y > 0)
		return (&g->data.texture.textures[SOUTH]);
	return (&g->data.texture.textures[NORTH]);
}

static int	get_texture_x(t_game *g, t_ray *ray, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = g->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = g->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir.x < 0) || (ray->side == 1 && ray->dir.y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

// TODO: Fix segmentatoon fault
static void	draw_texture_line(t_game *g, t_column *d)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	step = 1.0 * d->texture->height / d->wall_height;
	tex_pos = (d->pixel_bottom - g->mlx->height / 2 + d->wall_height / 2) * step;

	// ! This fixes the segmentation fault but it might not be correct behavior
	if (tex_pos < 0)
		tex_pos *= -1;
	y = d->pixel_bottom;
	while (y <= d->pixel_top)
	{
		tex_y = (int)tex_pos % d->texture->height;
		tex_pos += step;
		color = *(unsigned int *)(d->texture->addr
				+ (tex_y * d->texture->line_len + d->texture_x * (d->texture->bpp / 8)));
		ft_put_pixel(&g->mlx->frame_img, d->screen_x, y, color);
		y++;
	}
}


