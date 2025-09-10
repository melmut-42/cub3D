#include "game.h"

/**
 * @brief Checks if the given filename has a valid .cub extension.
 *
 * @details
 * - Verifies that the filename is not NULL.
 * - Locates the last '.' in the filename and ensures it matches
 *   the expected MAP_FILE_EXTENSION (".cub").
 * - Ensures that the filename part before the extension is not empty
 *   (e.g., prevents ".cub" or "/.cub").
 *
 * @param filename (char*): The file path or name to validate.
 *
 * @return (bool): true if the filename has a valid .cub extension, false otherwise.
 */
bool	has_valid_cub_extension(const char *filename)
{
	const char	*extension;
	const char	*basename;

	if (!filename)
		return (false);
	extension = ft_strrchr(filename, '.');
	if (!extension)
		return (false);
	if (ft_strcmp(extension, MAP_FILE_EXTENSION) != 0)
		return (false);
	basename = ft_strrchr(filename, '/');
	if (basename)
		basename++;
	else
		basename = filename;
	if (basename == extension)
		return (false);
	return (true);
}
