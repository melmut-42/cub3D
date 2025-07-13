#include "game.h"

static bool	skip_map_line(t_game *game, int fd);
static bool	matrix_realloc(t_game *game, t_map *map, char *data);
static bool	process_map_matrix(t_game *game, t_map *map, int fd, char *data);

bool	process_map_data(t_game *game, t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (does_fully_include_spaces(line))
			free(line);
		else if (!process_map_matrix(game, map, fd, line))
			return (false);
		line = get_next_line(fd);
	}
	return (true);
}

static bool	process_map_matrix(t_game *game, t_map *map, int fd, char *data)
{
	char	*trimmed;

	while (data)
	{
		if (does_fully_include_spaces(data))
		{
			free(data);
			return (skip_map_line(game, fd));
		}
		trimmed = ultimate_trim(game, data, NEWLINE);
		if (!trimmed)
			return (false);
		if (!matrix_realloc(game, map, trimmed))
			return (false);
		if (game->error_flag)
			return (false);
		data = get_next_line(fd);
	}
	return (true);
}

static bool	matrix_realloc(t_game *game, t_map *map, char *data)
{
	char	**new_matrix;
	size_t	i;

	map->height++;
	new_matrix = ft_calloc(map->height + 1, sizeof(char *));
	if (!new_matrix)
	{
		game->error_flag = true;
		display_error_message(GAME_ERR, true);
		return (false);
	}
	i = 0;
	while (i < map->height - 1)
	{
		new_matrix[i] = map->matrix[i];
		i++;
	}
	new_matrix[i++] = data;
	new_matrix[i] = NULL;
	free(map->matrix);
	map->matrix = new_matrix;
	return (true);
}

static bool	skip_map_line(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!does_fully_include_spaces(line))
		{
			free(line);
			game->error_flag = true;
			display_error_message(INV_DATA, false);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}
