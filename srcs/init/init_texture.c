#include "game.h"

static bool	process_texture_line(t_game *game, t_texture *texture, char *line);
static int	get_start_index(char *line);

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
		if (!process_texture_line(game, &game->data.texture, trimmed))
		{
			free(trimmed);
			return (false);
		}
		free(trimmed);
		line = get_next_line(fd);
	}
	return (true);
}

static bool	process_texture_line(t_game *game, t_texture *texture, char *line)
{
	int	i;

	if (ft_strncmp(line, NORTH_ABB, ft_strlen(line)))
		texture->no_path = get_dir_path(line);
	else if (ft_strncmp(line, SOUTH_ABB, ft_strlen(line)))
		texture->so_path = get_dir_path(line);
	else if (ft_strncmp(line, SOUTH_ABB, ft_strlen(line)))
		texture->ea_path = get_dir_path(line);
	else if (ft_strncmp(line, SOUTH_ABB, ft_strlen(line)))
		texture->we_path = get_dir_path(line);
}

static char	*get_dir_path(char *line)
{
	int	i;

	i = get_start_index(line);
	return (ft_substr(line, line + i, ft_strlen(line + i)));
}

static int	get_start_index(char *line)
{
	int	i;

	i = 2;
	while(is_space(line[i]))
	{
		i++;
	}
	if (line[i] == '\0')
		return (-1);
	return (i);
}
