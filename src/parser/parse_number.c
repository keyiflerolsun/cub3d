/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:16:05 by osancak           #+#    #+#             */
/*   Updated: 2025/12/18 10:29:47 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*skip_spaces(char *str)
{
	while (*str && ft_strchr(" \t", *str))
		str++;
	return (str);
}

int	parse_number(char **ptr)
{
	int	num;

	*ptr = skip_spaces(*ptr);
	num = 0;
	while (**ptr && ft_strchr("0123456789", **ptr))
	{
		num = num * 10 + (**ptr - '0');
		(*ptr)++;
	}
	return (num);
}
