#include "game.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	if (keycode == KEY_W)
		game->player.movement[W] = 1;
	if (keycode == KEY_S)
		game->player.movement[S] = 1;
	if (keycode == KEY_A)
		game->player.movement[A] = 1;
	if (keycode == KEY_D)
		game->player.movement[D] = 1;
	if (keycode == KEY_LEFT)
		game->player.rot.x = -3.42;
	if (keycode == KEY_RIGHT)
		game->player.rot.x = +3.42;
	return (0);
}

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
	if (keycode == KEY_LEFT)
		game->player.rot.x = 0;
	if (keycode == KEY_RIGHT)
		game->player.rot.x = 0;
	return (0);
}
