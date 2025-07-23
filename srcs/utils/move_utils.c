#include "game.h"

// * Helper that checks if a position is inside map and not a wall
bool	can_move(t_map *map, double x, double y)
{
	int mx;
	int my;

	mx = (int)x;
	my = (int)y;

	if (mx < 0 || mx >= (int)map->width)
		return (false);

	if (my < 0 || my >= (int)map->height)
		return (false);

	if (map->matrix[my][mx] == WALL)
		return (false);

	return (true);
}

// * Helper to attempt movement in a direction
void	attempt_move(t_map *map, t_axis *pos, double dx, double dy)
{
	double nx;
	double ny;

	nx = pos->x + dx;
	ny = pos->y + dy;

	if (can_move(map, nx, pos->y))
		pos->x = nx;

	if (can_move(map, pos->x, ny))
		pos->y = ny;
}
