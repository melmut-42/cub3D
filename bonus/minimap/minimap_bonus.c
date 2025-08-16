#include "game.h"
#include "bonus.h"

static void	put_tile_pixel(t_game *g, t_img *img, t_axis_int delta,
				t_axis_int offset);
static void	draw_minimap_tiles(t_game *g, t_img *img, t_axis_int offset);
static void	draw_minimap_player(t_img *img, t_axis_int offset);

void	draw_minimap(t_game *g)
{
	t_img		*img;
	t_axis_int	offset;

	img = &g->mlx->frame_img;
	offset.x = WIN_WIDTH - (MINIMAP_RADIUS * 2 + 1) - 10;
	offset.y = 10;
	draw_minimap_tiles(g, img, offset);
	draw_minimap_rays(g, img, offset);
	draw_minimap_player(img, offset);
}

static void	put_tile_pixel(t_game *g, t_img *img, t_axis_int delta,
		t_axis_int o)
{
	t_axis		win;
	size_t		m_x;
	size_t		m_y;
	t_axis_int	p;
	int			c;
	t_door		*door;

	win.x = g->player.pos.x + delta.x * MINIMAP_SCALE;
	win.y = g->player.pos.y + delta.y * MINIMAP_SCALE;
	m_x = (size_t)win.x;
	m_y = (size_t)win.y;
	c = MINIMAP_RADIUS;
	p.x = o.x + c + delta.x;
	p.y = o.y + c + delta.y;
	if (m_x >= g->data.map.width || m_y >= g->data.map.height)
		ft_put_pixel(img, p.x, p.y, 0x000000);
	else if (g->data.map.matrix[m_y][m_x] == WALL)
		ft_put_pixel(img, p.x, p.y, 0x555555);
	else if (g->data.map.matrix[m_y][m_x] == DOOR)
	{
		door = find_door(g, m_x, m_y);
		if (door && door->open >= 1.0)
			ft_put_pixel(img, p.x, p.y, 0x0000FF);
		else
			ft_put_pixel(img, p.x, p.y, 0x00FF00);
	}
	else
		ft_put_pixel(img, p.x, p.y, 0x222222);
}

static void	draw_minimap_tiles(t_game *g, t_img *img, t_axis_int offset)
{
	t_axis_int	d;

	d.y = -MINIMAP_RADIUS;
	while (d.y <= MINIMAP_RADIUS)
	{
		d.x = -MINIMAP_RADIUS;
		while (d.x <= MINIMAP_RADIUS)
		{
			if (d.x * d.x + d.y * d.y <= MINIMAP_RADIUS * MINIMAP_RADIUS)
				put_tile_pixel(g, img, d, offset);
			d.x++;
		}
		d.y++;
	}
}

static void	draw_minimap_player(t_img *img, t_axis_int offset)
{
	t_axis_int	p;
	int			half;

	half = MINIMAP_PLAYER_SIZE / 2;
	p.y = MINIMAP_RADIUS - half;
	while (p.y <= MINIMAP_RADIUS + half)
	{
		p.x = MINIMAP_RADIUS - half;
		while (p.x <= MINIMAP_RADIUS + half)
		{
			ft_put_pixel(img, offset.x + p.x, offset.y + p.y, 0xFF0000);
			p.x++;
		}
		p.y++;
	}
}
