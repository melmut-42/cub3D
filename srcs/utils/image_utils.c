#include "game.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	update_colors(t_game *g, t_texture *texture)
{
	texture->ceil_color = rgb_to_int(
			g->data.texture.ceil_rgb[0],
			g->data.texture.ceil_rgb[1],
			g->data.texture.ceil_rgb[2]);
	texture->floor_color = rgb_to_int(
			g->data.texture.floor_rgb[0],
			g->data.texture.floor_rgb[1],
			g->data.texture.floor_rgb[2]);
}
