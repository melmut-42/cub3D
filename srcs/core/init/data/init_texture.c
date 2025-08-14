#include "game.h"

static int	get_start_index(char *line);
static char	*get_dir_path(t_game *game, char *line);
static bool	process_texture_attr(t_game *game, t_texture *texture, char *line);
static void	process_path(t_game *game, t_texture *tex, t_dir dir, char *path);

bool	process_texture_data(t_game *game, t_texture *texture, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ultimate_trim(game, line, SPACE_SET);
		if (!trimmed)
			return (false);
		if (trimmed[0] == '\0')
			free(trimmed);
		else if (!process_texture_attr(game, texture, trimmed))
			return (false);
		if (is_texture_valid(&game->data.texture))
			return (true);
		line = get_next_line(fd);
	}
	if (!is_texture_valid(&game->data.texture))
	{
		display_error_message(ERR_TEX, false);
		return (false);
	}
	return (true);
}

static bool	process_texture_attr(t_game *game, t_texture *texture, char *line)
{
	char	*data;

	data = get_dir_path(game, line);
	if (!data)
	{
		free(line);
		return (false);
	}
	if (ft_strncmp(line, NORTH_ABB, ft_strlen(NORTH_ABB)) == 0)
		process_path(game, &game->data.texture, NORTH, data);
	else if (ft_strncmp(line, SOUTH_ABB, ft_strlen(SOUTH_ABB)) == 0)
		process_path(game, &game->data.texture, SOUTH, data);
	else if (ft_strncmp(line, EAST_ABB, ft_strlen(EAST_ABB)) == 0)
		process_path(game, &game->data.texture, EAST, data);
	else if (ft_strncmp(line, WEST_ABB, ft_strlen(WEST_ABB)) == 0)
		process_path(game, &game->data.texture, WEST, data);
	else if (ft_strncmp(line, FLOOR_ABB, ft_strlen(FLOOR_ABB)) == 0)
		process_rgb(game, texture->floor_rgb, data);
	else if (ft_strncmp(line, CEILING_ABB, ft_strlen(CEILING_ABB)) == 0)
		process_rgb(game, texture->ceil_rgb, data);
	free(line);
	if (game->error_flag)
		return (false);
	return (true);
}

static void	process_path(t_game *game, t_texture *tex, t_dir dir, char *path)
{
	char	**targets[NUMBER_DIR];
	char	**slot;

	if (dir < NORTH || dir > EAST)
		return ;
	targets[NORTH] = &tex->no_path;
	targets[SOUTH] = &tex->so_path;
	targets[WEST] = &tex->we_path;
	targets[EAST] = &tex->ea_path;
	slot = targets[dir];
	if (*slot)
	{
		free(path);
		game->error_flag = true;
		display_error_message(ERR_DUP, false);
		return ;
	}
	*slot = path;
}

static char	*get_dir_path(t_game *game, char *line)
{
	int		i;
	char	*path;

	i = get_start_index(line);
	if (i == NPOS)
	{
		display_error_message(ERR_DATA, false);
		game->error_flag = true;
		return (NULL);
	}
	path = ft_substr(line, i, ft_strlen(line + i));
	if (!path)
	{
		display_error_message(ERR_GAME, true);
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
	if (!is_space(line[i]))
		return (NPOS);
	while (is_space(line[i]))
		i++;
	if (line[i] == '\0')
		return (NPOS);
	return (i);
}
