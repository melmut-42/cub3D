#include "game.h"

void	free_textures(t_game *game)
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
			mlx_destroy_image(game->mlx->mlx_ptr, tex->textures[i].img_ptr);
			tex->textures[i].img_ptr = NULL;
		}
		i++;
	}
	if (game->mlx->frame_img.img_ptr)
	{
		mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->frame_img.img_ptr);
		game->mlx->frame_img.img_ptr = NULL;
	}
}

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
