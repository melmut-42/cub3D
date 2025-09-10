#include "game.h"

/**
 * @brief Rotates a 2D vector by a given angle.
 *
 * @details
 * - Uses precomputed sine and cosine tables for efficiency.
 * - Stores the old vector values before rotation.
 * - Applies standard 2D rotation matrix:
 *   x' = x * cos(angle) - y * sin(angle)
 *   y' = x * sin(angle) + y * cos(angle)
 *
 * @param data (t_data *): Pointer to data structure containing trig tables.
 * @param vec (t_axis *): Pointer to the vector to rotate (modified in place).
 * @param angle (double): Rotation angle in radians.
 * 
 * @return void
 */
void	rotate_vector(t_data *data, t_axis *vec, double angle)
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

/**
 * @brief Converts a radian angle into an index for trig tables.
 *
 * @details
 * - Normalizes the angle to [0, 2π).
 * - Scales the angle to match NUM_OF_DEGREE entries.
 * - Example: angle = π/2 → index ~ 90 if NUM_OF_DEGREE = 360.
 *
 * @param angle (double): Angle in radians.
 *
 * @return (int): Integer index into precomputed trig tables.
 */
int	get_angle_index(double angle)
{
	int	index;

	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	index = (int)(angle * NUM_OF_DEGREE / (2 * M_PI));
	return (index);
}

/**
 * @brief Converts degrees into radians.
 *
 * @param deg (double): Angle in degrees.
 *
 * @return (double): Angle in radians.
 */
double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}
