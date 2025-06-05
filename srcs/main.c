#include "../includes/game.h"

int	main(int argc, char **argv)
{
	if (argc != 2) 
	{
		ft_putendl_fd("Usage: ./cub3d <map_file.cub>", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!has_valid_cub_extension(argv[1])) 
	{
		ft_putendl_fd("Error: Invalid map file extension. Expected .cub", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
