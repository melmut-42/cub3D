#include "game.h"

static bool	skip_map_line(t_game *game, int fd);
static bool	matrix_realloc(t_game *game, t_map *map, char *line);
static bool	process_map_matrix(t_game *game, t_map *map, int fd, char *line);

/**
 * @brief Processes map data from the .cub file.
 *
 * @details
 * - Reads lines from the file descriptor.
 * - Ignores fully-space lines before the map begins.
 * - Passes non-empty lines to process_map_matrix().
 * - Validates that at least one map line was parsed.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param map (t_map *): Pointer to the map structure.
 * @param fd (int): File descriptor of the .cub file.
 *
 * @return (bool): true if map data is successfully processed, false otherwise.
 */
bool	process_map_data(t_game *game, t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_fully_space(line))
			free(line);
		else if (!process_map_matrix(game, map, fd, line))
			return (false);
		line = get_next_line(fd);
	}
	if (!map->matrix)
	{
		display_error_message(ERR_EMPTY, false);
		game->error_flag = true;
		return (false);
	}
	return (true);
}

/**
 * @brief Removes trailing whitespace characters from a line.
 *
 * @param line (char *): String to trim (modified in place).
 * 
 * @return void
 */
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

/**
 * @brief Processes consecutive map lines and stores them into the matrix.
 *
 * @details
 * - Reads lines until encountering a blank line or EOF.
 * - Trims trailing spaces from each line.
 * - Duplicates and stores each line into the map matrix.
 * - If a blank line is followed by more content, skip_map_line()
 *   raises an error (map must be contiguous).
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param map (t_map *): Pointer to the map structure.
 * @param fd (int): File descriptor for the .cub file.
 * @param line (char *): First line to process (already read).
 *
 * @return (bool): true if map matrix is successfully processed, false otherwise.
 */
static bool	process_map_matrix(t_game *game, t_map *map, int fd, char *line)
{
	char	*trimmed;

	while (line)
	{
		if (is_fully_space(line))
		{
			free(line);
			return (skip_map_line(game, fd));
		}
		ft_rtrim(line);
		trimmed = ft_strdup(line);
		free(line);
		if (!trimmed)
		{
			display_error_message(ERR_GAME, true);
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

/**
 * @brief Dynamically reallocates the map matrix to add a new line.
 *
 * @details
 * - Increases map->height by one.
 * - Updates map->width if the new line is longer.
 * - Allocates a new matrix with extra space.
 * - Copies old lines into the new matrix and appends the new line.
 * - Frees the old matrix pointer.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param map (t_map *): Pointer to the map structure.
 * @param line (char *): New map line to append.
 *
 * @return (bool): true if successful, false otherwise.
 */
static bool	matrix_realloc(t_game *game, t_map *map, char *line)
{
	char	**new_matrix;
	size_t	i;

	map->height++;
	if (ft_strlen(line) > map->width)
		map->width = ft_strlen(line);
	new_matrix = ft_calloc(map->height + 1, sizeof(char *));
	if (!new_matrix)
	{
		free(line);
		game->error_flag = true;
		display_error_message(ERR_GAME, true);
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

/**
 * @brief Skips remaining lines after a blank line in the map section.
 *
 * @details
 * - Reads lines until EOF.
 * - If any non-space line appears after a blank line, it's an error
 *   (map must be contiguous).
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param fd (int): File descriptor for the .cub file.
 *
 * @return (bool): true if only blank lines are found, false if invalid data is detected.
 */
static bool	skip_map_line(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!is_fully_space(line))
		{
			free(line);
			game->error_flag = true;
			display_error_message(ERR_DATA, false);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}
