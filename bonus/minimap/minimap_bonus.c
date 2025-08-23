#include "game.h"
#include "bonus.h"

static void	put_tile_pixel(t_game *g, t_img *img, t_axis_int delta,
				t_axis_int offset);
static void	draw_minimap_tiles(t_game *g, t_img *img, t_axis_int offset);
static void	draw_minimap_player(t_img *img, t_axis_int offset);
static void	draw_door_in_minimap(t_game *g, t_img *img, t_axis_int *cor,
				t_axis_int *map);

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
		t_axis_int offset)
{
	t_axis		win;
	t_axis_int	map;
	t_axis_int	cor;
	int			center;
	size_t		row_len;

	win.x = g->player.pos.x + delta.x * MINIMAP_SCALE;
	win.y = g->player.pos.y + delta.y * MINIMAP_SCALE;
	map.x = (size_t)win.x;
	map.y = (size_t)win.y;
	center = MINIMAP_RADIUS;
	cor.x = offset.x + center + delta.x;
	cor.y = offset.y + center + delta.y;
	if ((size_t)map.y < g->data.map.height && map.y >= 0)
		row_len = ft_strlen(g->data.map.matrix[map.y]);
	else
		row_len = 0;
	if ((size_t)map.x >= row_len || (size_t)map.y >= g->data.map.height)
		ft_put_pixel(img, cor.x, cor.y, COLOR_BLACK);
	else if (g->data.map.matrix[map.y][map.x] == WALL)
		ft_put_pixel(img, cor.x, cor.y, COLOR_OFF_GREY);
	else if (g->data.map.matrix[map.y][map.x] == DOOR)
		draw_door_in_minimap(g, img, &cor, &map);
	else
		ft_put_pixel(img, cor.x, cor.y, COLOR_GREY);
}

static void	draw_door_in_minimap(t_game *g, t_img *img, t_axis_int *cor,
				t_axis_int *map)
{
	t_door	*door;

	door = get_the_door(g, map->x, map->y);
	if (!door)
		return ;
	if (door->open == 1.0)
		ft_put_pixel(img, cor->x, cor->y, COLOR_GREEN);
	else
		ft_put_pixel(img, cor->x, cor->y, COLOR_PINK);
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
