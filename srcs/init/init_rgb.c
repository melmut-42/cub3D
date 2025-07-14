#include "game.h"

static bool	are_rgb_valid(t_game *game, char **rgb);
static char	**get_splitted_rgb(t_game *game, char *data);
static bool	has_rgb_already_processed(t_game *game, int rgb[RGB_CONSTANT]);

void	process_rgb(t_game *game, int rgb[RGB_CONSTANT], char *data)
{
	char	**splitted_rgb;
	int		i;

	if (game->error_flag)
		return ;
	if (has_rgb_already_processed(game, rgb))
		return ;
	splitted_rgb = get_splitted_rgb(game, data);
	if (!splitted_rgb)
		return ;
	if (!are_rgb_valid(game, splitted_rgb))
	{
		free_tab(splitted_rgb);
		return ;
	}
	i = 0;
	while (i < RGB_CONSTANT)
	{
		rgb[i] = ft_atoi(splitted_rgb[i]);
		i++;
	}
	free_tab(splitted_rgb);
}

static bool	has_rgb_already_processed(t_game *game, int rgb[RGB_CONSTANT])
{
	int	i;

	i = 0;
	while (i < RGB_CONSTANT)
	{
		if (rgb[i] == -1)
			return (false);
		i++;
	}
	display_error_message(DUP_DATA, false);
	game->error_flag = true;
	return (true);
}

static bool	are_rgb_valid(t_game *game, char **rgb)
{
	int		i;

	i = -1;
	while (++i < RGB_CONSTANT)
	{
		rgb[i] = ultimate_trim(game, rgb[i], SPACE_SET);
		if (!rgb[i])
			return (false);
		if (!is_number(rgb[i]) || ft_atoi(rgb[i]) < RGB_MIN_VAL || ft_atoi(rgb[i]) > RGB_MAX_VAL)
		{
			game->error_flag = true;
			display_error_message(INV_RGB_VAL, false);
			return (false);
		}
	}
	if (rgb[i])
	{
		game->error_flag = true;
		return (false);
	}
	return (true);
}

static char	**get_splitted_rgb(t_game *game, char *data)
{
	char	**splitted;

	if (data[ft_strlen(data) - 1] == COMMA)
	{
		free(data);
		display_error_message(INV_RGB_VAL, false);
		game->error_flag = true;
		return (NULL);
	}
	splitted = ft_split(data, COMMA);
	free(data);
	if (!splitted)
	{
		display_error_message(GAME_ERR, true);
		game->error_flag = true;
		return (NULL);
	}
	return (splitted);
}
