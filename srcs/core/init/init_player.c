#include "game.h"

static void	update_dir(t_dir dir, t_player *p);
static void	update_pos(t_axis *pos, t_axis new_pos, int *x, int *y);
static bool	set_player(t_game *game, t_player *player);
static bool	update_player(t_game *g, t_player *player, t_axis new_pos);

/**
 * @brief Initializes the player position and direction.
 *
 * @details
 * - Searches the map for a valid player start marker (N, S, W, E).
 * - Ensures only one player is defined.
 * - Sets the player's position and direction accordingly.
 * - Displays an error if no player or multiple players are found.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if initialization succeeded, false otherwise.
 */
bool	init_player(t_game *game)
{
	if (!set_player(game, &game->player))
		return (false);
	if (game->player.pos.x == NPOS || game->player.pos.y == NPOS)
	{
		display_error_message(ERR_NO_PLAYER, false);
		game->error_flag = true;
		return (false);
	}
	return (true);
}

/**
 * @brief Scans the map matrix to find the player start position.
 *
 * @details
 * - Iterates through all cells of the map.
 * - If a player marker (N, S, W, E) is found:
 *   - Calculates the centered position (x + 0.5, y + 0.5).
 *   - Updates player position and direction using update_player().
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param player (t_player *): Pointer to the player structure.
 *
 * @return (bool): true if player position is set, false otherwise.
 */
static bool	set_player(t_game *game, t_player *player)
{
	t_axis	pos;
	char	**matrix;
	int		y;
	int		x;

	matrix = game->data.map.matrix;
	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
		{
			if (is_player(matrix[y][x]))
			{
				pos.x = x + 0.5;
				pos.y = y + 0.5;
				if (!update_player(game, player, pos))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

/**
 * @brief Updates player position and direction based on map marker.
 *
 * @details
 * - Ensures there is only one player in the map.
 * - Sets the player's position and orientation (dir and plane).
 * - Direction is determined by the map marker (N, S, W, E).
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param player (t_player *): Pointer to the player structure.
 * @param new_pos (t_axis): Position of the player on the map (centered).
 *
 * @return (bool): true if successful, false if multiple players found.
 */
static bool	update_player(t_game *g, t_player *player, t_axis new_pos)
{
	char	*dir_set;
	int		y;
	int		x;

	if (player->pos.x != NPOS && player->pos.y != NPOS)
	{
		display_error_message(ERR_MULTI_P, false);
		g->error_flag = true;
		return (false);
	}
	update_pos(&player->pos, new_pos, &x, &y);
	dir_set = DIR_SET;
	if (dir_set[NORTH] == g->data.map.matrix[y][x])
		update_dir(NORTH, player);
	else if (dir_set[SOUTH] == g->data.map.matrix[y][x])
		update_dir(SOUTH, player);
	else if (dir_set[WEST] == g->data.map.matrix[y][x])
		update_dir(WEST, player);
	else
		update_dir(EAST, player);
	return (true);
}

/**
 * @brief Sets player direction and camera plane based on orientation.
 *
 * @details
 * - Direction vector points towards NORTH, SOUTH, WEST, or EAST.
 * - Camera plane vector (for raycasting) is set perpendicular
 *   to the direction with a FOV scaling factor (0.66).
 *
 * @param dir (t_dir): Direction enum (NORTH, SOUTH, WEST, EAST).
 * @param p (t_player *): Pointer to the player structure.
 * 
 * @return void
 */
static void	update_dir(t_dir dir, t_player *p)
{
	p->dir.x = (dir == WEST) * -1 + (dir == EAST);
	p->dir.y = (dir == NORTH) * -1 + (dir == SOUTH);
	if (dir == NORTH)
	{
		p->plane.x = 0.66;
		p->plane.y = 0;
	}
	else if (dir == SOUTH)
	{
		p->plane.x = -0.66;
		p->plane.y = 0;
	}
	else if (dir == WEST)
	{
		p->plane.x = 0;
		p->plane.y = -0.66;
	}
	else if (dir == EAST)
	{
		p->plane.x = 0;
		p->plane.y = 0.66;
	}
}

/**
 * @brief Updates player position coordinates.
 *
 * @details
 * - Stores the new floating-point position.
 * - Also provides integer grid coordinates for map lookup.
 *
 * @param pos (t_axis): Pointer to the player's position (to update).
 * @param new_pos (t_axis): New position (with fractional offsets).
 * @param x (int *): Output pointer for integer X coordinate.
 * @param y (int *): Output pointer for integer Y coordinate.
 * 
 * @return void
 */
static void	update_pos(t_axis *pos, t_axis new_pos, int *x, int *y)
{
	pos->x = new_pos.x;
	pos->y = new_pos.y;
	*x = (int)new_pos.x;
	*y = (int)new_pos.y;
}
