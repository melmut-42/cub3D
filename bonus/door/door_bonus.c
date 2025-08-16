#include "game.h"
#include "bonus.h"
#include "sys/time.h"

void	update_doors(t_game *g, double dt)
{
	size_t	i;
	t_door	*d;

	i = 0;
	while (i < g->door_count)
	{
		d = &g->doors[i];
		if (d->want_open)
		{
			d->open += dt * DOOR_MOVE_SPEED;
			if (d->open > 1.0)
				d->open = 1.0;
		}
		else
		{
			d->open -= dt * DOOR_MOVE_SPEED;
			if (d->open < 0.0)
				d->open = 0.0;
		}
		i++;
	}
}

double	get_delta_time(void)
{
	static struct timeval	prev = {0};
	struct timeval			now;
	double					delta;

	gettimeofday(&now, NULL);
	if (prev.tv_sec == 0 && prev.tv_usec == 0)
		prev = now;
	delta = (now.tv_sec - prev.tv_sec)
		+ (now.tv_usec - prev.tv_usec) / 1000000.0;
	prev = now;
	return (delta);
}

void	init_door_movement(t_game *game)
{
	t_door	*door;
	t_axis	dir = game->player.dir;
	t_axis	pos = game->player.pos;

	door = scan_facing_door(game, pos, dir);
	if (!door)
		return ;
	door->want_open = !door->want_open;
}


t_door	*find_door(t_game *game, int x, int y)
{
	size_t	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].pos.x == x && game->doors[i].pos.y == y)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
}


