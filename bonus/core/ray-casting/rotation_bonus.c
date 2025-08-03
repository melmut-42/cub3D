#include "game.h"

// * Rotates a vector by a given angle
void rotate_vector(t_data *data, t_axis *vec, double angle)
{
	double	old_x;
	double	old_y;
	int		index;

	// Get the index of the angle in the cosine and sine tables
	index = get_angle_index(angle);
	old_x = vec->x;
	old_y = vec->y;
	vec->x = old_x * data->cos_table[index] - old_y * data->sin_table[index];
	vec->y = old_x * data->sin_table[index] + old_y * data->cos_table[index];
}

// * Calculates the angle between two vectors
int get_angle_index(double angle)
{
	int index;

	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	index = (int)(angle * NUM_OF_DEGREE / (2 * M_PI));
	return (index);
}


double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

