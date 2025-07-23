#include "game.h"

// ! Norm compliance doesn't matter, this file is for debugging only and will be removed in production.

static void	display_axis(const char *label, const t_axis *a)
{
	printf("  %-12s: (%.2f, %.2f)\n", label, a->x, a->y);
}

static void	print_rgb(const char *label, const int rgb[RGB_CONSTANT])
{
	printf("  %-12s RGB: [%3d, %3d, %3d]\n", label, rgb[0], rgb[1], rgb[2]);
}

static void	display_img(const char *label, const t_img *img)
{
	if (!img || !img->img_ptr)
	{
		printf("  %s: NULL\n", label);
		return ;
	}
	printf("  %s:\n", label);
	printf("    Ptr     : %p\n", img->img_ptr);
	printf("    Addr    : %p\n", img->addr);
	printf("    BPP     : %d\n", img->bpp);
	printf("    Endian  : %d\n", img->endian);
	printf("    LineLen : %d\n", img->line_len);
	printf("    Size    : %dx%d\n", img->width, img->height);
}

static void	display_texture(const t_texture *tex)
{
	printf("Textures:\n");
	printf("  NO: %s\n", tex->no_path);
	printf("  SO: %s\n", tex->so_path);
	printf("  WE: %s\n", tex->we_path);
	printf("  EA: %s\n", tex->ea_path);
	print_rgb("Ceiling", tex->ceil_rgb);
	print_rgb("Floor", tex->floor_rgb);
}

static void	display_map(const t_map *m)
{
	size_t	i;
	size_t	j;

	printf("Map:\n");
	printf("  Height : %zu\n", m->height);
	printf("  Width  : %zu\n", m->width);
	printf("  Path   : %s\n", m->map_path);
	printf("  Matrix :\n");
	i = 0;
	while (m->matrix[i])
	{
		j = 0;
		while (m->matrix[i][j])
		{
			if (ft_strchr(SPACE_SET, m->matrix[i][j]))
				ft_putchar_fd('.', 1);
			else
				ft_putchar_fd(m->matrix[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

static void	display_player(const t_player *p)
{
	printf("Player:\n");
	display_axis("Position", &p->pos);
	display_axis("Direction", &p->dir);
	display_axis("Plane", &p->plane);
	display_axis("Rotation", &p->rot);
	display_axis("Sensitivity", &p->sens);
	printf("  Pitch       : %.2f\n", p->pitch_angle);
	printf("  Move Speed  : %.2f\n", p->mov_speed);
	printf("  Move Flags  : W[%d] A[%d] S[%d] D[%d]\n",
		p->movement[W], p->movement[A], p->movement[S], p->movement[D]);
}

static void	display_mlx(const t_mlx *mlx)
{
	printf("MLX:\n");
	if (!mlx)
	{
		printf("  NULL\n");
		return ;
	}
	printf("  Title   : %s\n", mlx->title);
	printf("  Size    : %dx%d\n", mlx->width, mlx->height);
	printf("  MLX ptr : %p\n", mlx->mlx_ptr);
	printf("  WIN ptr : %p\n", mlx->win_ptr);
	display_img("  Frame Img", &mlx->frame_img);
	display_img("  Minimap", &mlx->minimap_img);
}

void	display_game(const t_game *g)
{
	if (!g)
		return ;
	printf("======= GAME DEBUG =======\n");
	printf("Game Name   : %s\n", g->name);
	printf("Error Flag  : %s\n", g->error_flag ? "true" : "false");
	printf("Last Update : %lu ms\n", g->last_update);
	display_map(&g->data.map);
	display_texture(&g->data.texture);
	display_player(&g->player);
	display_mlx(g->mlx);
	printf("==========================\n");
}
