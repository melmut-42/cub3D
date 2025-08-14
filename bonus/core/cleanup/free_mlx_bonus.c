#include "game.h"

static void	free_normal_textures(t_game *game)
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

static void	free_special_textures(t_game *game)
{
	if (!game || !game->mlx || !game->mlx->mlx_ptr)
		return ;
	if (game->mlx->frame_img.img_ptr)
	{
		mlx_destroy_image(game->mlx->mlx_ptr,
			game->mlx->frame_img.img_ptr);
		game->mlx->frame_img.img_ptr = NULL;
	}
	if (game->weapon.weapon_img && game->weapon.weapon_img->img_ptr)
	{
		mlx_destroy_image(game->mlx->mlx_ptr,
			game->weapon.weapon_img->img_ptr);
		free(game->weapon.weapon_img);
		game->weapon.weapon_img = NULL;
	}
}

void	free_textures(t_game *game)
{
	free_normal_textures(game);
	free_special_textures(game);
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
