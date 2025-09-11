#include "game.h"

static void	exec_key_rotation(t_game *game, int keycode, int mode);
static void	exec_key_special(t_game *game, int keycode);

/**
 * @brief Handles key press events.
 *
 * @details
 * - ESC: Closes the game.
 * - W/A/S/D: Starts movement if player is not in air.
 * - SHIFT, SPACE, CTRL, E: Special actions handled by exec_key_special().
 * - Arrow keys: Rotation handled by exec_key_rotation().
 *
 * @param keycode (int): Pressed key code.
 * @param game (t_game *): Pointer to the game structure.
 *
 * @return Always returns 0.
 */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	if (keycode == KEY_W && !game->player.vertical.in_air)
		game->player.movement[W] = 1;
	if (keycode == KEY_S && !game->player.vertical.in_air)
		game->player.movement[S] = 1;
	if (keycode == KEY_A && !game->player.vertical.in_air)
		game->player.movement[A] = 1;
	if (keycode == KEY_D && !game->player.vertical.in_air)
		game->player.movement[D] = 1;
	exec_key_special(game, keycode);
	return (0);
}

/**
 * @brief Handles key release events.
 *
 * @details
 * - ESC: Closes the game.
 * - W/A/S/D: Stops movement.
 * - SHIFT: Restores normal movement speed.
 * - CTRL: Resets crouch target.
 * - Arrow keys: Stops rotation or pitch changes.
 *
 * @param keycode (int): Released key code.
 * @param game (t_game *): Pointer to the game structure.
 *
 * @return Always returns 0.
 */
int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	if (keycode == KEY_W)
		game->player.movement[W] = 0;
	if (keycode == KEY_S)
		game->player.movement[S] = 0;
	if (keycode == KEY_A)
		game->player.movement[A] = 0;
	if (keycode == KEY_D)
		game->player.movement[D] = 0;
	if (keycode == KEY_SHIFT)
		game->player.mov_speed -= game->player.mov_speed / 4;
	if (keycode == KEY_CTRL_L)
		game->player.vertical.crouch_target = 0.0;
	exec_key_rotation(game, keycode, 1);
	return (0);
}

/**
 * @brief Handles player rotation and pitch adjustments.
 *
 * @details
 * - mode == 0 → applies rotation (on key press).
 *   - LEFT / RIGHT arrows: rotates horizontally (yaw).
 *   - UP / DOWN arrows: adjusts pitch angle (looking up/down).
 *   - Pitch is clamped between MIN_PITCH and MAX_PITCH.
 * - mode == 1 → resets rotation (on key release).
 *
 * @param game Pointer to the game structure.
 * @param keycode Pressed/released key code.
 * @param mode 0 = press, 1 = release.
 * 
 * @return void
 */
static void	exec_key_rotation(t_game *game, int keycode, int mode)
{
	if (mode == 1)
	{
		if (keycode == KEY_LEFT)
			game->player.rot.x = 0;
		if (keycode == KEY_RIGHT)
			game->player.rot.x = 0;
		return ;
	}
	if (keycode == KEY_LEFT)
		game->player.rot.x = -3.42;
	if (keycode == KEY_RIGHT)
		game->player.rot.x = +3.42;
	if (keycode == KEY_UP)
		game->player.pitch_angle -= MAX_PITCH / (double) 20;
	if (keycode == KEY_DOWN)
		game->player.pitch_angle += MAX_PITCH / (double) 20;
	if (game->player.pitch_angle > MAX_PITCH)
		game->player.pitch_angle = MAX_PITCH;
	if (game->player.pitch_angle < MIN_PITCH)
		game->player.pitch_angle = MIN_PITCH;
}

/**
 * @brief Handles special key actions (non-movement).
 *
 * @details
 * - SHIFT: Increases movement speed (sprint).
 * - SPACE: Initiates a jump.
 * - CTRL: Initiates crouch.
 * - E: Interacts with doors.
 * - Also forwards arrow keys to exec_key_rotation().
 *
 * @param game (t_game *): Pointer to the game structure.
 * @param keycode (int): Pressed key code.
 * 
 * @return void
 */
static void	exec_key_special(t_game *game, int keycode)
{
	if (keycode == KEY_SHIFT && !game->player.vertical.in_air
		&& !game->player.vertical.in_crouch)
		game->player.mov_speed += game->player.mov_speed / 4;
	if (keycode == KEY_SPACE && !game->player.vertical.in_air)
	{
		game->player.vertical.vertical_vel = JUMP_VELOCITY;
		game->player.vertical.in_air = true;
	}
	if (keycode == KEY_CTRL_L)
	{
		game->player.vertical.crouch_off = CROUCH_SCALE;
		game->player.vertical.crouch_target = CROUCH_SCALE;
	}
	if (keycode == KEY_E)
		handle_door_interact(game);
	exec_key_rotation(game, keycode, 0);
}

/**
 * @brief Handles mouse click events.
 *
 * @param button (int): Mouse button code.
 * @param x (int): Mouse cursor X position.
 * @param y (int): Mouse cursor Y position.
 * @param game (t_game *): Pointer to the game structure.
 *
 * @return Always returns 0.
 */
int	handle_mouse_click(int button, int x, int y, t_game *game)
{
	(void)button;
	(void)x;
	(void)y;
	(void)game;
	return (0);
}
