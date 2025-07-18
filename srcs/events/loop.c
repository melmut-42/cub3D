#include "game.h"

// TODO: fix segmfault on walls
// TODO: fix movement
// TODO: fix segfault when lines are too small
// TODO: write table for trigonometry
static void render_scene(t_game *game);
static void	update_player(t_player *player, t_map *map);
static void render_game(t_game *game);
static void	rotate_vector(t_axis *vec, double angle);

static void	rotate_vector(t_axis *vec, double angle)
{
	double	old_x;
	double	old_y;

	old_x = vec->x;
	old_y = vec->y;
	
	// Rotate the player's direction vector by a given angle
	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
	vec->y = vec->x * sin(angle) + vec->y * cos(angle);
}

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
        update_player(&game->player, &game->data.map);
    }
    // Render the game state
    render_game(game);
    return (0);
}

// TODO: Fix direction based error + speed
// * Handles player movement
static void	update_player(t_player *player, t_map *map)
{
	// Update player position based on movement flags
	if (player->mov_up)
		player->pos.x += player->dir.x * player->mov_speed;
	if (player->mov_down)
		player->pos.x -= player->dir.x * player->mov_speed;
	if (player->mov_left)
		player->pos.y -= player->dir.y * player->mov_speed;
	if (player->mov_right)
		player->pos.y += player->dir.y * player->mov_speed;

	// Update player rotation based on rotation flags
	if (player->rot.x)
		rotate_vector(&player->dir, player->rot.x * player->sens.x); // TODO: Implement rotate_vector function
	if (player->rot.y)
		rotate_vector(&player->dir, player->rot.y * player->sens.y); // TODO: lol above
	
	// Ensure player stays within map bounds
	if (player->pos.x < 0)
		player->pos.x = 0;
	if (player->pos.x >= map->width)
		player->pos.x = map->height - 1;
	if (player->pos.y < 0)
		player->pos.y = 0;
	if (player->pos.y >= map->height)
		player->pos.y = map->height - 1;
	if (player->dir.x < -1.0f)
		player->dir.x = -1.0f;
	if (player->dir.x > 1.0f)
		player->dir.x = 1.0f;
	if (player->dir.y < -1.0f)
		player->dir.y = -1.0f;
	if (player->dir.y > 1.0f)
		player->dir.y = 1.0f;
	if (player->dir.x == 0 && player->dir.y == 0)
	{
		player->dir.x = 1.0f; // Default direction if no movement
		player->dir.y = 0.0f;
	}
}

static void render_game(t_game *game)
{
    // Render main 3D scene
    render_scene(game);

    // TODO: Render minimap overlay
    //draw_minimap(game);

	// TODO: Render HUD elements
	//draw_hud(game);
}

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
