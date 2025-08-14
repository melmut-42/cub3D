#include "game.h"
#include "bonus.h"

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, 17, 1L << 0, handle_close, game);
	mlx_hook(game->mlx->win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->mlx->win_ptr, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->mlx->win_ptr, 6, 1L << 6, handle_mouse, game);
	mlx_hook(game->mlx->win_ptr, 4, 1L << 2, handle_mouse_click, game);
	mlx_loop_hook(game->mlx->mlx_ptr, gameloop, game);
}

int	handle_close(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}
