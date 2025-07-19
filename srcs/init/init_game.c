#include "game.h"

static void data_ctor(t_data *data);
static void player_ctor(t_player *player);

// * Initializes the game structure and loads the map
t_game *init_game(char *map_path)
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		display_error_message(GAME_ERR, true);
		return (NULL);
	}
	game->data.map.map_path = map_path;
	data_ctor(&game->data);
	player_ctor(&game->player);
	game->name = WIN_TITLE;
	if (!init_data(game) || !init_player(game) ||
		!check_map(game) ||
		!init_mlx(game, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE) ||
		!init_frame_image(game) || !load_game_textures(game))
	{
		free_game(game);
		return (NULL);
	}
	return (game);
}

// * Data constructor to initialize texture RGB values
static void data_ctor(t_data *data)
{
	int i;

	i = 0;
	while (i < RGB_CONSTANT)
	{
		data->texture.ceil_rgb[i] = -1;
		data->texture.floor_rgb[i] = -1;
		i++;
	}
}

// * Player constructor to initialize player position, speed, sensitivity, and camera plane
static void player_ctor(t_player *player)
{
	player->pos.x = NPOS;
	player->pos.y = NPOS;
	player->mov_speed = 0.05;
	player->sens.x = 0.3;
	player->sens.y = 0.5;
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	player->vertical.in_air = false;
	player->vertical.vertical_pos = 0.0;
	player->vertical.vertical_vel = 0.0;
}
