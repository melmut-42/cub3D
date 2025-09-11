#include "game.h"

/**
 * @brief Compares two strings lexicographically.
 *
 * @details
 * - Iterates through both strings until characters differ or end is reached.
 * - Returns the difference between the first mismatching characters.
 *
 * @param s1 (const char *): First string.
 * @param s2 (const char *): Second string.
 *
 * @return (int): Negative if s1 < s2, zero if equal, positive if s1 > s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/**
 * @brief Checks whether a string contains only digits (ignoring spaces).
 *
 * @details
 * - Skips leading spaces and checks every non-space character.
 * - Returns false for NULL pointers or strings fully composed of spaces.
 *
 * @param str (char *): The string to check.
 *
 * @return (bool): true if the string represents a number, false otherwise.
 */
bool	is_number(char *str)
{
	int	i;

	if (!str)
		return (false);
	if (is_fully_space(str))
		return (false);
	i = 0;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Determines if a character is considered whitespace.
 *
 * @param c (char): The character to check.
 *
 * @return (bool): true if the character is whitespace, false otherwise.
 */
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

/**
 * @brief Checks if a string is composed entirely of whitespace characters.
 *
 * @details
 * - Iterates through the string and validates all characters with is_space().
 *
 * @param str (char *): The string to check.
 *
 * @return (bool): true if fully whitespace, false otherwise.
 */
bool	is_fully_space(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Trims a string and frees the original memory.
 *
 * @details
 * - Frees the original raw string after trimming.
 * - Displays an error message and returns NULL if trimming fails.
 *
 * @param game (t_game *): Pointer to the main game structure for error handling.
 * @param raw (char *): The original string to trim.
 * @param trim_set (char *): Set of characters to trim from the string.
 *
 * @return (char *): The trimmed string or NULL on failure.
 */
char	*ultimate_trim(t_game *game, char *raw, char *trim_set)
{
	char	*trimmed;

	trimmed = ft_strtrim(raw, trim_set);
	free(raw);
	if (!trimmed)
	{
		game->error_flag = false;
		display_error_message(ERR_GAME, true);
		return (NULL);
	}
	return (trimmed);
}
