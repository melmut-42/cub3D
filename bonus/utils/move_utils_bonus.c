#include "game.h"
#include "bonus.h"

static bool	is_blocking_tile(t_game *g, int x, int y);

bool	can_move(t_game *g, double x, double y)
{
	int	tl;
	int	tr;
	int	tt;
	int	tb;

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

// * Attempts to move player along a vector, respecting collision logic
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

// * Returns true if player is pressing a movement key
bool	is_moving(t_game *g)
{
	return ((g->player.movement[W] != g->player.movement[S])
		|| (g->player.movement[A] != g->player.movement[D]));
}

// * Returns true if player is in air and going upwards
bool	is_jumping(t_game *g)
{
	return (g->player.vertical.in_air
		&& g->player.vertical.vertical_vel > 0);
}

// * Returns true if the given tile blocks movement
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
		door = find_door_at(g, x, y);
		if (!door || door->open < 1.0)
			return (true);
	}
	return (false);
}
