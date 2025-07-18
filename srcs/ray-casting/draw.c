#include "game.h"

// * Rotates a vector by a given angle
void	rotate_vector(t_axis *vec, double angle)
{
	double	old_x;
	double	old_y;

	old_x = vec->x;
	old_y = vec->y;
	
	// Rotate the player's direction vector by a given angle
	vec->x = old_x * cos(angle) - old_y * sin(angle);
	vec->y = old_x * sin(angle) + old_y * cos(angle);
}
