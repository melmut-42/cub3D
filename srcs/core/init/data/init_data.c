#include "game.h"

static void	setup_trig_table(t_data *data);
static bool	process_file_data(t_game *game, const char *path);

/**
 * @brief Initializes game data (map, textures, trig tables).
 *
 * @details
 * - Reads map and texture data from the file specified in game->data.map.map_path.
 * - Sets up sine and cosine lookup tables for faster math operations.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if initialization succeeded, false otherwise.
 */
bool	init_data(t_game *game)
{
	if (!process_file_data(game, game->data.map.map_path))
		return (false);
	setup_trig_table(&game->data);
	return (true);
}

/**
 * @brief Precomputes sine and cosine values for all degrees.
 *
 * @details
 * - Converts each degree (0 .. NUM_OF_DEGREE - 1) to radians.
 * - Stores cos and sin values in lookup tables.
 * - Optimizes raycasting and rotations by avoiding repeated trig calls.
 *
 * @param data (t_data *): Pointer to the data structure where trig tables are stored.
 * 
 * @return void
 */
static void	setup_trig_table(t_data *data)
{
	int		i;
	double	radians;

	i = 0;
	while (i < NUM_OF_DEGREE)
	{
		radians = deg_to_rad(i);
		data->cos_table[i] = cos(radians);
		data->sin_table[i] = sin(radians);
		i++;
	}
}

/**
 * @brief Processes texture and map data from the input file.
 *
 * @details
 * - Opens the .cub file in read-only mode.
 * - Extracts texture paths and RGB data using process_texture_data().
 * - Extracts map matrix data using process_map_data().
 * - Handles errors by clearing the GNL buffer and closing the file.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param path (const char *): Path to the .cub file.
 *
 * @return (bool): true if file data processed successfully, false otherwise.
 */
static bool	process_file_data(t_game *game, const char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		display_error_message(ERR_FILE, true);
		return (false);
	}
	if (!process_texture_data(game, &game->data.texture, fd)
		|| !process_map_data(game, &game->data.map, fd))
	{
		clear_get_next_line(fd);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

/**
 * @brief Validates texture data.
 *
 * @details
 * - Ensures ceiling and floor RGB values are properly initialized.
 * - Ensures all required wall texture paths (EA, WE, NO, SO) are loaded.
 *
 * @param texture (t_texture *): Pointer to the texture structure.
 *
 * @return (bool): true if textures are valid, false otherwise.
 */
bool	is_texture_valid(t_texture *texture)
{
	int	i;

	i = 0;
	while (i < RGB_CONSTANT)
	{
		if (texture->ceil_rgb[i] == -1 || texture->floor_rgb[i] == -1)
			return (false);
		i++;
	}
	if (texture->ea_path == NULL || texture->we_path == NULL
		|| texture->no_path == NULL || texture->so_path == NULL)
	{
		return (false);
	}
	return (true);
}
