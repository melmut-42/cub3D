#include <sys/time.h>
#include "game.h"

/**
 * @brief Gets the current timestamp in milliseconds.
 *
 * @details
 * - Uses gettimeofday() to get the current time.
 * - Converts seconds and microseconds into milliseconds.
 * - If gettimeofday() fails, displays an error, frees resources, and exits.
 *
 * @param game (t_game *) Pointer to the main game structure (needed for cleanup).
 *
 * @return (t_ms -> uint64_t) Current timestamp in milliseconds (t_ms).
 */
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

/**
 * @brief Determines if a new frame should be rendered.
 *
 * @details
 * - Calculates elapsed time since the last update.
 * - Ensures updates occur at the target frame rate.
 * - Updates last_update if enough time has passed.
 *
 * @param game (t_game *) Pointer to the main game structure.
 *
 * @return (bool): true if the game should update/render this frame, false otherwise.
 */
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
