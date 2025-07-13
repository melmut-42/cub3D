#include "game.h"

static void	free_data(t_data *data);

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_data(&game->data);
	free(game);
}

static void	free_data(t_data *data)
{
	free(data->texture.ea_path);
	free(data->texture.we_path);
	free(data->texture.no_path);
	free(data->texture.so_path);
	free_tab(data->map.matrix);
}


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
