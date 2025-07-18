#include "game.h"

// TODO: fix segmfault on walls
// TODO: fix movement
// TODO: fix segfault when lines are too small
// TODO: write table for trigonometry
static void render_scene(t_game *game);
static void	update_player(t_game *g, t_player *p, t_map *map);
static void render_game(t_game *game);

// * The main game loop function that updates the game state
int gameloop(t_game *game)
{
    if (!should_update(game))
        return (0);
    if (game->player.mov_up   || game->player.mov_down  ||
        game->player.mov_left || game->player.mov_right ||
        game->player.rot.x    || game->player.rot.y)
    {
        // Update player position and rotation based on input
        update_player(game, &game->player, &game->data.map);
    }
    // Render the game state
    render_game(game);
    return (0);
}

// TODO: Fix direction based movement + speed
// * Handles player movement
static void	update_player(t_game *g, t_player *p, t_map *map)
{
	t_axis	strafe;
	double	angle;

	// Calculate strafe direction based on player direction
	strafe.x = -p->dir.y;
	strafe.y = p->dir.x;

	if (p->mov_up)
	{
		p->pos.x += p->dir.x * p->mov_speed;
		p->pos.y += p->dir.y * p->mov_speed;
	}
	if (p->mov_down)
	{
		p->pos.x -= p->dir.x * p->mov_speed;
		p->pos.y -= p->dir.y * p->mov_speed;
	}
	if (p->mov_right)
	{
		p->pos.x += strafe.x * p->mov_speed;
		p->pos.y += strafe.y * p->mov_speed;
	}
	if (p->mov_left)
	{
		p->pos.x -= strafe.x * p->mov_speed;
		p->pos.y -= strafe.y * p->mov_speed;
	}
	if (p->rot.x)
	{
		angle = p->rot.x * p->sens.x;
		rotate_vector(&g->data, &p->dir, angle);
		rotate_vector(&g->data, &p->plane, angle);
	}

	// TODO: Implement collision detection with the map
	// TODO: Check if the player is within the bounds of the map
	(void)map;
}

static void render_game(t_game *game)
{
    // Render main 3D scene
    render_scene(game);

    // TODO: Render minimap overlay
    //draw_minimap(game);

	// TODO: Render HUD elements
	//draw_hud(game);

	// TODO: Render other game elements
	//draw_elements(game);
}

// * Casts rays to render the scene
static void render_scene(t_game *game)
{
	int		i;
    t_ray	ray;
    int		screenW;

	screenW = game->mlx->width;
	i = 0;
	while (i < screenW)
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
