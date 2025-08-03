#include "game.h"

// * Loops through each character in the string and draws it with an outline
static void	outline_loop(void *mlx, void *win, int x, int y, int c, char *str)
{
	int		dx;
	int		dy;

	dx = -1;
	while (dx <= 1)
	{
		dy = -1;
		while (dy <= 1)
		{
			if (dx != 0 || dy != 0)
			{
				mlx_string_put(mlx, win, x + dx, y + dy, c, str);
				mlx_string_put(mlx, win, x + dx + 1, y + dy, c, str);
			}
			dy++;
		}
		dx++;
	}
}

// * Draws a single character with black outline and slight scaling
static void	draw_outline(void *mlx, void *win, int x, int y, int color, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	outline_loop(mlx, win, x, y, 0x000000, str);
	mlx_string_put(mlx, win, x, y, color, str);
	mlx_string_put(mlx, win, x + 1, y, color, str);
}

// * Draws a full string with outline and spacing
void	mlx_out_txt(void *mlx, void *win, int x, int y, int color, char *str)
{
	int	offset_x;
	int	i;

	offset_x = 0;
	i = 0;
	while (str[i])
	{
		draw_outline(mlx, win, x + offset_x, y, color, str[i]);
		offset_x += 10;
		i++;
	}
}
