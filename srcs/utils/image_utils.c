#include "game.h"

/**
 * @brief Puts a pixel of a specific color onto an image buffer.
 *
 * @details
 * - Checks for bounds to avoid writing outside the image.
 * - Computes the memory address of the pixel and writes the color value.
 *
 * @param img (t_img *): Pointer to the image structure.
 * @param x (int): X-coordinate of the pixel.
 * @param y (int): Y-coordinate of the pixel.
 * @param color (int): Color value in 0xRRGGBB format.
 *
 * @return void
 */
void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Converts separate RGB values into a single integer color.
 *
 * @details
 * - Shifts red and green components to their proper positions.
 * - Combines R, G, and B into a 24-bit integer.
 *
 * @param r (int): Red component (0–255).
 * @param g (int): Green component (0–255).
 * @param b (int): Blue component (0–255).
 *
 * @return (int): Color value in 0xRRGGBB format.
 */
int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Updates the ceiling and floor colors in a texture structure.
 *
 * @details
 * - Uses RGB values stored in the game's texture data.
 * - Converts RGB arrays to single integer colors using rgb_to_int().
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param texture (t_texture *): Pointer to the texture structure to update.
 *
 * @return void
 */
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

/**
 * @brief Retrieves the color of a pixel from an image buffer.
 *
 * @details
 * - Checks coordinates to ensure they are within the image bounds.
 * - Returns 0 if the coordinates are out of range.
 *
 * @param img (t_img *): Pointer to the image structure.
 * @param x (int): X-coordinate of the pixel.
 * @param y (int): Y-coordinate of the pixel.
 *
 * @return (int): Color value at the pixel location or 0 if out of bounds.
 */
int	get_pixel_from_img(t_img *img, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

/**
 * @brief Loads an XPM image file into an image structure using MiniLibX.
 *
 * @details
 * - Allocates a new t_img structure.
 * - Loads the XPM image and retrieves its pixel data address.
 * - Frees allocated memory and returns NULL on failure.
 *
 * @param mlx (void *): Pointer to the MLX instance.
 * @param path (char *): File path to the XPM image.
 *
 * @return (t_img *): Pointer to the loaded image, or NULL on failure.
 */
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
