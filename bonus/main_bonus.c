#include "../includes/core/game.h"

static int	execube(t_game *game)
{
	init_hooks(game);
	mlx_loop(game->mlx->mlx_ptr);
	free_game(game);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3d <map_file.cub>", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!has_valid_cub_extension(argv[1]))
	{
		display_error_message(ERR_EXT, false);
		return (EXIT_FAILURE);
	}
	game = init_game(argv[1]);
	if (!game)
		return (EXIT_FAILURE);
	return (execube(game));
}
