#include "game.h"

char	**copy_matrix(t_game *game, char **matrix)
{
	char	*copy;
	int		i;

	copy = ft_calloc((game->data.map.height) + 1, sizeof(char *));
	if (!copy)
	{
		game->error_flag = true;
		display_error_message(GAME_ERR, true);
		return (NULL);
	}
	i = 0;
	while (game->data.map.matrix[i])
	{
		copy[i] = ft_strdup(game->data.map.matrix[i]);
		if (!copy[i])
		{
			game->error_flag = true;
			display_error_message(GAME_ERR, true);
			free_tab(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}
