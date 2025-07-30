#include "game.h"

static bool	check_accessability(t_game *game);
static bool	check_invalid_element(t_game *game, char **matrix);
static void	flood_fill(t_game *game, char **matrix, int x, int y);

bool	check_map(t_game *game)
{
	return (check_invalid_element(game, game->data.map.matrix)
		&& check_accessability(game));
}

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
					|| matrix[i][j] == GROUND || is_player(matrix[i][j])))
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
