#include "game.h"
#include "bonus.h"

static void	init_ray(t_ray *ray, t_axis pos, t_axis dir);
static void	init_ray_steps(t_ray *ray, t_axis pos);
static bool	is_door_and_valid(t_game *g, t_ray *ray, t_door **out, double dist);
static double	calc_dist(t_ray *r, t_axis p);

t_door	*scan_facing_door(t_game *g, t_axis player_pos, t_axis dir)
{
	t_ray	    ray;
	double	    dist;
	t_door	    *door;
    t_axis_int  pos;

	init_ray(&ray, player_pos, dir);
    init_ray_steps(&ray, player_pos);
	dist = 0.0;
	while (dist < MAX_INTERACT_DIST)
	{
		step_ray(&ray);
		dist = calc_dist(&ray, player_pos);
        pos.x = (int)ray.map.x;
        pos.y = (int)ray.map.y;
		if (g->data.map.matrix[pos.y][pos.x] == WALL)
			break ;
		if (is_door_and_valid(g, &ray, &door, dist))
			return (door);
	}
	return (NULL);
}

static double	calc_dist(t_ray *r, t_axis p)
{
	double d;

	if (r->side == 0)
		d = (r->map.x - p.x + (1 - r->step_x) / 2.0) / r->dir.x;
	else
		d = (r->map.y - p.y + (1 - r->step_y) / 2.0) / r->dir.y;
	if (d < 0.0)
		d = 0.0;
	return (fabs(d));
}

static bool	is_door_and_valid(t_game *g, t_ray *ray, t_door **out, double dist)
{
	t_door		*door;
    t_axis_int	pos;

    pos.x = (int)ray->map.x;
    pos.y = (int)ray->map.y;
	if (g->data.map.matrix[pos.y][pos.x] != DOOR)
		return (false);
	door = find_door(g, pos.x, pos.y);
	if (!door)
		return (false);
	printf("dist: %f\n", dist);
	if (!(dist > MIN_INTERACT_DIST))
		return (false);
	*out = door;
	return (true);
}

static void	init_ray(t_ray *ray, t_axis pos, t_axis dir)
{
	ray->dir = dir;
	ray->map.x = (int)pos.x;
	ray->map.y = (int)pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = INF_DIST;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INF_DIST;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
}

static void	init_ray_steps(t_ray *ray, t_axis pos)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - pos.y) * ray->delta_dist.y;
	}
}
