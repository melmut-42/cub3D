#include "game.h"

/**
 * @brief Frees wall textures.
 *
 * @details
 * - Iterates over all directions (NUMBER_DIR).
 * - If an image exists, destroys it using mlx_destroy_image.
 * - Sets img_ptr to NULL after freeing.
 *
 * @param game Pointer to the main game structure.
 * 
 * @return void
 */
static void	free_walls(t_game *game)
{
	t_texture	*tex;
	int			i;

	if (!game || !game->mlx || !game->mlx->mlx_ptr)
		return ;
	tex = &game->data.texture;
	i = 0;
	while (i < NUMBER_DIR)
	{
		if (tex->textures[i].img_ptr)
		{
			mlx_destroy_image(game->mlx->mlx_ptr,
				tex->textures[i].img_ptr);
			tex->textures[i].img_ptr = NULL;
		}
		i++;
	}
}

/**
 * @brief Frees the weapon texture.
 *
 * @details
 * - Checks if weapon and weapon image exist.
 * - Destroys the MLX image and frees its structure.
 *
 * @param game Pointer to the main game structure.
 * 
 * @return void
 */
static void	free_weapon(t_game *game)
{
	if (!game || !game->mlx || !game->mlx->mlx_ptr || !game->weapon)
		return ;
	if (game->weapon->weapon_img && game->weapon->weapon_img->img_ptr)
	{
		mlx_destroy_image(game->mlx->mlx_ptr,
			game->weapon->weapon_img->img_ptr);
		free(game->weapon->weapon_img);
		game->weapon->weapon_img = NULL;
	}
}

/**
 * @brief Frees door textures and door data.
 *
 * @details
 * - Iterates through all door animation frames (NUM_DOOR_FRAMES).
 * - Destroys each MLX image if it exists.
 * - Frees the door array if allocated.
 *
 * @param game Pointer to the main game structure.
 * 
 * @return void
 */
static void	free_doors(t_game *game)
{
	int	i;

	if (!game || !game->mlx || !game->mlx->mlx_ptr)
		return ;
	i = 0;
	while (i < NUM_DOOR_FRAMES)
	{
		if (game->data.texture.doors[i].img_ptr)
			mlx_destroy_image(game->mlx->mlx_ptr,
				game->data.texture.doors[i].img_ptr);
		game->data.texture.doors[i].img_ptr = NULL;
		i++;
	}
	if (game->doors)
		ft_free((void **)&game->doors);
}

/**
 * @brief Frees all game textures.
 *
 * @details
 * - Frees walls, doors, and weapon textures.
 * - Frees the frame buffer image if allocated.
 *
 * @param game Pointer to the main game structure.
 * 
 * @return void
 */
void	free_textures(t_game *game)
{
	free_walls(game);
	free_doors(game);
	free_weapon(game);
	if (game->mlx->frame_img.img_ptr)
	{
		mlx_destroy_image(game->mlx->mlx_ptr,
			game->mlx->frame_img.img_ptr);
		game->mlx->frame_img.img_ptr = NULL;
	}
}

/**
 * @brief Destroys MLX images, window, and display.
 *
 * @details
 * - Frees all textures.
 * - Destroys the window if it exists.
 * - Destroys the MLX display and frees its pointer.
 * - Finally frees the mlx structure itself.
 *
 * @param game Pointer to the main game structure.
 * 
 * @return void
 */
void	destroy_img(t_game *game)
{
	if (game->mlx)
	{
		free_textures(game);
		if (game->mlx->mlx_ptr && game->mlx->win_ptr)
		{
			mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
			game->mlx->win_ptr = NULL;
		}
		if (game->mlx->mlx_ptr)
		{
			mlx_destroy_display(game->mlx->mlx_ptr);
			free(game->mlx->mlx_ptr);
			game->mlx->mlx_ptr = NULL;
		}
	}
	free(game->mlx);
}
