#include "game.h"

static void	print_rgb(const char *label, const int rgb[RGB_CONSTANT])
{
	printf("  %s RGB: [%d, %d, %d]\n", label, rgb[0], rgb[1], rgb[2]);
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
	printf("  Height: %zu\n", m->height);
	printf("  Width: %zu\n", m->width);
	printf("  Path: %s\n", m->map_path);
	printf("  Matrix:\n");
	for (i = 0; i < m->height; i++)
	{
		for (j = 0; m->matrix[i][j]; j++)
		{
			if (ft_strchr(SPACE_SET, m->matrix[i][j]))
				ft_putchar_fd('.', 1);
			else
				ft_putchar_fd(m->matrix[i][j], 1);
		}
		ft_putchar_fd('\n', 1);
	}
}

static void	display_axis(const char *label, const t_axis *a)
{
	printf("  %s: (%.2f, %.2f)\n", label, a->x, a->y);
}

static void	display_player(const t_player *p)
{
	printf("Player:\n");
	display_axis("Position", &p->pos);
	display_axis("Direction", &p->dir);
	display_axis("Plane", &p->plane);
	display_axis("Rotation", &p->rot);
	display_axis("Sensitivity", &p->sens);
	printf("  Pitch Angle: %.2f\n", p->pitch_angle);
	printf("  Movement Speed: %.2f\n", p->mov_speed);
	printf("  Move Flags: W[%d] A[%d] S[%d] D[%d]\n",
		p->mov_up, p->mov_left, p->mov_down, p->mov_right);
}

static void	display_mlx(const t_mlx *mlx)
{
	if (!mlx)
	{
		printf("MLX: NULL\n");
		return ;
	}
	printf("MLX:\n");
	printf("  Title: %s\n", mlx->title);
	printf("  Size: %dx%d\n", mlx->width, mlx->height);
	printf("  MLX ptr: %p\n", mlx->mlx_ptr);
	printf("  WIN ptr: %p\n", mlx->win_ptr);
}

void	display_game(const t_game *g)
{
	if (!g)
		return ;
	printf("======= GAME DEBUG =======\n");
	printf("Game: %s\n", g->name);
	printf("Error flag: %s\n", g->error_flag ? "true" : "false");
	display_map(&g->data.map);
	display_texture(&g->data.texture);
	display_player(&g->player);
	display_mlx(g->mlx);
	printf("==========================\n");
}
