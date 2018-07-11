/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 19:56:20 by bpierce           #+#    #+#             */
/*   Updated: 2018/02/13 19:27:19 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
** move_to_next_index_with_char:
**   - Given index of i in string s, returns the index of the next found char c
**   - Ignores any backslashed '\' characters equal to that of the given char c
**   - Will return the index of '\0' if the end of string s is reached
*/

int		move_to_next_index_with_char(char *s, int i, char c)
{
	i += 1;
	while (s[i])
	{
		if (s[i] == '\\')
			i += (s[i + 1] && s[i + 1] == c) ? 2 : 1;
		else if (s[i] == c)
			return (i);
		else
			++i;
	}
	return (i);
}
