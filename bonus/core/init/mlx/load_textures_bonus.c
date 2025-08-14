#include "game.h"

static bool	load_texture(t_game *game, t_texture *tex, const char *path,
				t_dir dir);

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
	return (true);
}

static bool	load_texture(t_game *game, t_texture *tex, const char *path,
		t_dir dir)
{
	tex->textures[dir].img_ptr = mlx_xpm_file_to_image(game->mlx->mlx_ptr,
			(char *)path, &tex->textures[dir].width,
			&tex->textures[dir].height);
	if (!tex->textures[dir].img_ptr)
	{
		display_error_message(ERR_MLX, true);
		return (false);
	}
	tex->textures[dir].addr = mlx_get_data_addr(tex->textures[dir].img_ptr,
			&tex->textures[dir].bpp, &tex->textures[dir].line_len,
			&tex->textures[dir].endian);
	return (true);
}
