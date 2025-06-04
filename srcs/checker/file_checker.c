#include "../../includes/game.h"

bool has_valid_cub_extension(const char *filename)
{
	char	*p;

	if (!filename || ft_strlen(filename) <= ft_strlen(MAP_FILE_EXTENSION))
    {
		return (false);
    }
	p = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (p == NULL || ft_strlen(p) != 4)
    {
		return (false);
    }
	return (true);
}
