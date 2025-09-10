#include "game.h"

static bool	validate_rgb(t_game *game, char **rgb);
static char	**get_rgb_segments(t_game *game, char *data);
static bool	check_missing_rgb(t_game *game, char **segment);
static bool	rgb_already_set(t_game *game, int rgb[RGB_CONSTANT]);

/**
 * @brief Parses and processes RGB values for floor or ceiling.
 *
 * @details
 * - Prevents duplicate definitions (rgb_already_set).
 * - Splits the input string by commas into 3 segments.
 * - Validates each segment (must be numeric, in [0–255]).
 * - Converts strings into integers and stores them in rgb array.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param rgb (int[3]): Target RGB array (3 elements for R, G, B).
 * @param data (char *): Raw input string containing RGB values (e.g., "220,100,0").
 * 
 * @return void
 */
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

/**
 * @brief Checks if an RGB value was already set.
 *
 * @details
 * - Each component is initialized to -1.
 * - If no component is -1, RGB has already been assigned.
 * - Prevents duplicate definitions in the config file.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param rgb (int[3]): Target RGB array.
 *
 * @return (bool): true if already set, false otherwise.
 */
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

/**
 * @brief Validates RGB segments for correctness.
 *
 * @details
 * - Trims whitespace around each segment.
 * - Ensures each value is numeric and length < 4.
 * - Ensures each value is in range [0, 255].
 * - Verifies there are exactly 3 values.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param rgb (int[3]): Target RGB array (3 elements for R, G, B).
 *
 * @return (bool): true if valid, false otherwise.
 */
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

/**
 * @brief Splits the RGB string into components.
 *
 * @details
 * - Checks for trailing comma (invalid).
 * - Splits by ',' into segments (expected 3).
 * - Ensures memory allocation succeeded.
 * - Ensures no missing values via check_missing_rgb().
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param data (char *): Raw RGB string.
 *
 * @return (char **): Array of string segments, or NULL on error.
 */
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

/**
 * @brief Ensures exactly 3 RGB components are present.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param segment (char **): Array of string segments.
 *
 * @return (bool): true if exactly 3 values, false otherwise.
 */
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
