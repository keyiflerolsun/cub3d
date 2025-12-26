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

int rgb_to_hex(t_color color)
{
    return ((color.r << 16) | (color.g << 8) | color.b);
}

int	get_texture_color(t_img *tex, int x, int y)
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
	return (*(int *)dst);
}

void	draw_pixels(t_game *game, int x, t_draw *d)
{
	int	y;
	int	color;
	int	pcolor;
	
	pcolor = rgb_to_hex(game->ceiling);
	y = -1;
	while (++y < d->start)
		put_pixel(x, y, pcolor, game);
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
	pcolor = rgb_to_hex(game->floor);
	while (++y < HEIGHT)
		put_pixel(x, y, pcolor, game);
}

void	set_texture(t_game *g, t_ray *ray, t_draw *d)
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

void	calc_texture_x(t_game *g, t_ray *ray, float dist, t_draw *d)
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
