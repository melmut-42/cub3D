#include "game.h"
#include "bonus.h"

// * Renders the FPS counter on the game window
static void render_fps(t_game *game, int x, int y, int color)
{
	static t_ms	last_time = 0;
	static int	frame_count = 0;
	static int	fps = 0;
	char		buffer[16];
	t_ms		now;

	now = get_timestamp(game);
	frame_count++;

	// Update the FPS counter every second
	if (now - last_time >= 1000)
	{
		fps = frame_count;
		frame_count = 0;
		last_time = now;
	}

	// Format the FPS value into a string
	sprintf(buffer, "FPS: %d", fps);
	mlx_out_txt(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y, color, buffer);
}

// * Renders the player's current position coordinates on the game window
static void render_coordinates(t_game *game, int x, int y, int color)
{
	char	buffer[32];

	// Format the player's position into a string
	sprintf(buffer, "Pos: (%d, %d)", (int)game->player.pos.x, (int)game->player.pos.y);
	mlx_out_txt(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y, color, buffer);
}

// * Calculates the compass direction based on the player's angle
static const char *get_compass_dir(double angle)
{
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
static void	render_compass(t_game *game, int x, int y, int color)
{
	char		buffer[32];
	double		angle;
	double		display_angle;
	const char	*dir;

	// Calculate the angle in degrees
	angle = atan2(game->player.dir.y, game->player.dir.x) * 180.0 / M_PI;
	if (angle < 0)
		display_angle = angle + 360;
	else
		display_angle = angle;

	// Get the compass direction and format the output
	dir = get_compass_dir(angle);
	sprintf(buffer, "Dir: %s (%.1f%c)", dir, display_angle, 176);
	mlx_out_txt(game->mlx->mlx_ptr, game->mlx->win_ptr, x, y, color, buffer);
}

// * Draws the HUD elements on the game window
void draw_hud(t_game *game)
{
	render_fps(game, 10, 20, 0xFFFFFF);
	render_coordinates(game, 10, 40, 0xFFFFFF);
	render_compass(game, 10, 60, 0xFFFFFF);
}
