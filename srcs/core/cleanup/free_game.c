#include "game.h"

static void	free_data(t_data *data);

/**
 * @brief Frees all allocated memory and resources of the game.
 *
 * @details
 * - Frees map data and texture paths.
 * - Destroys all loaded images.
 * - Frees weapon and game structures.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * 
 * @return void
 */
void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_data(&game->data);
	destroy_img(game);
	ft_free((void **)&game->weapon);
	ft_free((void **)&game);
}

/**
 * @brief Safely frees a pointer and sets it to NULL.
 *
 * @param ptr (void **) Double pointer to the allocated memory.
 * 
 * @return void
 */
void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * @param state (char **) The array to free.
 * 
 * @return void
 */
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

/**
 * @brief Frees texture paths and map data in the game data structure.
 *
 * @param data (t_data *) Pointer to the data structure.
 * 
 * @return void
 */
static void	free_data(t_data *data)
{
	ft_free((void **)&data->texture.ea_path);
	ft_free((void **)&data->texture.we_path);
	ft_free((void **)&data->texture.no_path);
	ft_free((void **)&data->texture.so_path);
	free_tab(data->map.matrix);
}
