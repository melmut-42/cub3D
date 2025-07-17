#include "game.h"

static void	data_ctor(t_data *data);
static void player_ctor(t_player *player);

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
	player_ctor(&game->player);
	if (!init_data(game) || !init_player(game) || !check_map(game))
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

static void	player_ctor(t_player *player)
{
	player->pos.x = NPOS;
	player->pos.y = NPOS;
	player->mov_speed = 0.5;
	player->sens.x = 0.1;
	player->sens.y = 0.1;
}
