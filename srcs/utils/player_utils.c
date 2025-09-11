#include "game.h"

/**
 * @brief Checks whether a character represents a valid player direction.
 *
 * @details
 * - Iterates through the predefined DIR_SET of valid direction characters.
 * - Compares the given character against each valid entry.
 * - Returns true if a match is found, otherwise false.
 *
 * @param player (char): The character to check.
 *
 * @return (bool): true if the character is a valid player symbol, false otherwise.
 */
bool	is_player(char player)
{
	int		i;
	char	*dir_set;

	dir_set = DIR_SET;
	i = 0;
	while (dir_set[i])
	{
		if (player == dir_set[i])
			return (true);
		i++;
	}
	return (false);
}
