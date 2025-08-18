#include "game.h"
#include "bonus.h"

static void	init_ray(const t_game *g, const t_player *p,
				t_ray *ray, int x);
static void	init_steps(const t_player *p, t_ray *ray);
static void	perform_dda(t_game *game, t_ray *ray);
static void	calc_perp_dist(t_game *g, t_ray *ray);

void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(game, &game->player, ray, x);
	init_steps(&game->player, ray);
	perform_dda(game, ray);
	calc_perp_dist(game, ray);
}

static void	init_ray(const t_game *g, const t_player *p,
				t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)g->mlx->width - 1;
	ray->dir.x = p->dir.x + p->plane.x * camera_x;
	ray->dir.y = p->dir.y + p->plane.y * camera_x;
	ray->pos.x = (int)p->pos.x;
	ray->pos.y = (int)p->pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = INF_DIST;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INF_DIST;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
}

static void	init_steps(const t_player *p, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (p->pos.x - ray->pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->pos.x + 1 - p->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (p->pos.y - ray->pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->pos.y + 1 - p->pos.y) * ray->delta_dist.y;
	}
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	int		map_x;
	int		map_y;

	ray->does_hit = false;
	while (!ray->does_hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos.x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->pos.y += ray->step_y;
			ray->side = 1;
		}
		map_x = (int)ray->pos.x;
		map_y = (int)ray->pos.y;
		if (game->data.map.matrix[map_y][map_x] == WALL)
			ray->does_hit = true;
	}
}

static void	calc_perp_dist(t_game *g, t_ray *ray)
{
	double	off;
	double	num;

	if (ray->side == 0)
		off = 0.5 * (1 - ray->step_x);
	else
		off = 0.5 * (1 - ray->step_y);
	if (ray->side == 0)
		num = ray->pos.x - g->player.pos.x + off;
	else
		num = ray->pos.y - g->player.pos.y + off;
	if (ray->side == 0)
		ray->perp_wall_dist = num / ray->dir.x;
	else
		ray->perp_wall_dist = num / ray->dir.y;
}
