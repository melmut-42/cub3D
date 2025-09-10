#include "game.h"

static bool	load_texture(t_game *game, t_texture *tex,
				const char *path, t_dir dir);
static bool	load_door_frame(t_game *game, t_texture *tex,
				const char *path, size_t idx);
static bool	load_door_textures(t_game *game);
static void	init_door_paths(t_texture *tex);

/**
 * @brief Loads all required game textures.
 *
 * @details
 * - Loads wall textures for each direction (N, S, E, W).
 * - Loads door animation frames.
 * - Uses MLX XPM loader to create images from file paths.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if all textures are successfully loaded, false otherwise.
 */
bool	load_game_textures(t_game *game)
{
	if (!load_texture(game, &game->data.texture,
			game->data.texture.no_path, NORTH))
		return (false);
	if (!load_texture(game, &game->data.texture,
			game->data.texture.so_path, SOUTH))
		return (false);
	if (!load_texture(game, &game->data.texture,
			game->data.texture.ea_path, EAST))
		return (false);
	if (!load_texture(game, &game->data.texture,
			game->data.texture.we_path, WEST))
		return (false);
	if (!load_door_textures(game))
		return (false);
	return (true);
}

/**
 * @brief Loads a single wall texture.
 *
 * @details
 * - Loads XPM file into MLX image.
 * - Retrieves pixel data pointer and image metadata.
 * - Stores image in the texture array by direction index.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param tex (t_texture *): Pointer to the texture structure.
 * @param path (const char *): Path to the XPM texture file.
 * @param dir (t_dir): Direction enum (NORTH, SOUTH, EAST, WEST).
 *
 * @return (bool): true if the texture is successfully loaded, false otherwise.
 */
static bool	load_texture(t_game *game, t_texture *tex,
		const char *path, t_dir dir)
{
	t_img	*img;

	img = &tex->textures[dir];
	img->img_ptr = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			(char *)path, &img->width, &img->height);
	if (!img->img_ptr)
	{
		display_error_message(ERR_MLX, true);
		return (false);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	return (true);
}

/**
 * @brief Loads all door animation frames.
 *
 * @details
 * - Initializes paths for each door frame.
 * - Iterates through NUM_DOOR_FRAMES and loads them sequentially.
 * - Displays an error if any frame fails to load.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if all door frames are successfully loaded, false otherwise.
 */
static bool	load_door_textures(t_game *game)
{
	size_t		i;
	t_texture	*tex;

	tex = &game->data.texture;
	i = 0;
	init_door_paths(tex);
	while (i < NUM_DOOR_FRAMES)
	{
		if (!tex->door_paths[i]
			|| !load_door_frame(game, tex, tex->door_paths[i], i))
		{
			display_error_message(ERR_MLX, true);
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Loads a single door animation frame.
 *
 * @details
 * - Loads XPM file into MLX image.
 * - Retrieves pixel data pointer and image metadata.
 * - Stores the frame in the doors array at given index.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param tex (t_texture *): Pointer to the texture structure.
 * @param path (const char *): Path to the XPM door frame file.
 * @param idx (size_t): Index in the door frames array.
 *
 * @return (bool): true if the frame is successfully loaded, false otherwise.
 */
static bool	load_door_frame(t_game *game, t_texture *tex,
		const char *path, size_t idx)
{
	t_img	*img;

	img = &tex->doors[idx];
	img->img_ptr = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			(char *)path, &img->width, &img->height);
	if (!img->img_ptr)
		return (false);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	return (true);
}

/**
 * @brief Initializes door texture paths.
 *
 * @details
 * - Assigns predefined macros (DOOR_FRAME_0 ... DOOR_FRAME_4)
 *   to the door_paths array.
 *
 * @param tex (t_texture *): Pointer to the texture structure.
 * 
 * @return void
 */
static void	init_door_paths(t_texture *tex)
{
	tex->door_paths[0] = DOOR_FRAME_0;
	tex->door_paths[1] = DOOR_FRAME_1;
	tex->door_paths[2] = DOOR_FRAME_2;
	tex->door_paths[3] = DOOR_FRAME_3;
	tex->door_paths[4] = DOOR_FRAME_4;
}
