#include "game.h"
#include "bonus.h"

static bool	is_blocking_tile(t_game *g, int x, int y);

bool	can_move(t_game *g, double x, double y)
{
	int tl;
	int tr;
	int tt;
	int tb;

	if (x < 0 || y < 0
		|| x >= g->data.map.width || y >= g->data.map.height)
		return (false);
	tl = (int)(x - PLAYER_MARGIN);
	tr = (int)(x + PLAYER_MARGIN);
	tt = (int)(y - PLAYER_MARGIN);
	tb = (int)(y + PLAYER_MARGIN);
	if (tl < 0 || tr >= (int)g->data.map.width
		|| tt < 0 || tb >= (int)g->data.map.height)
		return (false);
	if (is_blocking_tile(g, tl, tt)
		|| is_blocking_tile(g, tr, tt)
		|| is_blocking_tile(g, tl, tb)
		|| is_blocking_tile(g, tr, tb))
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

bool	is_moving(t_game *g)
{
	return ((g->player.movement[W] != g->player.movement[S])
		|| (g->player.movement[A] != g->player.movement[D]));
}

bool	is_jumping(t_game *g)
{
	return (g->player.vertical.in_air
		&& g->player.vertical.vertical_vel > 0);
}

static bool	is_blocking_tile(t_game *g, int x, int y)
{
	char	tile;

	if (x < 0 || y < 0
		|| x >= (int)g->data.map.width
		|| y >= (int)g->data.map.height)
		return (true);
	tile = g->data.map.matrix[y][x];
	if (tile == WALL)
		return (true);
	return (false);
}
