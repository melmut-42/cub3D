#include "../includes/game.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2) 
	{
		ft_putendl_fd("Usage: ./cub3d <map_file.cub>", STDERR_FILENO); // ? Does it count as error or not?
		return (EXIT_FAILURE);
	}
	if (!has_valid_cub_extension(argv[1])) 
	{
		display_error_message(INV_EXT, false);
		return (EXIT_FAILURE);
	}
	game = init_game(argv[1]);
	if (!game)
		return (EXIT_FAILURE);
	display_game(game);
	free_game(game);
	return (EXIT_SUCCESS);
}
