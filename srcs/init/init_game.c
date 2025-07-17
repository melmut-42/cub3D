#include "game.h"

static void	data_ctor(t_data *data);
static void player_ctor(t_player *player);

// * Initializes the game structure and loads the map
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
	game->name = WIN_TITLE;
	if (!init_data(game) || !init_player(game) || !check_map(game))
	{
		free_game(game);
		return (NULL);
	}
	return (game);
}

// * Data constructor to initialize texture RGB values
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

// * Player constructor to initialize player position, speed, sensitivity, and camera plane
static void	player_ctor(t_player *player)
{
	player->pos.x = NPOS;
	player->pos.y = NPOS;
	player->mov_speed = 0.5;
	player->sens.x = 0.1;
	player->sens.y = 0.1;
	player->plane.x = 0;
	player->plane.y = 0.66;
}

// * Loads the texture images after MLX initialization
int	load_game_textures(t_game *game)
{
	// waits t_texture, not char*
	if (!load_texture(game, &game->data.texture, game->data.texture.no_path, NORTH))
		return (0);
	if (!load_texture(game, &game->data.texture, game->data.texture.so_path, SOUTH))
		return (0);
	if (!load_texture(game, &game->data.texture, game->data.texture.ea_path, EAST))
		return (0);
	if (!load_texture(game, &game->data.texture, game->data.texture.we_path, WEST))
		return (0);

	return (1);
}
