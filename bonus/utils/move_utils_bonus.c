#include "game.h"
#include "bonus.h"

static bool	is_blocking_tile(t_game *g, int x, int y);

bool	can_move(t_game *g, double x, double y)
{
	int	left_cell_x;
	int	right_cell_x;
	int	top_cell_y;
	int	bottom_cell_y;

	if (x < 0.0 || y < 0.0
		|| x >= g->data.map.width || y >= g->data.map.height)
		return (false);

	left_cell_x = (int)(x - PLAYER_MARGIN);
	right_cell_x = (int)(x + PLAYER_MARGIN);
	top_cell_y = (int)(y - PLAYER_MARGIN);
	bottom_cell_y = (int)(y + PLAYER_MARGIN);

	if (left_cell_x < 0 || right_cell_x >= (int)g->data.map.width
		|| top_cell_y < 0 || bottom_cell_y >= (int)g->data.map.height)
		return (false);

	if (is_blocking_tile(g, left_cell_x,  top_cell_y)
	 || is_blocking_tile(g, right_cell_x, top_cell_y)
	 || is_blocking_tile(g, left_cell_x,  bottom_cell_y)
	 || is_blocking_tile(g, right_cell_x, bottom_cell_y))
		return (false);

	return (true);
}

void	attempt_move(t_game *g, t_axis *pos, double dx, double dy)
{
	double	next_x;
	double	next_y;

	next_x = pos->x + dx;
	next_y = pos->y + dy;

	if (can_move(g, next_x, pos->y))
		pos->x = next_x;
	if (can_move(g, pos->x, next_y))
		pos->y = next_y;
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
		door = find_door(g, x, y);
		if (!door || door->open < 1.0)
			return (true);
	}
	return (false);
}
