#include "../includes/game.h"

// * Main function to initialize and run the game
static int	execube(t_game *game)
{
	// Load textures and initialize the game data
	display_game(game);

	// Initialize hooks for mlx events
	init_hooks(game);
	
	// Start the mlx event loop
	mlx_loop(game->mlx->mlx_ptr);

	// Cleanup and free game resources // TODO: Make sure implementation works
	free_game(game);

	return (EXIT_SUCCESS);
}

// * Main function to start the game
int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3d <map_file.cub>", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	// Check if the map file has a valid .cub extension
	if (!has_valid_cub_extension(argv[1]))
	{
		display_error_message(INV_EXT, false);
		return (EXIT_FAILURE);
	}
	// Initialize the game structure and load the map
	game = init_game(argv[1]);
	if (!game)
		return (EXIT_FAILURE);
	return (execube(game)); // handle_error returns null
}
