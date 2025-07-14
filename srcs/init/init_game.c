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

	if (!init_data(game) || !init_player(game) || !check_map(game))
	{
		free_game(game);
		return (NULL);
	}
  player_ctor(&game->player); // TODO: Combine with the init_player function (for struct unity)
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
	player->x = 0.0f;
	player->y = 0.0f;
	player->direction = 0.0f;
	// Already set to 0 by calloc
	// player->mov_up = 0;
	// player->mov_down = 0;
	// player->mov_left = 0;
	// player->mov_right = 0;
	// player->rot_left = 0;
	// player->rot_right = 0;
	// player->mouse_x = 0;
	// player->mouse_y = 0;
}
