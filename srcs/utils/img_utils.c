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

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
