#include "game.h"

// * Handles keypress events for player movement and rotation
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);

	if (keycode == KEY_W)
		game->player.mov_up = 1;

	if (keycode == KEY_S)
		game->player.mov_down = 1;

	if (keycode == KEY_A)
		game->player.mov_left = 1;

	if (keycode == KEY_D)
		game->player.mov_right = 1;

	if (keycode == KEY_SHIFT)
		game->player.mov_speed += game->player.mov_speed / 4;

	// TODO: Remove other keys

	if (keycode == KEY_LEFT)
		game->player.rot.x = -0.42;
	if (keycode == KEY_RIGHT)
		game->player.rot.x = +0.42;
	
	// TODO: Handle pitch with mouse instead
	if (keycode == KEY_UP)
		game->player.pitch_angle -= MAX_PITCH / (double) 10; // look up
	if (keycode == KEY_DOWN)
		game->player.pitch_angle += MAX_PITCH / (double) 10; // look down

	// TODO: Handle pitch with mouse instead + make it smoother
	// TODO: Implement constant macros
	// Clamp pitch
	if (game->player.pitch_angle > MAX_PITCH)
		game->player.pitch_angle = MAX_PITCH;
	if (game->player.pitch_angle < MIN_PITCH)
		game->player.pitch_angle = MIN_PITCH;

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

	if (keycode == KEY_SHIFT)
		game->player.mov_speed -= game->player.mov_speed / 4;

	// TODO: Remove other keys

	if (keycode == KEY_LEFT)
		game->player.rot.x = 0;
	if (keycode == KEY_RIGHT)
		game->player.rot.x = 0;

	return (0);
}
