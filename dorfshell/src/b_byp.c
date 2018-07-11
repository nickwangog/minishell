/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_byp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 20:25:21 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/10 14:01:01 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		builtin_byp(t_mini *m)
{
	if (!m || !m->c)
		return (0);
	if (m->c[1])
		return (dorfshell_error("Too many args for byp to handle"));
	m->byp ^= 1;
	if (m->byp)
		ft_pflite("%sdorfshell: %s %s%s",
				IPURPLE,
				"You have enabled special privilege access",
				"to manipulate locked environmental variables!!!\n",
				COLOR_OFF);
	else
		ft_pflite("%sdorfshell: %s %s%s",
				IPURPLE,
				"You have disabled that special priviledge access",
				"I told you about before...\n",
				COLOR_OFF);
	return (1);
}
