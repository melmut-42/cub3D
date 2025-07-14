#include "game.h"

// * Helper function to free allocated texture paths and map matrix
static void	free_data(t_data *data)
{
	free(data->texture.ea_path);
	free(data->texture.we_path);
	free(data->texture.no_path);
	free(data->texture.so_path);
	free_tab(data->map.matrix);
}

// * Frees a 2D array of strings
void	free_tab(char **state)
{
	int	i;

	if (!state)
		return ;
	i = 0;
	while (state[i])
	{
		free(state[i]);
		i++;
	}
	free(state);
}

// * Frees the entire game structure including its data
void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_data(&game->data);
	free(game);
}
