#include "game.h"

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

static void	free_weapon(t_game *game)
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

static void	free_doors(t_game *game)
{
	int	i;

	if (!game || !game->mlx || !game->mlx->mlx_ptr)
		return ;
	i = 0;
	while (i < NUM_DOOR_FRAMES)
	{
		if (game->data.texture.doors[i].img_ptr)
			mlx_destroy_image(game->mlx->mlx_ptr, game->data.texture.doors[i].img_ptr);
		game->data.texture.doors[i].img_ptr = NULL;
		i++;
	}
	if (game->doors)
		ft_free((void **)&game->doors);
}

void	free_textures(t_game *game)
{
	free_walls(game);
	free_weapon(game);
	free_doors(game);
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
