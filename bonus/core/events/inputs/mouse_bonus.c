#include "game.h"
#include "bonus.h"

static void	update_rot_angles(t_player *player, int delta_x, int delta_y);

int	handle_mouse(int x, int y, t_game *game)
{
	int	dx;
	int	dy;

	dx = x - MID_POINT_X;
	dy = y - MID_POINT_Y;
	if (dx != 0 || dy != 0)
	{
		update_rot_angles(&game->player, dx, dy);
		mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->win_ptr,
			MID_POINT_X, MID_POINT_Y);
	}
	return (0);
}

static void	update_rot_angles(t_player *player, int delta_x, int delta_y)
{
	if (delta_y > MAX_VERTICAL_DELTA)
		delta_y = MAX_VERTICAL_DELTA;
	if (delta_y < -MAX_VERTICAL_DELTA)
		delta_y = -MAX_VERTICAL_DELTA;
	player->rot.x = delta_x * player->sens.x;
	player->pitch_angle -= delta_y * player->sens.y;
	if (player->pitch_angle > MAX_PITCH)
		player->pitch_angle = MAX_PITCH;
	if (player->pitch_angle < MIN_PITCH)
		player->pitch_angle = MIN_PITCH;
}
