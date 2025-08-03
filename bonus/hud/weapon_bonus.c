#include "game.h"
#include "bonus.h" // TODO: Check if necessary

// TODO: Move these to header file
static int	shake_offset_x = 0;
static int	shake_offset_y = 0;
static int	shake_direction_x = 1; // 1 right, -1 left
static int	shake_direction_y = 1; // 1 forward, -1 back
static int	weapon_base_y = 0; // Base Y position (will be set to bottom)

// TODO: Organise this code, move helper functions somewhere else, apply 42 norm, and fix leaks
// TODO: Make the weapon image load sticking to the bottom of the screen
// TODO: Make the weapon shake only one movement

int get_pixel_from_img(t_img *img, int x, int y)
{
	char *pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

t_img *load_xpm_to_img(void *mlx, char *path)
{
	t_img *img = malloc(sizeof(t_img));
	if (!img)
		return NULL;
	
	img->img_ptr = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->img_ptr)
	{
		free(img);
		return NULL;
	}
	
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(mlx, img->img_ptr);
		free(img);
		return NULL;
	}
	
	return img;
}

// * Gets the pixel color from the image at specified coordinates
static void put_pixel_to_screen(t_game *game, int x, int y, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return;

	t_img *img = &game->mlx->frame_img;

	char *pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));

	*(unsigned int *)pixel = color;
}

// * Makes a shake effect on the weapon image by offsetting its position (CS 1.6 style)
static void	shake_weapon(t_game *game, t_img *weapon_img)
{
	int	x_offset;
	int	y_offset;
	int	color;
	int	i;
	int	y;
	
	if (!weapon_img || !weapon_img->addr)
		return;
	
	// Set weapon base position to bottom-right corner
	if (weapon_base_y == 0)
		weapon_base_y = WIN_HEIGHT - weapon_img->height - 10;
	
	// CS 1.6 style positioning: right side, bottom of screen with shake
	x_offset = WIN_WIDTH - weapon_img->width - 50 + shake_offset_x;
	y_offset = weapon_base_y + shake_offset_y;
	
	i = 0;
	while (i < weapon_img->height)
	{
		y = 0;
		while (y < weapon_img->width)
		{
			color = get_pixel_from_img(weapon_img, y, i);

			// ? is 0 transparent??
			if (color != 0) // Assuming 0 is transparent
				put_pixel_to_screen(game, x_offset + y, y_offset + i, color);
			y++;
		}
		i++;
	}
}

// * Draws the weapon image on the screen with CS 1.6-style shaking effect
void draw_weapon(t_game *game)
{
	// TODO: Fix these later on (do NOT declare on the same line lol)
	static int		frame_count = 0;
	static t_img	*weapon_img = NULL; // TODO: free this later on
	static bool		load_attempted = false;

	if (!weapon_img && !load_attempted)
	{
		load_attempted = true;
		weapon_img = load_xpm_to_img(game->mlx->mlx_ptr, "textures/test_pack/karambit.xpm");
		if (!weapon_img)
		{
			printf("Warning: Could not load weapon texture\n");
			return;
		}
	}
	
	if (!weapon_img)
		return ;

	frame_count++;
	
	if (frame_count % 3 == 0) // Update every 3rd frame for slower movement
	{
		// Horizontal shake (left-right)
		shake_offset_x += shake_direction_x * 1;
		if (shake_offset_x > 3 || shake_offset_x < -3)
			shake_direction_x *= -1;
		
		// Vertical shake (forward-back simulation)
		shake_offset_y += shake_direction_y * 1;
		if (shake_offset_y > 2 || shake_offset_y < -2)
			shake_direction_y *= -1;
	}

	shake_weapon(game, weapon_img);
}
