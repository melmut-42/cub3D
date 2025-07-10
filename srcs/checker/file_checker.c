#include "../../includes/game.h"

// * Checks whether provided argument is valid or not
bool has_valid_cub_extension(const char *filename)
{
	const char *ext;
	const char *basename;

	if (!filename)
		return (false);
	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (false);
	if (ft_strcmp(ext, MAP_FILE_EXTENSION) != 0)
		return (false);
	basename = ft_strrchr(filename, '/');
	if (basename)
		basename = basename + 1;
	else
		basename = filename;
	if (basename == ext)
		return (false);
	return (true);
}
