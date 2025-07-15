#include "game.h"

static bool	skip_map_line(t_game *game, int fd);
static bool	matrix_realloc(t_game *game, t_map *map, char *line);
static bool	process_map_matrix(t_game *game, t_map *map, int fd, char *line);

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
	if (!map->matrix)
	{
		display_error_message(EMPTY_MAP_ERR, false);
		game->error_flag = true;
		return (false);
	}
	return (true);
}

static void	ft_rtrim(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (is_space(line[i]))
	{
		line[i] = '\0';
		i--;
	}
}

static bool	process_map_matrix(t_game *game, t_map *map, int fd, char *line)
{
	char	*trimmed;

	while (line)
	{
		if (does_fully_include_spaces(line))
		{
			free(line);
			return (skip_map_line(game, fd));
		}
		ft_rtrim(line);
		trimmed = ft_strdup(line);
		free(line);
		if (!trimmed)
		{
			display_error_message(GAME_ERR, true);
			game->error_flag = true;
			return (false);
		}
		if (!matrix_realloc(game, map, trimmed))
			return (false);
		if (game->error_flag)
			return (false);
		line = get_next_line(fd);
	}
	return (true);
}

static bool	matrix_realloc(t_game *game, t_map *map, char *line)
{
	char	**new_matrix;
	size_t	i;

	map->height++;
	new_matrix = ft_calloc(map->height + 1, sizeof(char *));
	if (!new_matrix)
	{
		free(line);
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
	new_matrix[i++] = line;
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
