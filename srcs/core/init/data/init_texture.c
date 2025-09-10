#include "game.h"

static int	get_start_index(char *line);
static char	*get_dir_path(t_game *game, char *line);
static bool	process_texture_attr(t_game *game, t_texture *texture, char *line);
static void	process_path(t_game *game, t_texture *tex, t_dir dir, char *path);

/**
 * @brief Processes texture and color data from the .cub file.
 *
 * @details
 * - Reads each line and trims spaces.
 * - Ignores empty lines.
 * - Passes lines to process_texture_attr() for handling.
 * - Stops early if all textures and colors are already valid.
 * - Ensures all required attributes are present before returning.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param texture (t_texture *): Pointer to the texture structure.
 * @param fd (int): File descriptor of the .cub file.
 *
 * @return (bool): true if textures and colors were processed successfully, false otherwise.
 */
bool	process_texture_data(t_game *game, t_texture *texture, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ultimate_trim(game, line, SPACE_SET);
		if (!trimmed)
			return (false);
		if (trimmed[0] == '\0')
			free(trimmed);
		else if (!process_texture_attr(game, texture, trimmed))
			return (false);
		if (is_texture_valid(&game->data.texture))
			return (true);
		line = get_next_line(fd);
	}
	if (!is_texture_valid(&game->data.texture))
	{
		display_error_message(ERR_TEX, false);
		return (false);
	}
	return (true);
}

/**
 * @brief Processes a single texture or color attribute line.
 *
 * @details
 * - Identifies the type of attribute by its prefix (NO, SO, WE, EA, F, C).
 * - For NO/SO/WE/EA → extracts path and assigns to texture slot.
 * - For F/C → parses RGB values via process_rgb().
 * - Updates color values after successful parsing.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param texture (t_texture *): Pointer to the texture structure.
 * @param line (char *): Trimmed attribute line.
 *
 * @return (bool): true if processed successfully, false otherwise.
 */
static bool	process_texture_attr(t_game *game, t_texture *texture, char *line)
{
	char	*data;

	data = get_dir_path(game, line);
	if (!data)
	{
		free(line);
		return (false);
	}
	if (ft_strncmp(line, NORTH_ABB, ft_strlen(NORTH_ABB)) == 0)
		process_path(game, &game->data.texture, NORTH, data);
	else if (ft_strncmp(line, SOUTH_ABB, ft_strlen(SOUTH_ABB)) == 0)
		process_path(game, &game->data.texture, SOUTH, data);
	else if (ft_strncmp(line, EAST_ABB, ft_strlen(EAST_ABB)) == 0)
		process_path(game, &game->data.texture, EAST, data);
	else if (ft_strncmp(line, WEST_ABB, ft_strlen(WEST_ABB)) == 0)
		process_path(game, &game->data.texture, WEST, data);
	else if (ft_strncmp(line, FLOOR_ABB, ft_strlen(FLOOR_ABB)) == 0)
		process_rgb(game, texture->floor_rgb, data);
	else if (ft_strncmp(line, CEILING_ABB, ft_strlen(CEILING_ABB)) == 0)
		process_rgb(game, texture->ceil_rgb, data);
	free(line);
	if (game->error_flag)
		return (false);
	update_colors(game, texture);
	return (true);
}

/**
 * @brief Assigns a path to the correct texture slot.
 *
 * @details
 * - Validates the direction (N, S, W, E).
 * - Prevents duplicate assignment of texture paths.
 * - Stores the provided path in the appropriate slot.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param tex (t_texture *): Pointer to the texture structure.
 * @param dir (t_dir): Direction enum (NORTH, SOUTH, WEST, EAST).
 * @param path (char *): File path string for the texture.
 * 
 * @return void
 */
static void	process_path(t_game *game, t_texture *tex, t_dir dir, char *path)
{
	char	**targets[NUMBER_DIR];
	char	**slot;

	if (dir < NORTH || dir > EAST)
		return ;
	targets[NORTH] = &tex->no_path;
	targets[SOUTH] = &tex->so_path;
	targets[WEST] = &tex->we_path;
	targets[EAST] = &tex->ea_path;
	slot = targets[dir];
	if (*slot)
	{
		free(path);
		game->error_flag = true;
		display_error_message(ERR_DUP, false);
		return ;
	}
	*slot = path;
}

/**
 * @brief Extracts the path or data substring from a line.
 *
 * @details
 * - Determines the starting index using get_start_index().
 * - Extracts the substring after the identifier and spaces.
 * - Handles allocation errors.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param line (char *): Input line (e.g., "NO ./path/to/tex.xpm").
 *
 * @return (char *): Newly allocated substring with the path, or NULL on error.
 */
static char	*get_dir_path(t_game *game, char *line)
{
	int		i;
	char	*path;

	i = get_start_index(line);
	if (i == NPOS)
	{
		display_error_message(ERR_DATA, false);
		game->error_flag = true;
		return (NULL);
	}
	path = ft_substr(line, i, ft_strlen(line + i));
	if (!path)
	{
		display_error_message(ERR_GAME, true);
		game->error_flag = true;
		return (NULL);
	}
	return (path);
}

/**
 * @brief Gets the index where the path/data begins after the identifier.
 *
 * @details
 * - For NO/SO/WE/EA → skips 2-character identifier.
 * - For F/C → skips 1-character identifier.
 * - Skips any following spaces.
 * - Returns NPOS if no valid data is found.
 *
 * @param line (char *): Input line.
 *
 * @return (int): Index of start of path/data, or NPOS if invalid.
 */
static int	get_start_index(char *line)
{
	int	i;

	if (ft_strncmp(line, NORTH_ABB, ft_strlen(NORTH_ABB)) == 0
		|| ft_strncmp(line, EAST_ABB, ft_strlen(EAST_ABB)) == 0
		|| ft_strncmp(line, WEST_ABB, ft_strlen(WEST_ABB)) == 0
		|| ft_strncmp(line, SOUTH_ABB, ft_strlen(SOUTH_ABB)) == 0)
	{
		i = ft_strlen(EAST_ABB);
	}
	else if (ft_strncmp(line, FLOOR_ABB, ft_strlen(FLOOR_ABB)) == 0
		|| ft_strncmp(line, CEILING_ABB, ft_strlen(CEILING_ABB)) == 0)
	{
		i = ft_strlen(FLOOR_ABB);
	}
	else
		return (NPOS);
	if (!is_space(line[i]))
		return (NPOS);
	while (is_space(line[i]))
		i++;
	if (line[i] == '\0')
		return (NPOS);
	return (i);
}
