#include "game.h"

static bool	validate_rgb(t_game *game, char **rgb);
static char	**get_rgb_segments(t_game *game, char *data);
static bool	check_missing_rgb(t_game *game, char **segment);
static bool	rgb_already_set(t_game *game, int rgb[RGB_CONSTANT]);

void	process_rgb(t_game *game, int rgb[RGB_CONSTANT], char *data)
{
	char	**rgb_segments;
	int		i;

	if (game->error_flag || rgb_already_set(game, rgb))
	{
		free(data);
		return ;
	}
	rgb_segments = get_rgb_segments(game, data);
	if (!rgb_segments)
		return ;
	if (!validate_rgb(game, rgb_segments))
	{
		free_tab(rgb_segments);
		return ;
	}
	i = 0;
	while (i < RGB_CONSTANT)
	{
		rgb[i] = ft_atoi(rgb_segments[i]);
		i++;
	}
	free_tab(rgb_segments);
}

static bool	rgb_already_set(t_game *game, int rgb[RGB_CONSTANT])
{
	int	i;

	i = 0;
	while (i < RGB_CONSTANT)
	{
		if (rgb[i] == -1)
			return (false);
		i++;
	}
	display_error_message(ERR_DUP, false);
	game->error_flag = true;
	return (true);
}

static bool	validate_rgb(t_game *game, char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i] && i < RGB_CONSTANT)
	{
		rgb[i] = ultimate_trim(game, rgb[i], SPACE_SET);
		if (!rgb[i])
			return (false);
		if (ft_strlen(rgb[i]) >= 4 || !is_number(rgb[i])
			|| ft_atoi(rgb[i]) < RGB_MIN_VAL || ft_atoi(rgb[i]) > RGB_MAX_VAL)
		{
			game->error_flag = true;
			display_error_message(ERR_RGB, false);
			return (false);
		}
		i++;
	}
	if (i != RGB_CONSTANT || rgb[i])
	{
		game->error_flag = true;
		return (false);
	}
	return (true);
}

static char	**get_rgb_segments(t_game *game, char *data)
{
	char	**segments;

	if (data[ft_strlen(data) - 1] == COMMA)
	{
		free(data);
		display_error_message(ERR_RGB, false);
		game->error_flag = true;
		return (NULL);
	}
	segments = ft_split(data, COMMA);
	free(data);
	if (!segments)
	{
		display_error_message(ERR_GAME, true);
		game->error_flag = true;
		return (NULL);
	}
	if (!check_missing_rgb(game, segments))
	{	
		free_tab(segments);
		segments = NULL;
		return (false);
	}
	return (segments);
}

static bool	check_missing_rgb(t_game *game, char **segment)
{
	int	rgb_count;

	rgb_count = 0;
	while (segment[rgb_count])
		rgb_count++;
	if (rgb_count != RGB_CONSTANT)
	{
		display_error_message(ERR_RGB_COUNT, false);
		game->error_flag = true;
		return (false);
	}
	return (true);
}
