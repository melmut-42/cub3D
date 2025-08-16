#include "game.h"
#include "bonus.h"

static bool	check_hit(t_game *game, t_ray *ray);
static void	set_ray_door(t_ray *ray, t_door *door, t_game *game);

double	calc_perp_dist_door(t_player *p, t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->map.x - p->pos.x + (1 - ray->step_x) / 2.0) / ray->dir.x);
	return ((ray->map.y - p->pos.y + (1 - ray->step_y) / 2.0) / ray->dir.y);
}

double	get_wall_hit_pos(t_player *p, t_ray *ray, double perp)
{
	if (ray->side == 0)
		return (p->pos.y + perp * ray->dir.y - floor(p->pos.y + perp * ray->dir.y));
	return (p->pos.x + perp * ray->dir.x - floor(p->pos.x + perp * ray->dir.x));
}

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
		if (door && door->open == 0.0)
			return (true);
		if (door && door->open != 0.0)
			set_ray_door(ray, door, game);
	}
	return (false);
}

static void	set_ray_door(t_ray *ray, t_door *door, t_game *game)
{
	double	perp;
	double	hit_pos;

	perp = calc_perp_dist_door(&game->player, ray);
	hit_pos = get_wall_hit_pos(&game->player, ray, perp);
	ray->door.has = true;
	ray->door.cell.x = ray->map.x;
	ray->door.cell.y = ray->map.y;
	ray->door.side = ray->side;
	ray->door.open = door->open;
	ray->door.perp = perp;
	ray->door.tex_x = (int)(hit_pos * 64);
}


