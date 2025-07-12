#include "game.h"

static char	*get_dir_path(t_game *game, char *line);
static int	get_start_index(char *line);
static bool	process_texture_attr(t_game *game, t_texture *texture, char *line);

bool	process_texture_data(t_game *game, t_texture *texture, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, SPACE_SET);
		free(line);
		if (!trimmed)
		{
			display_error_message(GAME_ERR, true);
			return (false);
		}
		if (trimmed[0] == '\0')
			free(trimmed);
		else if (!process_texture_attr(game, texture, trimmed))
			return (false);
		line = get_next_line(fd);
	}
	return (true);
}

static bool	process_texture_attr(t_game *game, t_texture *texture, char *line)
{
	int		i;
	char	*data;

	data = get_dir_path(game, line);
	if (!data)
	{
		free(line);
		return (false);
	}
	if (ft_strncmp(line, NORTH_ABB, ft_strlen(NORTH_ABB)) == 0)
		texture->no_path = data;
	else if (ft_strncmp(line, SOUTH_ABB, ft_strlen(SOUTH_ABB)) == 0)
		texture->so_path = data;
	else if (ft_strncmp(line, EAST_ABB, ft_strlen(EAST_ABB)) == 0)
		texture->ea_path = data;
	else if (ft_strncmp(line, WEST_ABB, ft_strlen(WEST_ABB)) == 0)
		texture->we_path = data;
	else if (ft_strncmp(line, FLOOR_ABB, ft_strlen(FLOOR_ABB)) == 0)
		process_rgb(game, texture->floor_rgb, data);
	else if (ft_strncmp(line, CEILING_ABB, ft_strlen(CEILING_ABB)) == 0)
		process_rgb(game, texture->ceil_rgb, data);
	free(line);
	if (game->error_flag)
		return (false);
	return (true);
}

static char	*get_dir_path(t_game *game, char *line)
{
	int		i;
	char	*path;

	i = get_start_index(line);
	if (i == NPOS)
	{
		display_error_message(INV_DATA, false);
		game->error_flag = true;
		return (NULL);
	}
	path = ft_substr(line, line + i, ft_strlen(line + i));
	if (!path)
	{
		display_error_message(GAME_ERR, true);
		game->error_flag = true;
		return (NULL);
	}
	return (path);
}

static int	get_start_index(char *line)
{
	int	i;

	if (ft_strncmp(line, NORTH_ABB, ft_strlen(NORTH_ABB)) == 0
		|| ft_strncmp(line, EAST_ABB, ft_strlen(EAST_ABB)) == 0
		|| ft_strncmp(line, WEST_ABB, ft_strlen(WEST_ABB)) == 0
		|| ft_strncmp(line, SOUTH_ABB, ft_strlen(SOUTH_ABB)) == 0)
	{
		i = ft_strlen(EAST_ABB);
	}
	else if (ft_strncmp(line, FLOOR_ABB, ft_strlen(FLOOR_ABB)) == 0
			|| ft_strncmp(line, CEILING_ABB, ft_strlen(CEILING_ABB)) == 0)
	{
		i = ft_strlen(FLOOR_ABB);
	}
	else
		return (NPOS);
	while (is_space(line[i]))
		i++;
	if (line[i] == '\0')
		return (NPOS);
	return (i);
}
