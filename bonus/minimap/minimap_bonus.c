#include "game.h"
#include "../../includes/bonus/minimap_bonus.h"

static void	put_tile_pixel(t_game *g, t_img *img, int dx, int dy);
static void	draw_minimap_tiles(t_game *g, t_img *img);
static void	draw_minimap_player(t_img *img);

void	draw_minimap(t_game *game)
{
	t_img	*img;

	img = &game->mlx->frame_img;
	draw_minimap_tiles(game, img);
	draw_minimap_rays(game, img);
	draw_minimap_player(img);
}

static void	put_tile_pixel(t_game *g, t_img *img, int dx, int dy)
{
	double	w_x;
	double	w_y;
	size_t	m_x;
	size_t	m_y;
	int		cx;

	w_x = g->player.pos.x + dx * MINIMAP_SCALE;
	w_y = g->player.pos.y + dy * MINIMAP_SCALE;
	m_x = (size_t)w_x;
	m_y = (size_t)w_y;
	cx = MINIMAP_RADIUS;
	if (m_x >= g->data.map.width || m_y >= g->data.map.height)
	{
		ft_put_pixel(img, cx + dx, cx + dy, 0x000000);
		return ;
	}
	if (g->data.map.matrix[m_y][m_x] == WALL)
		ft_put_pixel(img, cx + dx, cx + dy, 0x555555);
	else
		ft_put_pixel(img, cx + dx, cx + dy, 0x222222);
}


static void	draw_minimap_tiles(t_game *g, t_img *img)
{
	int	dx;
	int	dy;

	dy = -MINIMAP_RADIUS;
	while (dy <= MINIMAP_RADIUS)
	{
		dx = -MINIMAP_RADIUS;
		while (dx <= MINIMAP_RADIUS)
		{
			if (dx * dx + dy * dy <= MINIMAP_RADIUS * MINIMAP_RADIUS)
				put_tile_pixel(g, img, dx, dy);
			dx++;
		}
		dy++;
	}
}

static void	draw_minimap_player(t_img *img)
{
	int	x;
	int	y;

	y = MINIMAP_RADIUS - 1;
	while (y <= MINIMAP_RADIUS + 1)
	{
		x = MINIMAP_RADIUS - 1;
		while (x <= MINIMAP_RADIUS + 1)
		{
			ft_put_pixel(img, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}
