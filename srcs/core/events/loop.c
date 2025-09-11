#include "game.h"

static void	render_scene(t_game *game);
static void	render_game(t_game *game);

/**
 * @brief Main game loop called by MLX.
 *
 * @details
 * - Updates player movement and rotation if active.
 * - Handles jump and crouch/stand-up events with fixed delta time
 * - Updates door states (opening/closing).
 * - Calls the rendering pipeline to draw the scene, minimap, weapon, and HUD.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (int): Always returns 0.
 */
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

/**
 * @brief Handles the full rendering pipeline of the game.
 *
 * @details
 * - Renders the 3D scene using raycasting.
 * - Draws the minimap overlay.
 * - Draws the weapon sprite if equipped.
 * - Pushes the final frame buffer to the MLX window.
 * - Draws HUD elements on top of the frame.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * 
 * @return void
 */
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

/**
 * @brief Renders the 3D world scene using raycasting.
 *
 * @details
 * - Iterates over every screen column.
 * - Casts a ray for each column.
 * - Draws the corresponding vertical slice (walls, doors, etc.).
 *
 * @param game (t_game *game): Pointer to the main game structure.
 * 
 * @return void
 */
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
