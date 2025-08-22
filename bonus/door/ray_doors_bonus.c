#include "game.h"
#include "bonus.h"

static double	calc_perp_dist(t_game *game, t_ray *ray);

void	update_ray_door(t_game *game, t_ray *ray, int map_y, int map_x)
{
	t_door	*door;

	door = get_the_door(game, map_x, map_y);
	if (!door)
		return ;
	if (door->open <= 0.0)
	{
		ray->does_hit = true;
		ray->is_door = true;
		return ;
	}
	if (door->open >= 1.0)
		return ;
    if (ray->door_feat.ptr)
        return ;
    ray->door_feat.ptr = door;
	ray->door_feat.ptr = door;
	ray->door_feat.pos.x = map_x;
	ray->door_feat.pos.y = map_y;
	ray->door_feat.side = ray->side;
	ray->door_feat.open = door->open;
	ray->door_feat.perp_dist = calc_perp_dist(game, ray);
}

static double	calc_perp_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->pos.x - game->player.pos.x
				+ (1 - ray->step_x) / 2.0) / ray->dir.x);
	else
		return ((ray->pos.y - game->player.pos.y
				+ (1 - ray->step_y) / 2.0) / ray->dir.y);
}
