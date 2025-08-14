#include "game.h"

bool	is_player(char player)
{
	int		i;
	char	*dir_set;

	dir_set = DIR_SET;
	i = 0;
	while (dir_set[i])
	{
		if (player == dir_set[i])
			return (true);
		i++;
	}
	return (false);
}
