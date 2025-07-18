#include "game.h"

// * Loads a texture from the specified path into the game structure
int	load_texture(t_game *game, t_texture *tex, const char *path, t_directions dir)
{
	// Define the texture paths based on the direction
	tex->textures[dir].img_ptr = mlx_xpm_file_to_image(game->mlx->mlx_ptr, (char *)path,
			&tex->textures[dir].width, &tex->textures[dir].height);

	// Check if the texture was loaded successfully
	if (!tex->textures[dir].img_ptr)
		return (0);

	// Store the path in the corresponding texture path
	tex->textures[dir].addr = mlx_get_data_addr(tex->textures[dir].img_ptr,
			&tex->textures[dir].bpp, &tex->textures[dir].line_len,
			&tex->textures[dir].endian);

	return (1);
}
