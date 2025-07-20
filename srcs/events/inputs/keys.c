#include "game.h"

static void	exec_keypress_rotation(t_game *game, int keycode);

// * Handles keypress events for player movement and rotation
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);

	if (keycode == KEY_W && !game->player.vertical.in_air)
		game->player.mov_up = 1;

	if (keycode == KEY_S && !game->player.vertical.in_air)
		game->player.mov_down = 1;

	if (keycode == KEY_A && !game->player.vertical.in_air)
		game->player.mov_left = 1;

	if (keycode == KEY_D && !game->player.vertical.in_air)
		game->player.mov_right = 1;

	if (keycode == KEY_SHIFT && !game->player.vertical.in_air &&
			!game->player.vertical.in_crouch)
		game->player.mov_speed = game->player.mov_speed + (INITIAL_SPEED / 4);

	if (keycode == KEY_SPACE && !game->player.vertical.in_air)
	{
        game->player.vertical.vertical_vel = JUMP_VELOCITY;
        game->player.vertical.in_air = true;
    }

	if (keycode == KEY_CTRL_L || keycode == KEY_CTRL_R)
    {
        game->player.vertical.crouch_offset = CROUCH_SCALE;
        game->player.vertical.crouch_target = CROUCH_SCALE;
    }
	
	exec_keypress_rotation(game, keycode);

	return (0);
}

// * Handles key release events to stop player movement and rotation
int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);

	if (keycode == KEY_W)
		game->player.mov_up = 0;

	if (keycode == KEY_S)
		game->player.mov_down = 0;

	if (keycode == KEY_A)
		game->player.mov_left = 0;

	if (keycode == KEY_D)
		game->player.mov_right = 0;

	if (keycode == KEY_SHIFT && !game->player.vertical.in_air)
		game->player.mov_speed = game->player.mov_speed - (INITIAL_SPEED / 4);

	if (keycode == KEY_CTRL_L)
		game->player.vertical.crouch_target = 0.0;


	// TODO: Remove other keys

	if (keycode == KEY_LEFT)
	{
		game->player.rot.x = 0;
	}
	if (keycode == KEY_RIGHT)
	{

		game->player.rot.x = 0;
	}

	return (0);
}

// * provides rotation by using keys
// TODO: Impelement release mode
static void	exec_keypress_rotation(t_game *game, int keycode)
{
	// TODO: Remove other keys
	// TODO: Implement constant macros
	if (keycode == KEY_LEFT)
		game->player.rot.x = -0.42;
	if (keycode == KEY_RIGHT)
		game->player.rot.x = +0.42;
	
	if (keycode == KEY_UP)
		game->player.pitch_angle -= MAX_PITCH / (double) 10; // look up
	if (keycode == KEY_DOWN)
		game->player.pitch_angle += MAX_PITCH / (double) 10; // look down

	// TODO: Handle pitch with mouse instead + make it smoother

	// Clamp pitch
	if (game->player.pitch_angle > MAX_PITCH)
		game->player.pitch_angle = MAX_PITCH;
	if (game->player.pitch_angle < MIN_PITCH)
		game->player.pitch_angle = MIN_PITCH;
}
