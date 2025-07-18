#include "game.h"

static void	setup_trigonometry_table(t_data *data);
static bool	process_file_data(t_game *game, const char *path);

bool	init_data(t_game *game)
{
	if (!process_file_data(game, game->data.map.map_path))
		return (false);
	setup_trigonometry_table(&game->data);
	return (true);
}

static void	setup_trigonometry_table(t_data *data)
{
	int		i;
	double	radians;

	i = 0;
	while (i < NUM_OF_DEGREE)
	{
		radians = (i * M_PI) / 180.0;
		data->cos_table[i] = cos(radians);
		data->sin_table[i] = sin(radians);
		i++;
	}
}

static bool	process_file_data(t_game *game, const char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		display_error_message(FILE_ERR, true);
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

bool	does_texture_attr_completed(t_texture *texture)
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
