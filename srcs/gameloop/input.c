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

	if (keycode == KEY_LEFT)
		game->player.rot_left = 1;

	if (keycode == KEY_RIGHT)
		game->player.rot_right = 1;

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

	if (keycode == KEY_LEFT)
		game->player.rot_left = 0;

	if (keycode == KEY_RIGHT)
		game->player.rot_right = 0;

	return (0);
}

// TODO: Check if necessary
// * Handles mouse events within the game window
int	handle_mouse(int x, int y, t_game *game)
{
	int	midpoint_x;

	// Check if the mouse is within the window bounds
	if (x < 0 || x >= game->mlx->width || y < 0 || y >= game->mlx->height)
		return (0); // Ignore mouse events outside the window

	// Update player mouse coordinates
	game->player.mouse_x = x;
	game->player.mouse_y = y;

	// Update player rotation based on mouse position
	midpoint_x = game->mlx->width / 2;
	game->player.rot_left = (x < midpoint_x); // Rotate left if mouse is on the left side of the screen
	game->player.rot_right = (x > midpoint_x); // Rotate right if mouse is on the right side of the screen
	return (0);
}
