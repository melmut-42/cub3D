#include "game.h"

static double	calc_perp_dist(t_game *game, t_ray *ray);

/**
 * @brief Updates the ray with door information when intersecting a door tile.
 *
 * @details
 * - Checks if the door is fully closed, fully open, or partially open.
 * - Updates ray properties accordingly to handle door rendering.
 * 
 * @param game (t_game *): Pointer to the main game structure.
 * @param ray (t_ray *): Pointer to the ray being processed.
 * @param map_y (int): Y-coordinate of the map cell being checked.
 * @param map_x (int): X-coordinate of the map cell being checked.
 *
 * @return void
 */
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

/**
 * @brief Calculates the perpendicular distance from the player to the door hit point.
 *
 * @details
 * - Uses the raycasting algorithm to adjust for grid stepping.
 * - Chooses calculation based on which side (vertical or horizontal) was hit.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param ray (t_ray *): Pointer to the ray containing hit data.
 *
 * @return (double): The perpendicular distance to the door.
 */
static double	calc_perp_dist(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->pos.x - game->player.pos.x
				+ (1 - ray->step_x) / 2.0) / ray->dir.x);
	else
		return ((ray->pos.y - game->player.pos.y
				+ (1 - ray->step_y) / 2.0) / ray->dir.y);
}
