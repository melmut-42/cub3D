#include "game.h"


static void	render_scene(t_game *game);
static void	render_game(t_game *game);

int	gameloop(t_game *game)
{
	if (!should_update(game))
		return (0);
	if (game->player.movement[W] || game->player.movement[A]
		|| game->player.movement[S] || game->player.movement[D]
		|| game->player.rot.x || game->player.rot.y
		|| game->player.vertical.in_air)
	{
		update_player_movement(game, &game->player);
	}
	jump_event(&game->player, 0.016);
	stand_up(&game->player, 0.016);
	update_doors(game);
	render_game(game);
	return (0);
}

static void	render_game(t_game *game)
{
	render_scene(game);
	draw_minimap(game);
	if (game->weapon)
		draw_weapon(game);
	mlx_put_image_to_window(game->mlx->mlx_ptr,
		game->mlx->win_ptr,
		game->mlx->frame_img.img_ptr,
		0, 0);
	draw_hud(game);
}

static void	render_scene(t_game *game)
{
	t_ray	ray;
	int		screen_width;
	int		i;

	i = 0;
	screen_width = game->mlx->width;
	while (i < screen_width)
	{
		cast_ray(game, &ray, i);
		draw_column(game, &ray, i);
		i++;
	}
}
