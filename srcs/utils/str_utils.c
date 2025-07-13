#include "game.h"

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

bool	is_number(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_space(char c)
{
	int		i;
	char	*space_set;

	i = 0;
	space_set = SPACE_SET;
	while (space_set[i])
	{
		if (c == space_set[i])
			return (true);
		i++;
	}
	return (false);
}

bool	does_fully_include_spaces(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while(str[i])
	{
		if (!is_space(str[i]))
			return (false);
		i++;
	}
	return (true);
}

char	*ultimate_trim(t_game *game, char *raw, char *trim_set)
{
	char	*trimmed;

	trimmed = ft_strtrim(raw, trim_set);
	free(raw);
	if (!trimmed)
	{
		game->error_flag = false;
		display_error_message(GAME_ERR, true);
		return (NULL);
	}
	return (trimmed);
}
