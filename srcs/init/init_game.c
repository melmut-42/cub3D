#include "game.h"

static void	data_ctor(t_data *data);

t_game *init_game(char *map_path)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		display_error_message(GAME_ERR, true);
		return (NULL);
	}
	game->data.map.map_path = map_path;
	data_ctor(&game->data);
	if (!init_data(game))
	{
		free_game(game);
		return (NULL);
	}
	return (game);
}

static void	data_ctor(t_data *data)
{
	int	i;

	i = 0;
	while (i < RGB_CONSTANT)
	{
		data->texture.ceil_rgb[i] = -1;
		data->texture.floor_rgb[i] = -1;
		i++;
	}
}