#include "game.h"

static void	setup_trig_table(t_data *data);
static bool	process_file_data(t_game *game, const char *path);

// * Initializes the game data structure and sets up the trigonometry tables
bool	init_data(t_game *game)
{
	if (!process_file_data(game, game->data.map.map_path))
		return (false);

	setup_trig_table(&game->data);
	return (true);
}

// * Initializes the trigonometry tables for fast sine and cosine calculations
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

// * Processes the texture data and map data from the file
static bool	process_file_data(t_game *game, const char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("it works\n");
		display_error_message(ERR_FILE, true);
		return (false);
	}

	// Initialize texture and map data
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

// * Processes the texture data from the file
bool	is_texture_valid(t_texture *texture)
{
	int	i;

	i = 0;
	while (i < RGB_CONSTANT) // Check if all RGB values are set
	{
		if (texture->ceil_rgb[i] == -1 || texture->floor_rgb[i] == -1)
			return (false);
		i++;
	}

	// Check if all texture paths are set
	if (texture->ea_path == NULL || texture->we_path == NULL
			|| texture->no_path == NULL || texture->so_path == NULL)
	{
		return (false);
	}
	return (true);
}
