#include "game.h"

// * HUD rendering functions for the game

// * Renders the FPS counter on the game window
static void render_fps(t_game *game)
{
	// TODO: Find a way to avoid norm violation with static variables and inline definitions
	static t_ms last_time = 0;
	static int frame_count = 0;
	static int fps = 0;
	char buffer[16];
	t_ms now;

	// Get the current timestamp and calculate FPS
	now = get_timestamp(game);
	frame_count++;

	if (now - last_time >= 1000)
	{
		fps = frame_count;
		frame_count = 0;
		last_time = now;
	}

	// Format the FPS value into a string and render it
	sprintf(buffer, "FPS: %d", fps);
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr, 10, 20, 0xFFFFFF, buffer);
}

// * Renders the player's current position coordinates on the game window
static void render_coordinates(t_game *game)
{
	char buffer[32];

	// Format the player's position into a string
	sprintf(buffer, "Pos: (%d, %d)", (int)game->player.pos.x, (int)game->player.pos.y);
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr, 10, 40, 0xFFFFFF, buffer);
}

// * Calculates the compass direction based on the player's angle
static const char *get_compass_dir(double angle)
{
	// Normalize the angle to [0, 360) range
	angle = fmod(angle, 360.0);
	if (angle < 0)
		angle += 360.0;

	if (angle >= 22.5 && angle < 67.5)
		return ("NE");
	else if (angle >= 67.5 && angle < 112.5)
		return ("E");
	else if (angle >= 112.5 && angle < 157.5)
		return ("SE");
	else if (angle >= 157.5 && angle < 202.5)
		return ("S");
	else if (angle >= 202.5 && angle < 247.5)
		return ("SW");
	else if (angle >= 247.5 && angle < 292.5)
		return ("W");
	else if (angle >= 292.5 && angle < 337.5)
		return ("NW");
	else
		return ("N");
}

// * Renders the compass direction based on the player's angle
static void render_compass(t_game *game)
{
	char buffer[32];
	double angle = atan2(game->player.dir.y, game->player.dir.x) * 180.0 / M_PI;
	const char *dir = get_compass_dir(angle);
	snprintf(buffer, sizeof(buffer), "Dir: %s (%.1f°)", dir, angle < 0 ? angle + 360 : angle);
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr, 10, 60, 0xFFFFFF, buffer);
}

// * Draws the HUD elements on the game window
void draw_hud(t_game *game)
{
	render_fps(game);
	render_coordinates(game);
	render_compass(game);
}
