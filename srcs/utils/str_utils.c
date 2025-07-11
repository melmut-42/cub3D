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
