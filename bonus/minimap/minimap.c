#include "game.h"

static void	put_tile_pixel(t_game *g, t_img *img, int dx, int dy);
static void	draw_pixel(t_img *img, int x, int y, int color);
static void	draw_minimap_tiles(t_game *g, t_img *img);
static void	draw_minimap_player(t_img *img);
static void	draw_minimap_rays(t_game *g, t_img *img);
static void	draw_minimap_ray(t_game *g, t_img *img, double angle);
static double	deg_to_rad(double deg);

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
	double	w_x = g->player.pos.x + dx * MINIMAP_SCALE;
	double	w_y = g->player.pos.y + dy * MINIMAP_SCALE;
	size_t		m_x = (size_t)w_x;
	size_t		m_y = (size_t)w_y;
	int		cx = MINIMAP_RADIUS;

	if (m_x < 0 || m_y < 0 || m_x >= g->data.map.width || m_y >= g->data.map.height)
		return ;
	if (g->data.map.matrix[m_y][m_x] == WALL)
		draw_pixel(img, cx + dx, cx + dy, 0x555555);
	else
		draw_pixel(img, cx + dx, cx + dy, 0x222222);
}

static void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
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
			draw_pixel(img, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_rays(t_game *g, t_img *img)
{
	int		i;
	double	start;
	double	step;
	double	angle;

	start = atan2(g->player.dir.y, g->player.dir.x)
		- deg_to_rad(MINIMAP_FOV / 2.0);
	step = deg_to_rad((double)MINIMAP_FOV / RAY_COUNT);
	i = 0;
	while (i < RAY_COUNT)
	{
		angle = start + i * step;
		draw_minimap_ray(g, img, angle);
		i++;
	}
}


static void	draw_minimap_ray(t_game *g, t_img *img, double angle)
{
	double	len;
	double	rx;
	double	ry;
	int		dx;
	int		dy;
	int		px;
	int		py;

	len = 0.0;
	while (len < RAY_MAX_LEN)
	{
		rx = g->player.pos.x + cos(angle) * len;
		ry = g->player.pos.y + sin(angle) * len;
		dx = (rx - g->player.pos.x) / MINIMAP_SCALE;
		dy = (ry - g->player.pos.y) / MINIMAP_SCALE;
		px = MINIMAP_RADIUS + dx;
		py = MINIMAP_RADIUS + dy;
		if (dx * dx + dy * dy > MINIMAP_RADIUS * MINIMAP_RADIUS)
			return ;
		draw_pixel(img, px, py, 0xAAAAAA);
		len += RAY_STEP_SIZE;
	}
}

double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}


