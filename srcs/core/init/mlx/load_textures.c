#include "game.h"

static bool	load_texture(t_game *game, t_texture *tex, const char *path, t_dir dir);

// * Loads the texture images after MLX initialization
bool	load_game_textures(t_game *game)
{
	// waits t_texture, not char*
	if (!load_texture(game, &game->data.texture, game->data.texture.no_path, NORTH))
		return (false);

	if (!load_texture(game, &game->data.texture, game->data.texture.so_path, SOUTH))
		return (false);

	if (!load_texture(game, &game->data.texture, game->data.texture.ea_path, EAST))
		return (false);

	if (!load_texture(game, &game->data.texture, game->data.texture.we_path, WEST))
		return (false);

	return (true);
}

// * Loads a texture from the specified path into the game structure
static bool	load_texture(t_game *game, t_texture *tex, const char *path, t_dir dir)
{
	// Define the texture paths based on the direction
	tex->textures[dir].img_ptr = mlx_xpm_file_to_image(game->mlx->mlx_ptr, (char *)path,
			&tex->textures[dir].width, &tex->textures[dir].height);

	// Check if the texture was loaded successfully
	if (!tex->textures[dir].img_ptr)
	{
		display_error_message(ERR_MLX, true);
		return (false);
	}

	// Store the path in the corresponding texture path
	tex->textures[dir].addr = mlx_get_data_addr(tex->textures[dir].img_ptr,
			&tex->textures[dir].bpp, &tex->textures[dir].line_len,
			&tex->textures[dir].endian);

	return (true);
}
