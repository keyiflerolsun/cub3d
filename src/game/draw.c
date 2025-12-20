/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:10:57 by hyakici           #+#    #+#             */
/*   Updated: 2025/12/20 15:58:15 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	init_ray(t_ray *ray, t_game *game, float angle)
{
	ray->map_x = (int)(game->player.x / BLOCK_SIZE);
	ray->map_y = (int)(game->player.y / BLOCK_SIZE);
	ray->delta_x = fabs(1 / cosf(angle));
	ray->delta_y = fabs(1 / sinf(angle));
	ray->step_x = 1;
	ray->side_x = (ray->map_x + 1.0 - game->player.x / BLOCK_SIZE)
		* ray->delta_x;
	if (cosf(angle) < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.x / BLOCK_SIZE - ray->map_x) * ray->delta_x;
	}
	ray->step_y = 1;
	ray->side_y = (ray->map_y + 1.0 - game->player.y / BLOCK_SIZE)
		* ray->delta_y;
	if (sinf(angle) < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.y / BLOCK_SIZE - ray->map_y) * ray->delta_y;
	}
}

static float	get_dda_dist(t_game *game, float angle, t_ray *ray)
{
	int	hit;

	init_ray(ray, game, angle);
	hit = 0;
	while (hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= 10 || ray->map_x < 0
			|| ray->map_x >= 15
			|| game->map.full[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		return ((ray->side_x - ray->delta_x) * BLOCK_SIZE);
	return ((ray->side_y - ray->delta_y) * BLOCK_SIZE);
}

static unsigned int	get_texture_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	dst = tex->addr + (y * tex->row_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	set_texture(t_game *g, t_ray *ray, t_draw *d)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			d->tex = &g->east_wall;
		else
			d->tex = &g->west_wall;
	}
	else
	{
		if (ray->step_y > 0)
			d->tex = &g->south_wall;
		else
			d->tex = &g->north_wall;
	}
}

static void	calc_texture_x(t_game *g, t_ray *ray, float dist, t_draw *d)
{
	float	wall_x;

	set_texture(g, ray, d);
	if (ray->side == 0)
		wall_x = g->player.y + dist * sinf(d->angle);
	else
		wall_x = g->player.x + dist * cosf(d->angle);
	wall_x /= BLOCK_SIZE;
	wall_x -= floor(wall_x);
	d->tex_x = (int)(wall_x * (float)d->tex->width);
	if ((ray->side == 0 && ray->step_x > 0) || (ray->side == 1
			&& ray->step_y < 0))
		d->tex_x = d->tex->width - d->tex_x - 1;
}

static void	draw_pixels(t_game *game, int x, t_draw *d)
{
	int	y;
	int	color;

	y = -1;
	while (++y < d->start)
		put_pixel(x, y, 0x87CEEB, game);
	y = d->start;
	while (y < d->end && y < HEIGHT)
	{
		d->tex_y = (int)d->tex_pos % d->tex->height;
		d->tex_pos += d->step;
		color = get_texture_color(d->tex, d->tex_x, d->tex_y);
		put_pixel(x, y, color, game);
		y++;
	}
	y--;
	while (++y < HEIGHT)
		put_pixel(x, y, 0x444444, game);
}

static void	draw_one_col(t_game *game, int x, float r_angle, float fov)
{
	t_ray	ray;
	t_draw	d;
	float	raw_dist;
	float	fix_dist;

	raw_dist = get_dda_dist(game, r_angle, &ray);
	fix_dist = raw_dist * cosf(r_angle - game->player.rotation);
	d.wall_h = (BLOCK_SIZE / fix_dist) * ((WIDTH / 2) / tanf(fov / 2));
	d.start = (HEIGHT / 2) - (d.wall_h / 2);
	d.end = (HEIGHT / 2) + (d.wall_h / 2);
	d.angle = r_angle;
	calc_texture_x(game, &ray, raw_dist, &d);
	d.step = d.tex->height / d.wall_h;
	d.tex_pos = (d.start - HEIGHT / 2 + d.wall_h / 2) * d.step;
	if (d.start < 0)
	{
		d.tex_pos += -d.start * d.step;
		d.start = 0;
	}
	draw_pixels(game, x, &d);
}

int	draw_loop(t_game *game)
{
	int		x;
	float	fov;
	float	fov_half;
	float	ray_angle;
	float	cam_x;

	move_player(game);
	clear_image(game);
	fov = 60 * (P / 180);
	fov_half = tan(fov / 2);
	x = 0;
	while (x < WIDTH)
	{
		cam_x = 2.0 * x / (float)WIDTH - 1.0;
		ray_angle = game->player.rotation + atanf(cam_x * fov_half);
		draw_one_col(game, x, ray_angle, fov);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
