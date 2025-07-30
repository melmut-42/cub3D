#include "game.h"

// * Checks if the file name has a valid ".cub" extension
bool has_valid_cub_extension(const char *filename)
{
	const char *extension;
	const char *basename;

	if (!filename)
		return (false);

	// Find the last occurrence of '.' in the filename
	extension = ft_strrchr(filename, '.');
	if (!extension)
		return (false);

	// Check if the extension matches ".cub"
	if (ft_strcmp(extension, MAP_FILE_EXTENSION) != 0)
		return (false);

	// Find the last '/' to isolate basename
	basename = ft_strrchr(filename, '/');
	if (basename)
		basename++; // Move past the '/'
	else
		basename = filename;

	if (basename == extension)
		return (false);

	return (true);
}
