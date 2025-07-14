#include "game.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC keycode on Linux (X11)
	{
		free_game(game);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	handle_close(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}
