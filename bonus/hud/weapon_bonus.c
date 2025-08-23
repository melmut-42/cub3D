#include "game.h"
#include "bonus.h"

static float	lerp(float start, float end, float t)
{
	return (start + (end - start) * t);
}

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

static void	shake_on_jump(t_game *game)
{
	t_weapon	*weapon;

	weapon = &game->weapon;
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

static void	shake_on_movement(t_game *game)
{
	t_weapon	*weapon;

	weapon = &game->weapon;
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

void	draw_weapon(t_game *game)
{
	t_weapon	*weapon;

	weapon = &game->weapon;
	if (!weapon->weapon_img && !weapon->load_attempted)
	{
		weapon->load_attempted = true;
		weapon->weapon_img = xpm_to_img(game->mlx->mlx_ptr,
				"textures/test_pack/karambit.xpm");
		if (!weapon->weapon_img)
		{
			display_error_message("Could not load weapon texture!", true);
			return ;
		}
	}
	weapon->frame_count++;
	shake_on_jump(game);
	if (!is_jumping(game))
		shake_on_movement(game);
	shake_weapon(game, weapon, weapon->weapon_img);
}
