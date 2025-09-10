#include "game.h"

static void	data_ctor(t_data *data);
static void	player_ctor(t_player *player);

/**
 * @brief Initializes the game structure and all subsystems.
 *
 * @details
 * - Allocates memory for the main game structure.
 * - Sets map path and default values.
 * - Initializes data (textures, RGB, etc.).
 * - Initializes player with default state.
 * - Sequentially initializes all subsystems:
 *   - Map data
 *   - Player position
 *   - Map validation
 *   - Doors
 *   - MLX window
 *   - Frame buffer
 *   - Textures
 *   - Weapon
 * - If any step fails, frees all resources and returns NULL.
 *
 * @param map_path (char *): Path to the map file (.cub).
 *
 * @return (t_game *): Pointer to allocated game structure, or NULL on failure.
 */
t_game	*init_game(char *map_path)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		display_error_message(ERR_GAME, true);
		return (NULL);
	}
	game->data.map.map_path = map_path;
	data_ctor(&game->data);
	player_ctor(&game->player);
	game->name = WIN_TITLE;
	if (!init_data(game) || !init_player(game)
		|| !check_map(game) || !init_doors(game)
		|| !init_mlx(game, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE)
		|| !init_frame_image(game) || !load_game_textures(game)
		|| !init_weapon(game))
	{
		free_game(game);
		return (NULL);
	}
	return (game);
}

/**
 * @brief Initializes default values for data structure.
 *
 * @details
 * - Sets ceiling and floor RGB values to -1 (uninitialized).
 *
 * @param data (t_data *): Pointer to the data structure.
 * 
 * @return void
 */
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
	player->mov_speed = INITIAL_SPEED;
	player->sens.x = SENS_X;
	player->sens.y = SENS_Y;
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	player->vertical.in_air = false;
	player->vertical.in_crouch = false;
	player->vertical.jump_off = 0.0;
	player->vertical.crouch_off = 0.0;
	player->vertical.vertical_pos = 0.0;
	player->vertical.vertical_vel = 0.0;
}
