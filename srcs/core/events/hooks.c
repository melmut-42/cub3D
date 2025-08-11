# include "game.h"

// * Function to setup event listeners/hooks
void	init_hooks(t_game *game)
{
	// Hook window close (clicking 'X')
	mlx_hook(game->mlx->win_ptr, 17, 1L << 0, handle_close, game);

	// Hook key press event for player movement and rotation
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, handle_keypress, game);
    mlx_hook(game->mlx->win_ptr, 3, 1L << 1, handle_keyrelease, game);

    // Set up the continuous game loop
    mlx_loop_hook(game->mlx->mlx_ptr, gameloop, game);
}

// * Handles the close event of the game window
int	handle_close(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}
