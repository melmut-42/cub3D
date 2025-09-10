#include "game.h"

static void	update_rot_angles(t_player *player, int delta_x, int delta_y);

/**
 * @brief Handles mouse movement events.
 *
 * @details
 * - Calculates horizontal (dx) and vertical (dy) mouse movement
 *   relative to the screen midpoint.
 * - Updates player's rotation angles accordingly.
 * - Resets the mouse position back to the screen center to allow
 *   continuous rotation without hitting window edges.
 *
 * @param x (int): Current X position of the mouse.
 * @param y (int): Current Y position of the mouse.
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return Always returns 0.
 */
int	handle_mouse(int x, int y, t_game *game)
{
	int	dx;
	int	dy;

	dx = x - MID_POINT_X;
	dy = y - MID_POINT_Y;
	if (dx != 0 || dy != 0)
	{
		update_rot_angles(&game->player, dx, dy);
		mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->win_ptr,
			MID_POINT_X, MID_POINT_Y);
	}
	return (0);
}

/**
 * @brief Updates player's yaw and pitch angles based on mouse delta.
 *
 * @details
 * - Horizontal delta (delta_x) changes yaw (left/right view).
 * - Vertical delta (delta_y) changes pitch (up/down view).
 * - Vertical delta is clamped to avoid extreme sensitivity spikes.
 * - Pitch angle is clamped between MIN_PITCH and MAX_PITCH to prevent
 *   looking too far up or down.
 *
 * @param player (t_player *): Pointer to the player structure.
 * @param delta_x (int): Horizontal mouse movement relative to midpoint.
 * @param delta_y (int): Vertical mouse movement relative to midpoint.
 * 
 * @return void
 */
static void	update_rot_angles(t_player *player, int delta_x, int delta_y)
{
	if (delta_y > MAX_VERTICAL_DELTA)
		delta_y = MAX_VERTICAL_DELTA;
	if (delta_y < -MAX_VERTICAL_DELTA)
		delta_y = -MAX_VERTICAL_DELTA;
	player->rot.x = delta_x * player->sens.x;
	player->pitch_angle -= delta_y * player->sens.y;
	if (player->pitch_angle > MAX_PITCH)
		player->pitch_angle = MAX_PITCH;
	if (player->pitch_angle < MIN_PITCH)
		player->pitch_angle = MIN_PITCH;
}
