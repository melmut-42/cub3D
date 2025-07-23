#include "game.h"

#define INF_DIST 1e30

static void	init_ray(const t_game *g, const t_player *p,
				t_ray *ray, int x);
static void	init_steps(const t_player *p, t_ray *ray);
static void	perform_dda(t_game *game, t_ray *ray);
static void	calc_perp_dist(t_game *g, t_ray *ray);

// * Casts a ray for the specified pixel x in the game
void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(game, &game->player, ray, x);
	init_steps(&game->player, ray);
	perform_dda(game, ray);
	calc_perp_dist(game, ray);
}

// * Initializes the ray direction, map position, and delta distances
static void	init_ray(const t_game *g, const t_player *p,
				t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)g->mlx->width - 1;

	// Calculate ray direction based on camera plane
	ray->dir.x = p->dir.x + p->plane.x * camera_x;
	ray->dir.y = p->dir.y + p->plane.y * camera_x;

	// Current map square of the player
	ray->map.x = (int)p->pos.x;
	ray->map.y = (int)p->pos.y;

	// Calculate distance to next x-side and y-side
	if (ray->dir.x == 0)
		ray->delta_dist.x = INF_DIST;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INF_DIST;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
}

// * Determines step direction and initial side distances
static void	init_steps(const t_player *p, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		// Distance from player to next x-side
		ray->side_dist.x = (p->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map.x + 1 - p->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		// Distance from player to next y-side
		ray->side_dist.y = (p->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map.y + 1 - p->pos.y) * ray->delta_dist.y;
	}
}

// * Performs the DDA algorithm to find the first wall hit
static void	perform_dda(t_game *game, t_ray *ray)
{
	ray->does_hit = false;
	while (!ray->does_hit)
	{
		// Choose shortest side distance to step
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step_x;
			ray->side = 0; // hit vertical side
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step_y;
			ray->side = 1; // hit horizontal side
		}
		const int	map_x = (int)ray->map.x;
		const int	map_y = (int)ray->map.y;

		// Check if ray has hit a wall
		if (game->data.map.matrix[map_y][map_x] == WALL)
			ray->does_hit = true;
	}
}

// * Calculate perpendicular wall distance to avoid fish-eye effect
static void	calc_perp_dist(t_game *g, t_ray *ray)
{
	double	off;
	double	num;

	if (ray->side == 0)
		off = 0.5 * (1 - ray->step_x);
	else
		off = 0.5 * (1 - ray->step_y);

	if (ray->side == 0)
		num = ray->map.x - g->player.pos.x + off;
	else
		num = ray->map.y - g->player.pos.y + off;

	if (ray->side == 0)
		ray->perp_wall_dist = num / ray->dir.x;
	else
		ray->perp_wall_dist = num / ray->dir.y;
}
