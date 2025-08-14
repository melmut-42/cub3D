#include "game.h"

static void	free_data(t_data *data);

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_data(&game->data);
	destroy_img(game);
	ft_free((void **)&game);
}

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_tab(char **state)
{
	int	i;

	if (!state)
		return ;
	i = 0;
	while (state[i])
	{
		ft_free((void **)&state[i]);
		i++;
	}
	ft_free((void **)&state);
}

static void	free_data(t_data *data)
{
	ft_free((void **)&data->texture.ea_path);
	ft_free((void **)&data->texture.we_path);
	ft_free((void **)&data->texture.no_path);
	ft_free((void **)&data->texture.so_path);
	ft_free((void **)&data->texture.door);
	free_tab(data->map.matrix);
}
