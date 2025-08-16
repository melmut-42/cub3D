#include "game.h"
#include "bonus.h"

static bool	check_hit(t_game *game, t_ray *ray);

void	perform_dda(t_game *game, t_ray *ray)
{
	ray->does_hit = false;
	while (!ray->does_hit)
	{
		step_ray(ray);
		ray->does_hit = check_hit(game, ray);
	}
}

void	step_ray(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step_y;
		ray->side = 1;
	}
}

static bool	check_hit(t_game *game, t_ray *ray)
{
	t_door	*door;
	int		map_x;
	int		map_y;

	map_x = (int)ray->map.x;
	map_y = (int)ray->map.y;
	if (game->data.map.matrix[map_y][map_x] == WALL)
		return (true);
	if (game->data.map.matrix[map_y][map_x] == DOOR)
	{
		door = find_door(game, map_x, map_y);
		if (door && is_ray_blocked_by_door(game, ray, door))
			return (true);
	}
	return (false);
}
