#include "game.h"
#include "bonus.h"

// TODO: Consider moving this to a math utility file
// Lerping is a common technique to smoothly interpolate between two values
// * Function linearly interpolates between start and end based on t (0.0 to 1.0)
static float lerp(float start, float end, float t)
{
	return start + (end - start) * t;
}

// * Makes a shake effect on the weapon image by offsetting its position (CS 1.6 style)
static void shake_weapon(t_game *game, t_weapon *weapon, t_img *weapon_img)
{
	int x_offset;
	int y_offset;
	int color;
	int i;
	int y;

	if (!weapon_img || !weapon_img->addr)
		return;

	// Set weapon base position to the bottom of the screen 
	if (weapon->weapon_base_y == 0)
		weapon->weapon_base_y = WIN_HEIGHT - weapon_img->height + 10; // Ensures weapon sticking to the bottom

	// CS 1.6 style positioning: right side, bottom of screen with shake
	x_offset = WIN_WIDTH - weapon_img->width - 100 + weapon->shake_offset_x; // Centered
	y_offset = weapon->weapon_base_y + weapon->shake_offset_y;

	// Loop through each pixel of the weapon image and draw it on the frame buffer
	i = 0;
	while (i < weapon_img->height)
	{
		y = 0;
		while (y < weapon_img->width)
		{
			color = get_pixel_from_img(weapon_img, y, i);

			// ? is 0 transparent??
			if (color != 0) // Assuming 0 is transparent
				ft_put_pixel(&game->mlx->frame_img, x_offset + y, y_offset + i, color);
			y++;
		}
		i++;
	}
}

// * Applies shaking effect based on player jump
static void shake_on_jump(t_game *game)
{
	t_weapon *weapon = &game->weapon;

	if (is_jumping(game))
	{
		weapon->jump_frame++;
		weapon->shake_offset_y = (int)(-12.0f * sinf(weapon->jump_frame * 0.02f)); // smooth oscillation effect
		weapon->shake_offset_x = 0; // no horizontal shake on jump
	}
	else
	{
		weapon->jump_frame = 0;
	}
}

// * Applies shaking effect based on player movement
static void shake_on_movement(t_game *game)
{
	t_weapon *weapon = &game->weapon;

	if (is_moving(game))
	{
		if (weapon->frame_count % 3 == 0) // Update every 3rd frame for slower movement
		{
			// Horizontal shake (left-right)
			weapon->shake_offset_x += weapon->shake_direction_x * 2;
			if (weapon->shake_offset_x > 8 || weapon->shake_offset_x < -8)
				weapon->shake_direction_x *= -1;

			// Vertical shake (forward-back simulation)
			weapon->shake_offset_y += weapon->shake_direction_y * 2;
			if (weapon->shake_offset_y > 2 || weapon->shake_offset_y < -8)
				weapon->shake_direction_y *= -1;
		}
	}
	else
	{
		// smooth reset to zero
		weapon->shake_offset_x = (int)lerp(weapon->shake_offset_x, 0, 0.2f);
		weapon->shake_offset_y = (int)lerp(weapon->shake_offset_y, 0, 0.2f);

		weapon->shake_direction_x = 1;
		weapon->shake_direction_y = 1;
	}
}

// * Draws the weapon image on the screen with CS 1.6-style shaking effect
void draw_weapon(t_game *game)
{
	t_weapon *weapon = &game->weapon;

	// TODO: Init this as something else? // DO I EVEN nEED THIS?????????
	if (!weapon->weapon_img && !weapon->load_attempted)
	{
		weapon->load_attempted = true;
		weapon->weapon_img = xpm_to_img(game->mlx->mlx_ptr, "textures/test_pack/karambit.xpm");
		if (!weapon->weapon_img)
		{
			printf("Warning: Could not load weapon texture\n");
			return;
		}
	}

	weapon->frame_count++;

	shake_on_jump(game);

	if (!is_jumping(game))
		shake_on_movement(game);

	shake_weapon(game, weapon, weapon->weapon_img);
}
