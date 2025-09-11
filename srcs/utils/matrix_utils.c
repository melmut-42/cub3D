#include "game.h"

/**
 * @brief Creates a deep copy of the map matrix.
 *
 * @details
 * - Allocates a new array of strings sized to match the map height.
 * - Duplicates each row from the original matrix using ft_strdup().
 * - On allocation failure, sets the game's error flag, displays an error message,
 *   frees any allocated rows, and returns NULL.
 *
 * @param game (t_game *): Pointer to the main game structure, used for error handling.
 * @param matrix (char **): The original map matrix to copy.
 *
 * @return (char **): A newly allocated copy of the map matrix, or NULL on failure.
 */
char	**copy_matrix(t_game *game, char **matrix)
{
	char	**copy;
	int		i;

	copy = ft_calloc((game->data.map.height) + 1, sizeof(char *));
	if (!copy)
	{
		game->error_flag = true;
		display_error_message(ERR_GAME, true);
		return (NULL);
	}
	i = 0;
	while (matrix[i])
	{
		copy[i] = ft_strdup(matrix[i]);
		if (!copy[i])
		{
			game->error_flag = true;
			display_error_message(ERR_GAME, true);
			free_tab(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}
