#include "game.h"


static double	vec_len(double x, double y);

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

static double	vec_len(double x, double y)
{
	return (sqrt(x * x + y * y));
}
