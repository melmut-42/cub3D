#include "game.h"

// * Display texture file paths and RGB color values
static void display_texture(const t_texture *tex)
{
	printf("Textures:\n");
	printf("  NO: %s\n", tex->no_path);
	printf("  SO: %s\n", tex->so_path);
	printf("  WE: %s\n", tex->we_path);
	printf("  EA: %s\n", tex->ea_path);
	printf("  Ceiling RGB: [%d, %d, %d]\n",
		tex->ceil_rgb[0], tex->ceil_rgb[1], tex->ceil_rgb[2]);
	printf("  Floor   RGB: [%d, %d, %d]\n",
		tex->floor_rgb[0], tex->floor_rgb[1], tex->floor_rgb[2]);
}

// * Display map info alongside its matrix representation
static void display_map(const t_map *m)
{
	size_t	i;
	size_t	j;

	printf("Map:\n");
	printf("  Height: %zu\n", m->height);
	printf("  Path: %s\n", m->map_path);
	printf("  Matrix:\n");
	for (i = 0; i < m->height; i++)
	{
		for (j = 0; m->matrix[i][j]; j++)
		{
			if (is_space((unsigned char)m->matrix[i][j]))
				ft_putchar_fd('.', 1);
			else
				ft_putchar_fd(m->matrix[i][j], 1);
		}
		ft_putchar_fd('\n', 1);
	}
}

// * Convert direction enum to string
static const char *direction_to_str(t_directions dir)
{
	switch (dir)
	{
		case NORTH: return "NORTH";
		case SOUTH: return "SOUTH";
		case EAST:  return "EAST";
		case WEST:  return "WEST";
		case FLOOR: return "FLOOR";
		case CEILING: return "CEILING";
		default: return "NONE";
	}
}

// * Display player position and direction
static void display_player(const t_player *p)
{
	printf("Player:\n");
	printf("  Position: (%d, %d)\n", p->pos.x_axis, p->pos.y_axis);
	printf("  Direction: %s\n", direction_to_str(p->dir));
}

// * Display the combined game data (map & textures)
void display_data(const t_data *d)
{
	printf("--- Game Data ---\n");
	display_map(&d->map);
	display_texture(&d->texture);
}

// * Display overall game info including error flag and game data
void display_game(const t_game *g)
{
	printf("Game: %s\n", g->name);
	printf("Error flag: %s\n", g->error_flag ? "true" : "false");
	display_data(&g->data);
	display_player(&g->player);
}
