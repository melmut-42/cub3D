#include "game.h"

static void	outline_loop(t_game *game, int x, int y, char *str);
static void	draw_outline(t_game *game, int x, int y, char c);

/**
 * @brief Renders a full string with outlined characters using MLX.
 *
 * @details
 * - Iterates through each character of the string.
 * - Draws each character with draw_outline() and spaces them horizontally.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param x (int): Starting x-coordinate for the string.
 * @param y (int): Y-coordinate for the string.
 * @param str (char *): The string to render.
 *
 * @return void
 */
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

/**
 * @brief Draws a black outline around a character string for better visibility.
 *
 * @details
 * - Iterates through surrounding positions to create an outline effect.
 * - Renders the string twice per offset to thicken the border.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param x (int): Base x-coordinate for the text.
 * @param y (int): Base y-coordinate for the text.
 * @param str (char *): The string to outline.
 *
 * @return void
 */
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

/**
 * @brief Draws a single outlined character at the given screen position.
 *
 * @details
 * - Converts the character to a temporary string for MLX rendering.
 * - Draws the black outline first, then the white character on top.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param x (int): X-coordinate of the character.
 * @param y (int): Y-coordinate of the character.
 * @param c (char): The character to render.
 *
 * @return void
 */
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
