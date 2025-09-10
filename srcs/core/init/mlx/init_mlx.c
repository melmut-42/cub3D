#include "game.h"

static void	setup_mlx_dimensions(t_mlx *mlx, int w, int h, char *title);

/**
 * @brief Initializes the MLX context and game window.
 *
 * @details
 * - Allocates memory for the MLX wrapper structure.
 * - Initializes MLX with mlx_init().
 * - Creates a new window with given width, height, and title.
 * - Stores window dimensions and title in the MLX struct.
 * - Hides the mouse cursor inside the window.
 * - Assigns the MLX structure to the game instance.
 *
 * If any step fails, an error message is displayed and false is returned.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param width (int): Window width in pixels.
 * @param height (int): Window height in pixels.
 * @param title (char *): Window title string.
 *
 * @return (bool): true if initialization succeeded, false otherwise.
 */
bool	init_mlx(t_game *game, int width, int height, char *title)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
	{
		display_error_message(ERR_MLX, true);
		return (false);
	}
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		display_error_message(ERR_MLX, true);
		return (false);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, title);
	if (!mlx->win_ptr)
	{
		display_error_message(ERR_MLX, true);
		return (false);
	}
	setup_mlx_dimensions(mlx, width, height, title);
	mlx_mouse_hide(mlx->mlx_ptr, mlx->win_ptr);
	game->mlx = mlx;
	return (true);
}

/**
 * @brief Creates the main frame buffer image.
 *
 * @details
 * - Allocates an MLX image with the same dimensions as the window.
 * - Retrieves a pointer to the pixel buffer (addr) along with
 *   image properties (bpp, line length, endian).
 * - Stores the image width and height in the structure.
 *
 * This frame buffer is later used for all rendering before being
 * drawn to the screen with mlx_put_image_to_window().
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if the image is successfully created, false otherwise.
 */
bool	init_frame_image(t_game *game)
{
	t_img	*frame_img;

	frame_img = &game->mlx->frame_img;
	frame_img->img_ptr = mlx_new_image(game->mlx->mlx_ptr,
			game->mlx->width, game->mlx->height);
	if (!frame_img->img_ptr)
	{
		display_error_message(ERR_MLX, true);
		return (false);
	}
	frame_img->addr = mlx_get_data_addr(frame_img->img_ptr, &frame_img->bpp,
			&frame_img->line_len, &frame_img->endian);
	if (!frame_img->addr)
	{
		display_error_message(ERR_MLX, true);
		return (false);
	}
	frame_img->width = game->mlx->width;
	frame_img->height = game->mlx->height;
	return (true);
}

/**
 * @brief Stores window dimensions and title in the MLX structure.
 *
 * @param mlx (t_mlx *): Pointer to MLX wrapper structure.
 * @param w (int): Window width in pixels.
 * @param h (int): Window height in pixels.
 * @param title (char *): Window title string.
 * 
 * @return void
 */
static void	setup_mlx_dimensions(t_mlx *mlx, int w, int h, char *title)
{
	mlx->width = w;
	mlx->height = h;
	mlx->title = title;
}
