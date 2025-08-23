#include "game.h"
#include "bonus.h"

static void	render_fps(t_game *game, int x, int y, int color)
{
	static t_ms	last_time = 0;
	static int	frame_count = 0;
	static int	fps = 0;
	char		buffer[16];
	t_ms		now;

	(void)color;
	now = get_timestamp(game);
	frame_count++;
	if (now - last_time >= 1000)
	{
		fps = frame_count;
		frame_count = 0;
		last_time = now;
	}
	sprintf(buffer, "FPS: %d", fps);
	mlx_out_txt(game, x, y, buffer);
}

static void	render_coordinates(t_game *game, int x, int y, int color)
{
	char	buffer[32];

	(void)color;
	sprintf(buffer, "Pos: (%d, %d)", (int)game->player.pos.x,
		(int)game->player.pos.y);
	mlx_out_txt(game, x, y, buffer);
}

static const char	*get_compass_dir(double angle)
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

static void	render_compass(t_game *game, int x, int y, int color)
{
	char		buffer[32];
	double		angle;
	double		display_angle;
	const char	*dir;

	(void)color;
	angle = atan2(game->player.dir.y, game->player.dir.x) * 180.0 / M_PI;
	if (angle < 0)
		display_angle = angle + 360;
	else
		display_angle = angle;
	dir = get_compass_dir(angle);
	sprintf(buffer, "Dir: %s (%.1f%c)", dir, display_angle, 176);
	mlx_out_txt(game, x, y, buffer);
}

void	draw_hud(t_game *game)
{
	render_fps(game, 10, 20, COLOR_WHITE);
	render_coordinates(game, 10, 40, COLOR_WHITE);
	render_compass(game, 10, 60, COLOR_WHITE);
}
