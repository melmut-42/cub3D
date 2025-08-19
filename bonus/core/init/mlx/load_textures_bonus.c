#include "game.h"

static bool	load_texture(t_game *game, t_texture *tex,
				const char *path, t_dir dir);
static bool	load_door_frame(t_game *game, t_texture *tex,
				const char *path, size_t idx);
static bool	load_door_textures(t_game *game);
static void	init_door_paths(t_texture *tex);

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

static bool	load_door_textures(t_game *game)
{
	size_t		i;
	t_texture	*tex;

	tex = &game->data.texture;
	i = 0;
	init_door_paths(tex);
	while (++i < NUM_DOOR_FRAMES)
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

static void	init_door_paths(t_texture *tex)
{
	tex->door_paths[0] = DOOR_FRAME_0;
	tex->door_paths[1] = DOOR_FRAME_1;
	tex->door_paths[2] = DOOR_FRAME_2;
	tex->door_paths[3] = DOOR_FRAME_3;
	tex->door_paths[4] = DOOR_FRAME_4;
}
