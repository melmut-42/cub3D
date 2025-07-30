#include "game.h"

static void	free_data(t_data *data);

// * Frees the entire game structure including its data
void	free_game(t_game *game)
{
	if (!game)
		return ;

	// Free all allocated textures
	free_data(&game->data);

	// Free the mlx structure and its resources (includes textures)
	destroy_img(game);



	// Free the game structure itself
	ft_free((void **)&game);
}

// * Helper function to safely free pointer and set it to NULL
void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// * Free 2D array of strings
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

// * Helper function to free allocated texture paths and map matrix
static void	free_data(t_data *data)
{
	ft_free((void **)&data->texture.ea_path);
	ft_free((void **)&data->texture.we_path);
	ft_free((void **)&data->texture.no_path);
	ft_free((void **)&data->texture.so_path);
	free_tab(data->map.matrix);
}
