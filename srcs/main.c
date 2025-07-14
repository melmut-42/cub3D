#include "../includes/game.h"

// * Main function to initialize and run the game
static int	execube(char *map_file)
{
	t_game	*game;

	// Check if the map file has a valid .cub extension
	if (!has_valid_cub_extension(map_file))
	{
		display_error_message(INV_EXT, false);
		return (EXIT_FAILURE);
	}

	// Initialize the game structure and load the map
	game = init_game(map_file);
	if (!game)
		return (EXIT_FAILURE);

	// Initialize the mlx structure and create a new window
	game->mlx = setup_mlx(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, game);
	if (!game->mlx)
	{
		handle_error(MALLOC_ERR, false);
		return (EXIT_FAILURE);
	}

	// Load textures and initialize the game data
	display_game(game);

	// Hook ESC key and window close events
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->mlx->win_ptr, 17, 1L << 0, handle_close, game);
	
	// Start the mlx event loop
	mlx_loop(game->mlx->mlx_ptr);

	// Cleanup and free game resources // TODO: Make sure implementation works
	free_game(game);

	return (EXIT_SUCCESS);
}

// * Main function to start the game
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3d <map_file.cub>", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	return (execube(argv[1])); // handle_error returns null
}
