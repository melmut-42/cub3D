#include "game.h"

t_img  *get_wall_texture(t_game *g, t_ray *ray)
{
    if (ray->side == 0 && ray->dir.x > 0)
        return (&g->data.texture.textures[EAST]);
    if (ray->side == 0 && ray->dir.x < 0)
        return (&g->data.texture.textures[WEST]);
    if (ray->side == 1 && ray->dir.y > 0)
        return (&g->data.texture.textures[SOUTH]);
    return (&g->data.texture.textures[NORTH]);
}

int     get_texture_x(t_game *g, t_ray *ray, t_img *tex)
{
    double wall_x;
    int    tex_x;

    if (ray->side == 0)
        wall_x = g->player.pos.y + ray->perp_wall_dist * ray->dir.y;
    else
        wall_x = g->player.pos.x + ray->perp_wall_dist * ray->dir.x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (double)tex->width);
    if ((ray->side == 0 && ray->dir.x < 0)
     || (ray->side == 1 && ray->dir.y > 0))
        tex_x = tex->width - tex_x - 1;
    return (tex_x);
}


static void init_column(t_column *col, t_game *g, t_ray *ray, int x)
{
    int win_h;
    int pitch;

    win_h = g->mlx->height;
    col->wall_height = (int)(win_h / ray->perp_wall_dist);
	// ! Use pitch-adjusted screen center
    pitch = (int)(g->player.pitch_angle
                    + g->player.vertical.jump_offset
                    - g->player.vertical.crouch_offset);
    col->pixel_top = (win_h - col->wall_height) / 2 + pitch;
    if (col->pixel_top < 0)
        col->pixel_top = 0;
    col->pixel_bottom = (win_h + col->wall_height) / 2 + pitch;
    if (col->pixel_bottom >= win_h)
        col->pixel_bottom = win_h - 1;
    col->texture = get_wall_texture(g, ray);
    col->texture_x = get_texture_x(g, ray, col->texture);
    col->screen_x = x;
}

static void draw_ceiling(t_game *g, t_column *col, int color)
{
    int y;

    y = 0;
    while (y < col->pixel_top)
        ft_put_pixel(&g->mlx->frame_img, col->screen_x, y++, color);
}

static void draw_floor(t_game *g, t_column *col, int color)
{
    int y;
    int win_h;

    win_h = g->mlx->height;
    y = col->pixel_bottom + 1;
    while (y < win_h)
        ft_put_pixel(&g->mlx->frame_img, col->screen_x, y++, color);
}

static void draw_wall(t_game *g, t_column *col)
{
    int           y;
    int           center;
    double        step;
    double        tex_pos;
    int           tex_y;

    /* combine camera look, jump rise and crouch drop */
    center = g->mlx->height / 2
           + (int)g->player.pitch_angle
           + (int)g->player.vertical.jump_offset   /* upward shift */
           - (int)g->player.vertical.crouch_offset;/* downward shift */

    step    = (double)col->texture->height / col->wall_height;
    tex_pos = (col->pixel_top - center + col->wall_height / 2) * step;
    y       = col->pixel_top;
    while (y <= col->pixel_bottom)
    {
        if (tex_pos >= 0.0 && tex_pos < col->texture->height)
        {
            tex_y = (int)tex_pos;
            ft_put_pixel(&g->mlx->frame_img,
                         col->screen_x,
                         y,
                         *(unsigned int *)(col->texture->addr
                           + tex_y * col->texture->line_len
                           + col->texture_x * (col->texture->bpp / 8)));
        }
        tex_pos += step;
        y++;
    }
}



void draw_column(t_game *g, t_ray *ray, int x)
{
    t_column col;
    int       ceil_col;
    int       floor_col;

    init_column(&col, g, ray, x);
    ceil_col = rgb_to_int(
        g->data.texture.ceil_rgb[0],
        g->data.texture.ceil_rgb[1],
        g->data.texture.ceil_rgb[2]);
    floor_col = rgb_to_int(
        g->data.texture.floor_rgb[0],
        g->data.texture.floor_rgb[1],
        g->data.texture.floor_rgb[2]);
    draw_ceiling(g, &col, ceil_col);
    draw_wall(g, &col);
    draw_floor(g, &col, floor_col);
}
