#include "game.h"

static double	vec_len(double x, double y);

/**
 * @brief Handles player interaction with a door directly in front.
 *
 * @details
 * - Calculates a forward position based on player direction and step size.
 * - Checks if the targeted cell contains a door.
 * - Computes distance to ensure interaction only within range.
 * - Toggles the door's open state and marks it as moving.
 *
 * @param g (t_game *): Pointer to the main game structure.
 *
 * @return void
 */
void	handle_door_interact(t_game *g)
{
	t_axis		forward;
	t_axis_int	cell;
	t_door		*door;
	double		dist;

	forward.x = g->player.pos.x + g->player.dir.x * INTERACT_STEP;
	forward.y = g->player.pos.y + g->player.dir.y * INTERACT_STEP;
	cell.x = (int)forward.x;
	cell.y = (int)forward.y;
	if (g->data.map.matrix[cell.y][cell.x] != DOOR)
		return ;
	dist = vec_len((cell.x + 0.5) - g->player.pos.x,
			(cell.y + 0.5) - g->player.pos.y);
	if (dist < MIN_DOOR_INT_DIST)
		return ;
	door = get_the_door(g, cell.x, cell.y);
	if (!door)
		return ;
	door->want_open = !door->want_open;
	door->is_moving = true;
}

/**
 * @brief Finds and returns a pointer to the door at specified coordinates.
 *
 * @details
 * - Iterates through the door list in the game structure.
 * - Compares door positions with the given map coordinates.
 * - Returns NULL if no door matches.
 *
 * @param g (t_game *): Pointer to the main game structure.
 * @param x (int): X-coordinate of the door.
 * @param y (int): Y-coordinate of the door.
 *
 * @return (t_door*): Pointer to the matching door, or NULL if not found.
 */
t_door	*get_the_door(t_game *g, int x, int y)
{
	size_t	i;

	i = 0;
	while (i < g->door_count)
	{
		if (g->doors[i].pos.x == x && g->doors[i].pos.y == y)
			return (&g->doors[i]);
		i++;
	}
	return (NULL);
}

/**
 * @brief Computes the length (magnitude) of a 2D vector.
 *
 * @param x (double): X-component of the vector.
 * @param y (double): Y-component of the vector.
 *
 * @return (double): The vector length.
 */
static double	vec_len(double x, double y)
{
	return (sqrt(x * x + y * y));
}
