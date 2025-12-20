/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:15:48 by osancak           #+#    #+#             */
/*   Updated: 2025/12/20 15:58:17 by hyakici          ###   ########.fr       */
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

#endif
