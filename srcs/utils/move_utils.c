#include "game.h"

// * Helper that checks if a position is inside map and not a wall
bool	can_move(t_map *map, double x, double y)
{
	int	tile_left;
	int	tile_right;
	int	tile_top;
	int	tile_bottom;

	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (false);

	// Compute tile positions around the player considering the margin
	tile_left = (int)(x - PLAYER_MARGIN);
	tile_right = (int)(x + PLAYER_MARGIN);
	tile_top = (int)(y - PLAYER_MARGIN);
	tile_bottom = (int)(y + PLAYER_MARGIN);

	// Reject if margin-check positions are outside the map
	if (tile_left < 0 || tile_right >= (int)map->width
		|| tile_top < 0 || tile_bottom >= (int)map->height)
		return (false);

	// Check if there is a wall in the surrounding tiles
	if (map->matrix[tile_top][tile_left] == WALL
		|| map->matrix[tile_top][tile_right] == WALL
		|| map->matrix[tile_bottom][tile_left] == WALL
		|| map->matrix[tile_bottom][tile_right] == WALL)
		return (false);

	return (true);
}

// * Helper to attempt movement in a direction
void	attempt_move(t_map *map, t_axis *pos, double dx, double dy)
{
	double nx;
	double ny;

	nx = pos->x + dx;
	ny = pos->y + dy;

	if (can_move(map, nx, pos->y))
		pos->x = nx;

	if (can_move(map, pos->x, ny))
		pos->y = ny;
}
