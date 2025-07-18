#include "game.h"

// * Sets up the mlx structure and creates a new window
void	*setup_mlx(int width, int height, char *title, t_game *game)
{
	t_mlx	*mlx;

	// Allocate memory for the mlx structure
	mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
	{
		handle_error(MALLOC_ERR, false);
		return (NULL);
	}

	// Initialize the mlx structure
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		free(mlx);
		handle_error(MALLOC_ERR, false);
		return (NULL);
	}

	// Create a new window with the given dimensions and title
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, title);
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		ft_free((void **)&mlx->mlx_ptr);
		ft_free((void **)&mlx);
		free_game(game);

		handle_error(MALLOC_ERR, false);
		return (NULL);
	}

	// Store dimensions and title
	mlx->width = width;
	mlx->height = height;
	mlx->title = title;

	return (mlx);
}

int	create_frame_image(t_game *game)
{
	t_img	*frame_img;
	
	frame_img = &game->mlx->frame_img;
	frame_img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, game->mlx->width, game->mlx->height);
	if (!frame_img->img_ptr)
	{
		handle_error(MALLOC_ERR, false);
		return (0);
	}

	frame_img->addr = mlx_get_data_addr(frame_img->img_ptr, &frame_img->bpp, &frame_img->line_len, &frame_img->endian);
	frame_img->width = game->mlx->width;
	frame_img->height = game->mlx->height;

	return (1);
}
 