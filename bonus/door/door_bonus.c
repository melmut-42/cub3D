#include "game.h"

t_door	*find_door_at(t_game *game, int x, int y)
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

bool	is_ray_blocked_by_door(t_game *g, t_ray *ray, t_door *door)
{
	double	ray_pos;

	if (ray->side == 0)
		ray_pos = g->player.pos.y
			+ ray->side_dist.x * ray->dir.y;
	else
		ray_pos = g->player.pos.x
			+ ray->side_dist.y * ray->dir.x;
	ray_pos -= floor(ray_pos);
	if (ray_pos < door->open)
		return (false);
	return (true);
}
