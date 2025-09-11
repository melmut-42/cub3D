#include "game.h"

static bool	check_accessability(t_game *game);
static bool	check_invalid_element(t_game *game, char **matrix);
static void	flood_fill(t_game *game, char **matrix, int x, int y);

/**
 * @brief Validates the map of the game.
 *
 * @details
 * - Checks if all elements in the map are valid.
 * - Ensures that the map is properly closed and accessible
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if the map is valid, false otherwise.
 */
bool	check_map(t_game *game)
{
	return (check_invalid_element(game, game->data.map.matrix)
		&& check_accessability(game));
}

/**
 * @brief Verifies that the map is fully accessible.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if the map is accessible, false otherwise.
 */
static bool	check_accessability(t_game *game)
{
	char	**cpy;
	int		i;
	int		j;

	cpy = copy_matrix(game, game->data.map.matrix);
	if (!cpy)
		return (false);
	flood_fill(game, cpy, (int)game->player.pos.x, (int)game->player.pos.y);
	i = 0;
	while (cpy[i])
	{
		j = 0;
		while (cpy[i][j])
		{
			if (cpy[i][j] == GROUND)
				flood_fill(game, cpy, j, i);
			j++;
		}
		i++;
	}
	free_tab(cpy);
	if (game->error_flag)
		return (false);
	return (true);
}

/**
 * @brief Checks for invalid characters inside the map matrix.
 *
 * @details
 * Valid elements:
 * - Space (' ')
 * - Wall (WALL)
 * - Ground (GROUND)
 * - Player start position (N, S, E, W)
 * - Door (DOOR)
 *
 * If an invalid element is found, sets the error flag and displays an error.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param matrix (char **) The map matrix to validate.
 *
 * @return (bool): true if all elements are valid, false otherwise.
 */
static bool	check_invalid_element(t_game *game, char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (!(is_space(matrix[i][j]) || matrix[i][j] == WALL
					|| matrix[i][j] == GROUND || is_player(matrix[i][j])
					|| matrix[i][j] == DOOR))
			{
				display_error_message(ERR_ELEM, false);
				game->error_flag = true;
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

/**
 * @brief Flood fill algorithm to validate accessibility.
 *
 * @details
 * - Marks visited cells to avoid infinite loops.
 * - If flood fill reaches the border, an accessibility error is raised.
 * - Recursively checks all adjacent positions (up, down, left, right).
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param matrix (char **): A copy of the map matrix.
 * @param x (int): Current x position.
 * @param y (int): Current y position.
 * 
 * @return void
 */
static void	flood_fill(t_game *game, char **matrix, int x, int y)
{
	if (game->error_flag)
		return ;
	if (matrix[y][x] == WALL || matrix[y][x] == VISITED || game->error_flag)
		return ;
	if (is_space(matrix[y][x]) || x == 0 || matrix[y][x] == '\0' || y == 0
		|| (size_t)y >= game->data.map.height - 1)
	{
		if (!game->error_flag)
			display_error_message(ERR_ACCESS, false);
		game->error_flag = true;
		return ;
	}
	matrix[y][x] = VISITED;
	flood_fill(game, matrix, x + 1, y);
	flood_fill(game, matrix, x - 1, y);
	flood_fill(game, matrix, x, y + 1);
	flood_fill(game, matrix, x, y - 1);
}
