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

void	update_colors(t_texture *texture)
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

int	get_pixel_from_img(t_img *img, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

t_img	*xpm_to_img(void *mlx, char *path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img_ptr = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->img_ptr)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(mlx, img->img_ptr);
		free(img);
		return (NULL);
	}
	return (img);
}
