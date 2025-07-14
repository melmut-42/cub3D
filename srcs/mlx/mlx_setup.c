#include "game.h"

// TODO: consider returning a different value
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

	// Create a new window with the specified width, height, and title
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

	return (mlx);
}
