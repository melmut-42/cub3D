#include "game.h"

static int get_angle_index(double angle);

// * Rotates a vector by a given angle
void rotate_vector(t_data *data, t_axis *vec, double angle)
{
	double	old_x;
	double	old_y;
	int		index;

	index = get_angle_index(angle);
	old_x = vec->x;
	old_y = vec->y;
	vec->x = old_x * data->cos_table[index] - old_y * data->sin_table[index];
	vec->y = old_x * data->sin_table[index] + old_y * data->cos_table[index];
}

static int get_angle_index(double angle)
{
	int index;

	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	index = (int)(angle * (180.0 / M_PI)) % NUM_OF_DEGREE;
	return (index);
}
