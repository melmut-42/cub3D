#include "game.h"

// * Handles the close event of the game window
int	handle_close(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

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
		game->player.mov_speed += 0.02;

	// TODO: Remove other keys

	if (keycode == KEY_LEFT)
		game->player.rot.x = -0.42;
	if (keycode == KEY_RIGHT)
		game->player.rot.x = +0.42;
	
	// TODO: Handle pitch with mouse instead
	if (keycode == KEY_UP)
		game->player.pitch_angle -= 42; // look up
	if (keycode == KEY_DOWN)
		game->player.pitch_angle += 42; // look down

	// TODO: Handle pitch with mouse instead + make it smoother
	// Clamp pitch
	if (game->player.pitch_angle > 200)
		game->player.pitch_angle = 200;
	if (game->player.pitch_angle < -200)
		game->player.pitch_angle = -200;

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
		game->player.mov_speed -= 0.02;

	// TODO: Remove other keys

	if (keycode == KEY_LEFT)
		game->player.rot.x = 0;
	if (keycode == KEY_RIGHT)
		game->player.rot.x = 0;

	return (0);
}

// TODO: Check if necessary
// * Handles mouse events within the game window
int	handle_mouse(int x, int y, t_game *game)
{
	// ! This function is currently not implemented.
	(void)x;
	(void)y;
	(void)game;
	// static int	prev_y = -1;

	// if (!game || !game->mlx || !game->mlx->win_ptr)
	// 	return (0);

	// // Only handle inside-window motion
	// if (x < 0 || x >= game->mlx->width || y < 0 || y >= game->mlx->height)
	// 	return (0);

	// // Horizontal rotation
	// game->player.rot.x = (x - game->mlx->width / 2) * game->player.sens.x;

	// // Vertical rotation — track delta from previous y
	// if (prev_y != -1)
	// {
	// 	int dy = y - prev_y;
	// 	game->player.pitch_angle += dy * game->player.sens.y;

	// 	// Clamp pitch
	// 	if (game->player.pitch_angle > 200)
	// 		game->player.pitch_angle = 200;
	// 	if (game->player.pitch_angle < -200)
	// 		game->player.pitch_angle = -200;
	// }
	// prev_y = y;

	// // Reset mouse to center (only for x)
	// mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->win_ptr,
	// 	game->mlx->width / 2, y);

	// mlx_mouse_hide(game->mlx->mlx_ptr, game->mlx->win_ptr);

	return (0);
}
