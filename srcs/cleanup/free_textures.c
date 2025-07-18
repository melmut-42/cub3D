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
}
