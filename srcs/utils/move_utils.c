#include "game.h"

bool	can_move(t_game *g, double x, double y)
{
	t_map	*map;
	int		tl;
	int		tr;
	int		tt;
	int		tb;

	map = &g->data.map;
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (false);
	tl = (int)(x - PLAYER_MARGIN);
	tr = (int)(x + PLAYER_MARGIN);
	tt = (int)(y - PLAYER_MARGIN);
	tb = (int)(y + PLAYER_MARGIN);
	if (tl < 0 || tr >= (int)map->width
		|| tt < 0 || tb >= (int)map->height)
		return (false);
	if (map->matrix[tt][tl] == WALL
		|| map->matrix[tt][tr] == WALL
		|| map->matrix[tb][tl] == WALL
		|| map->matrix[tb][tr] == WALL)
		return (false);
	return (true);
}

void	attempt_move(t_game *g, t_axis *pos, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = pos->x + dx;
	ny = pos->y + dy;
	if (can_move(g, nx, pos->y))
		pos->x = nx;
	if (can_move(g, pos->x, ny))
		pos->y = ny;
}
