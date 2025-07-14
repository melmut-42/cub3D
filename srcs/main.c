#include "../includes/game.h"

// * Main function to start the game
int	main(int argc, char **argv)
{
	t_game	*game;

	// Validate argument count
	if (argc != 2) 
	{
		// TODO: verify usage message and error return (is this correct?)
		ft_putendl_fd("Usage: ./cub3d <map_file.cub>", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	// Validate map file extension
	if (!has_valid_cub_extension(argv[1])) 
	{
		display_error_message(INV_EXT, false);
		return (EXIT_FAILURE);
	}

	// Initialize the game with the given map file
	game = init_game(argv[1]);
	if (!game)
		return (EXIT_FAILURE);

	// Display and run the game
	display_game(game);

	// Free allocated resources
	free_game(game);

	return (EXIT_SUCCESS);
}
