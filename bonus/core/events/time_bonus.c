#include <sys/time.h>
#include "game.h"

t_ms	get_timestamp(t_game *game)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) != 0)
	{
		display_error_message(ERR_TIME, true);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	return ((t_ms)now.tv_sec * 1000ULL + (t_ms)(now.tv_usec / 1000));
}

bool	should_update(t_game *game)
{
	t_ms	now;
	t_ms	elapsed;
	t_ms	one_second;

	one_second = 1000;
	now = get_timestamp(game);
	elapsed = now - game->last_update;
	if (game->last_update == 0 || elapsed >= (one_second / TARGET_FPS))
	{
		game->last_update = now;
		return (true);
	}
	return (false);
}
