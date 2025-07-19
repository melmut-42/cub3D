#include "game.h"

// * Helper that checks if a position is inside map and not a wall
int	can_move(t_map *map, double x, double y)
{
	int mx;
	int my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || mx >= (int)map->width)
		return (0);
	if (my < 0 || my >= (int)map->height)
		return (0);
	if (map->matrix[my][mx] == '1')
		return (0);
	return (1);
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
