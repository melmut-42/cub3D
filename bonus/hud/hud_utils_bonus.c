#include "game.h"
#include "bonus.h"

static void	outline_loop(t_game *game, int x, int y, char *str)
{
	int	dx;
	int	dy;

	dx = -1;
	while (dx <= 1)
	{
		dy = -1;
		while (dy <= 1)
		{
			if (dx != 0 || dy != 0)
			{
				mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr,
					x + dx, y + dy, COLOR_BLACK, str);
				mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr,
					x + dx + 1, y + dy, COLOR_BLACK, str);
			}
			dy++;
		}
		dx++;
	}
}

static void	draw_outline(t_game *game, int x, int y, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	outline_loop(game, x, y, str);
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y,
		COLOR_WHITE, str);
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr, x + 1, y,
		COLOR_WHITE, str);
}

void	mlx_out_txt(t_game *game, int x, int y, char *str)
{
	int	offset_x;
	int	i;

	offset_x = 0;
	i = 0;
	while (str[i])
	{
		draw_outline(game, x + offset_x, y, str[i]);
		offset_x += 10;
		i++;
	}
}
