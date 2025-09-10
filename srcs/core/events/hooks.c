#include "game.h"

/**
 * @brief Initializes MLX event hooks and the main game loop.
 *
 * @details
 * - Sets callback functions for:
 *   - Event 17: Window close button (handle_close).
 *   - Event 2:  Key press (handle_keypress).
 *   - Event 3:  Key release (handle_keyrelease).
 *   - Event 6:  Mouse movement (handle_mouse).
 *   - Event 4:  Mouse button click (handle_mouse_click).
 * - Registers the main game loop function (gameloop).
 *
 * @param game (t_game *): Pointer to the main game structure.
 * 
 * @return void
 */
void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, 17, 1L << 0, handle_close, game);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->mlx->win_ptr, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->mlx->win_ptr, 6, 1L << 6, handle_mouse, game);
	mlx_hook(game->mlx->win_ptr, 4, 1L << 2, handle_mouse_click, game);
	mlx_loop_hook(game->mlx->mlx_ptr, gameloop, game);
}

/**
 * @brief Handles window close event.
 *
 * @details
 * - Frees all game resources.
 * - Exits the program with EXIT_SUCCESS.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return Always returns 0 (unused).
 */
int	handle_close(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}
