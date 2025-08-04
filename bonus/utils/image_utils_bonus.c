#include "game.h"

// * Function to put a pixel on the image at (x, y) with the specified color
void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	// Check for coordinates out of bounds
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return;

	// Calculate the address of the pixel in the image data
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// * Function to convert RGB values to a single integer
int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// * Function to get the pixel color from the image at (x, y)
int get_pixel_from_img(t_img *img, int x, int y)
{
	char *pixel;

	// Check for coordinates out of bounds
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);

	// Calculate the address of the pixel in the image data
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

// * Function to convert an XPM file to an image structure
t_img *xpm_to_img(void *mlx, char *path)
{
	t_img *img = malloc(sizeof(t_img));
	if (!img)
		return NULL;
	
	img->img_ptr = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->img_ptr)
	{
		free(img);
		return NULL;
	}
	
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(mlx, img->img_ptr);
		free(img);
		return NULL;
	}
	
	return (img);
}
