#include "game.h"

static void	shake_weapon(t_game *game, t_weapon *weapon, t_img *weapon_img);
static void	shake_on_movement(t_game *game);
static void	shake_on_jump(t_game *game);

/**
 * @brief Draws the weapon on screen and applies shake effects.
 *
 * @details
 * - Increments the weapon frame counter.
 * - Applies vertical shake if the player is jumping.
 * - Applies horizontal/vertical sway if the player is moving.
 * - Renders the weapon image with offsets for shake effect.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return void
 */
void	draw_weapon(t_game *game)
{
	game->weapon->frame_count++;
	shake_on_jump(game);
	if (!is_jumping(game))
		shake_on_movement(game);
	shake_weapon(game, game->weapon, game->weapon->weapon_img);
}

/**
 * @brief Renders the weapon image at its shaken position.
 *
 * @details
 * - Calculates x and y offsets based on shake offsets.
 * - Initializes weapon_base_y on first draw.
 * - Iterates through the weapon texture and plots visible pixels.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param weapon (t_weapon *): Pointer to the weapon state structure.
 * @param weapon_img (t_img *): Pointer to the weapon image.
 *
 * @return void
 */
static void	shake_weapon(t_game *game, t_weapon *weapon, t_img *weapon_img)
{
	int	x_offset;
	int	y_offset;
	int	color;
	int	y;
	int	x;

	if (!weapon_img || !weapon_img->addr)
		return ;
	if (weapon->weapon_base_y == 0)
		weapon->weapon_base_y = WIN_HEIGHT - weapon_img->height + 10;
	x_offset = WIN_WIDTH - weapon_img->width - 100 + weapon->shake_offset_x;
	y_offset = weapon->weapon_base_y + weapon->shake_offset_y;
	y = -1;
	while (++y < weapon_img->height)
	{
		x = 0;
		while (x < weapon_img->width)
		{
			color = get_pixel_from_img(weapon_img, x, y);
			if (color != 0)
				ft_put_pixel(&game->mlx->frame_img, x_offset + x,
					y_offset + y, color);
			x++;
		}
	}
}

/**
 * @brief Applies vertical shaking effect when the player is jumping.
 *
 * @details
 * - Increases jump_frame counter for sine-based motion.
 * - Resets offsets when not jumping.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return void
 */
static void	shake_on_jump(t_game *game)
{
	t_weapon	*weapon;

	weapon = game->weapon;
	if (is_jumping(game))
	{
		weapon->jump_frame++;
		weapon->shake_offset_y = -12 * sinf(weapon->jump_frame * 0.02f);
		weapon->shake_offset_x = 0;
	}
	else
	{
		weapon->jump_frame = 0;
	}
}

/**
 * @brief Applies weapon sway when the player is moving.
 *
 * @details
 * - Updates shake offsets and directions based on frame count.
 * - Uses lerp to gradually reset offsets when movement stops.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return void
 */
static void	shake_on_movement(t_game *game)
{
	t_weapon	*weapon;

	weapon = game->weapon;
	if (is_moving(game))
	{
		if (weapon->frame_count % 3 == 0)
		{
			weapon->shake_offset_x += weapon->shake_direction_x * 2;
			if (weapon->shake_offset_x > 8 || weapon->shake_offset_x < -8)
				weapon->shake_direction_x *= -1;
			weapon->shake_offset_y += weapon->shake_direction_y * 2;
			if (weapon->shake_offset_y > 2 || weapon->shake_offset_y < -8)
				weapon->shake_direction_y *= -1;
		}
	}
	else
	{
		weapon->shake_offset_x = (int)lerp(weapon->shake_offset_x, 0, 0.2f);
		weapon->shake_offset_y = (int)lerp(weapon->shake_offset_y, 0, 0.2f);
		weapon->shake_direction_x = 1;
		weapon->shake_direction_y = 1;
	}
}

/**
 * @brief Initializes the weapon structure with default values.
 *
 * @details
 * - Resets frame counters, offsets, and directions.
 * - Sets weapon_img to NULL and weapon_base_y to 0.
 *
 * @param weapon (t_weapon *): Pointer to the weapon structure.
 *
 * @return void
 */
void	weapon_ctor(t_weapon *weapon)
{
	if (!weapon)
		return ;
	weapon->weapon_img = NULL;
	weapon->frame_count = 0;
	weapon->jump_frame = 0;
	weapon->shake_offset_x = 0;
	weapon->shake_offset_y = 0;
	weapon->shake_direction_x = 1;
	weapon->shake_direction_y = 1;
	weapon->weapon_base_y = 0;
}
