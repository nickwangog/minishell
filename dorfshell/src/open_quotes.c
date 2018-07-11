/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 21:31:47 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/11 18:16:53 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	has_unreconciled_quotes(t_mini *m)
{
	int	i;
	int	q;

	i = -1;
	while (m->tmp[++i])
	{
		if ((m->tmp[i] == '\'' || m->tmp[i] == '\"'))
		{
			q = m->tmp[i];
			i = move_to_next_index_with_char(m->tmp, i, m->tmp[i]);
			if (!m->tmp[i])
				return (q);
		}
	}
	return (0);
}

int			check_for_open_quotes(t_mini *m)
{
	int		q;

	if (!m->line)
		return (0);
	m->tmp = m->line;
	m->line = NULL;
	while ((q = has_unreconciled_quotes(m)))
	{
		ft_putstr(q == '\'' ? SHELL_Q_QUOTE : SHELL_D_QUOTE);
		if (!(m->line = get_input()))
			return (dorfshell_error("Error on input read"));
		if (!(m->tmp = ft_strffjoin(&m->tmp, &m->line)))
			return (dorfshell_error("Failed to join m->line to m->tmp"));
	}
	m->line = ft_trim(m->tmp);
	m->tmp = NULL;
	return (1);
}
