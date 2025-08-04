#include "game.h"

static void	exec_key_rotation(t_game *game, int keycode, int mode);

// * Handles keypress events for player movement and rotation
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

	if (keycode == KEY_SHIFT && !game->player.vertical.in_air &&
			!game->player.vertical.in_crouch)
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
	
	exec_key_rotation(game, keycode, 0);

	return (0);
}

// * Handles key release events to stop player movement and rotation
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

	// TODO: Remove other keys

	exec_key_rotation(game, keycode, 1);

	return (0);
}

// * Provides rotation by using keys
static void	exec_key_rotation(t_game *game, int keycode, int mode)
{
	// Handles release of rotation keys
	if (mode == 1)
	{
		if (keycode == KEY_LEFT)
			game->player.rot.x = 0;

		if (keycode == KEY_RIGHT)
			game->player.rot.x = 0;

		return ;
	}

	if (keycode == KEY_LEFT)
		game->player.rot.x = -0.42;

	// TODO: Doesn't work after weapon shake was added for some reason (FIX IT)
	if (keycode == KEY_RIGHT)
		game->player.rot.x = +0.42;
	
	if (keycode == KEY_UP)
		game->player.pitch_angle -= MAX_PITCH / (double) 10; // look up

	if (keycode == KEY_DOWN)
		game->player.pitch_angle += MAX_PITCH / (double) 10; // look down

	// Clamp pitch
	if (game->player.pitch_angle > MAX_PITCH)
		game->player.pitch_angle = MAX_PITCH;

	if (game->player.pitch_angle < MIN_PITCH)
		game->player.pitch_angle = MIN_PITCH;
}

// * Ignores mouse click events
int	handle_mouse_click(int button, int x, int y, t_game *game)
{
	(void)button;
	(void)x;
	(void)y;
	(void)game;

	return (0);
}
