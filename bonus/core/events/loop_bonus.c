#include "game.h"
#include "bonus.h"

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
	render_game(game);
	return (0);
}

static void	render_game(t_game *game)
{
	double	dt;

	dt = get_delta_time();
	update_doors(game, dt);
	render_scene(game);
	draw_minimap(game);
	draw_hud(game);
	draw_weapon(game);
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
	mlx_put_image_to_window(game->mlx->mlx_ptr,
		game->mlx->win_ptr,
		game->mlx->frame_img.img_ptr,
		0, 0);
}
