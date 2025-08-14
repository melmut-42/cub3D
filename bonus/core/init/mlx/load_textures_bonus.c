#include "game.h"

static bool	load_door_texture(t_game *game, t_texture *tex);
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
	if (!load_door_texture(game, &game->data.texture))
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

static bool	load_door_texture(t_game *game, t_texture *tex)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
	{
		display_error_message(ERR_GAME, true);
		return (false);
	}
	img->img_ptr = mlx_xpm_file_to_image(
			game->mlx->mlx_ptr, "textures/test_pack/door.xpm",
			&img->width, &img->height);
	if (!img->img_ptr)
	{
		free(img);
		display_error_message(ERR_MLX, true);
		return (false);
	}
	img->addr = mlx_get_data_addr(
			img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	tex->door = img;
	return (true);
}
