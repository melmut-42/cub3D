#include "game.h"

// * Frees all texture images in the game
void	free_textures(t_game *game)
{
	t_texture *tex;
	int	i;

	if (!game || !game->mlx || !game->mlx->mlx_ptr)
		return;

	tex = &game->data.texture;
	i = 0;
	while (i < NUMBER_DIR)
	{
		if (tex->textures[i].img_ptr)
		{
			mlx_destroy_image(game->mlx->mlx_ptr, tex->textures[i].img_ptr);
			tex->textures[i].img_ptr = NULL;
		}
		i++;
	}
	
	// Destroy frame buffer image
	if (game->mlx->frame_img.img_ptr)
	{
		mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->frame_img.img_ptr);
		game->mlx->frame_img.img_ptr = NULL;
	}

	// TODO: Fix leak :(
	// if (game->mlx->weapon_img.img_ptr)
	// {
	// 	mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->weapon_img.img_ptr);
	// 	game->mlx->weapon_img.img_ptr = NULL;
	// }
}

// * Destroy mlx window and display properly
void	destroy_img(t_game *game)
{
	if (game->mlx)
	{
		// Free all texture images and frame buffer
		free_textures(game);

		mlx_mouse_show(game->mlx->mlx_ptr, game->mlx->win_ptr);
		
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
