/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:15:48 by osancak           #+#    #+#             */
/*   Updated: 2026/01/06 18:14:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3d.h"

void	print_game_info(t_game *game);
int		draw_loop(t_game *game);
void	clear_image(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);
void	move_player(t_game *game);
void	init_player(t_game *game);
int		rgb_to_hex(t_color color);
void	draw_pixels(t_game *game, int x, t_draw *d);
int		get_texture_color(t_img *tex, int x, int y);
void	set_texture(t_game *g, t_ray *ray, t_draw *d);
void	calc_texture_x(t_game *g, t_ray *ray, float dist, t_draw *d);

#endif
