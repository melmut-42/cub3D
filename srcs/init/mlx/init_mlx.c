#include "game.h"



static void	setup_mlx_dimensions(t_mlx *mlx, int w, int h, char *title);

// * Sets up the mlx structure and creates a new window
bool	init_mlx(t_game *game, int width, int height, char *title)
{
	t_mlx	*mlx;

	// Allocate memory for the mlx structure
	mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
	{
		display_error_message(MLX_ERR, true);
		return (false);
	}

	// Initialize the mlx structure
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		display_error_message(MLX_ERR, true);
		return (false);
	}

	// Create a new window with the given dimensions and title
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, title);
	if (!mlx->win_ptr)
	{
		display_error_message(MLX_ERR, true);
		return (false);
	}
	setup_mlx_dimensions(mlx, width, height, title);
	game->mlx = mlx;
	return (true);
}

bool	init_frame_image(t_game *game)
{
	t_img	*frame_img;
	
	frame_img = &game->mlx->frame_img;
	frame_img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, game->mlx->width, game->mlx->height);
	if (!frame_img->img_ptr)
	{
		display_error_message(MLX_ERR, true);
		return (false);
	}
	frame_img->addr = mlx_get_data_addr(frame_img->img_ptr, &frame_img->bpp, &frame_img->line_len, &frame_img->endian);
	if (!frame_img->addr)
	{
		display_error_message(MLX_ERR, true);
		return (false);
	}
	frame_img->width = game->mlx->width;
	frame_img->height = game->mlx->height;
	return (true);
}

// Store dimensions and title
static void	setup_mlx_dimensions(t_mlx *mlx, int w, int h, char *title)
{
	mlx->width = w;
	mlx->height = h;
	mlx->title = title;
}
