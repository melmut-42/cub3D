#include "game.h"

bool	check_map(t_game *game)
{
	char	**cpy;

	cpy = copy_matrix(game, game->data.map.matrix);
	if (!cpy)
		return (false);
	
}

void	flood_fill(t_game *game, char **matrix, t_position pos)
{
	
}
