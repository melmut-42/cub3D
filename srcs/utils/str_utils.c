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
	bool	result;

	i = 0;
	space_set = SPACE_SET;
	result = false;
	while (space_set[i])
	{
		if (c == space_set[i])
			result = true;
		i++;
	}
	return (result);
}

void	free_tab(char **state)
{
	int	i;

	if (!state)
		return ;
	i = 0;
	while (state[i])
	{
		free(state[i]);
		i++;
	}
	free(state);
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
