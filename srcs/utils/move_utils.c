#include "game.h"

static bool	is_blocking_tile(t_game *g, int x, int y);

/**
 * @brief Checks if the player can move to the specified coordinates.
 *
 * @details
 * - Verifies the target position is within the map boundaries.
 * - Calculates margins around the player's position to avoid clipping walls.
 * - Uses is_blocking_tile() to test surrounding tiles for collisions.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param x (double): Target x-coordinate.
 * @param y (double): Target y-coordinate.
 *
 * @return (bool): true if movement is allowed, false otherwise.
 */
bool	can_move(t_game *g, double x, double y)
{
	int	left;
	int	right;
	int	top;
	int	bottom;

	if (x < 0 || y < 0
		|| x >= g->data.map.width || y >= g->data.map.height)
		return (false);
	left = (int)(x - PLAYER_MARGIN);
	right = (int)(x + PLAYER_MARGIN);
	top = (int)(y - PLAYER_MARGIN);
	bottom = (int)(y + PLAYER_MARGIN);
	if (left < 0 || right >= (int)g->data.map.width
		|| top < 0 || bottom >= (int)g->data.map.height)
		return (false);
	if (is_blocking_tile(g, left, top)
		|| is_blocking_tile(g, right, top)
		|| is_blocking_tile(g, left, bottom)
		|| is_blocking_tile(g, right, bottom))
		return (false);
	return (true);
}

/**
 * @brief Attempts to move the player by dx and dy while checking collisions.
 *
 * @details
 * - Calculates the new position based on delta values.
 * - Updates each axis independently to prevent corner clipping.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param pos (t_axis *): Current player position.
 * @param dx (double): Change in x-coordinate.
 * @param dy (double): Change in y-coordinate.
 *
 * @return void
 */
void	attempt_move(t_game *g, t_axis *pos, double dx, double dy)
{
	t_axis	new_pos;

	new_pos.x = pos->x + dx;
	new_pos.y = pos->y + dy;
	if (can_move(g, new_pos.x, pos->y))
		pos->x = new_pos.x;
	if (can_move(g, pos->x, new_pos.y))
		pos->y = new_pos.y;
}

/**
 * @brief Checks whether the player is currently moving.
 *
 * @details
 * - Compares opposite movement inputs (W/S and A/D).
 * - Returns true if forward/backward or left/right inputs are active.
 *
 * @param g (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if the player is moving, false otherwise.
 */
bool	is_moving(t_game *g)
{
	return ((g->player.movement[W] != g->player.movement[S])
		|| (g->player.movement[A] != g->player.movement[D]));
}

/**
 * @brief Determines if the player is currently jumping upward.
 *
 * @details
 * - Checks if the player is marked as in_air and has a positive vertical velocity.
 *
 * @param g (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if the player is in the air and ascending, false otherwise.
 */
bool	is_jumping(t_game *g)
{
	return (g->player.vertical.in_air
		&& g->player.vertical.vertical_vel > 0);
}

/**
 * @brief Determines if a map tile blocks movement.
 *
 * @details
 * - Returns true for out-of-bounds coordinates or walls.
 * - Checks for doors and blocks movement unless fully open.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param x (int): Tile x-coordinate.
 * @param y (int): Tile y-coordinate.
 *
 * @return (bool): true if the tile blocks movement, false otherwise.
 */
static bool	is_blocking_tile(t_game *g, int x, int y)
{
	char	tile;
	t_door	*door;

	if (x < 0 || y < 0
		|| x >= (int)g->data.map.width
		|| y >= (int)g->data.map.height)
		return (true);
	tile = g->data.map.matrix[y][x];
	if (tile == WALL)
		return (true);
	if (tile == DOOR)
	{
		door = get_the_door(g, x, y);
		if (door && door->open != 1)
			return (true);
	}
	return (false);
}
