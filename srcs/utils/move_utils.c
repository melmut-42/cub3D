#include "game.h"


static bool	is_blocking_tile(t_game *g, int x, int y);

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
