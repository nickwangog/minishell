/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_semicolon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:04:22 by bpierce           #+#    #+#             */
/*   Updated: 2018/02/25 18:02:27 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	n_cmds(t_mini *m)
{
	int	i;

	if (!m->line || !(i = -1))
		return (0);
	m->num_of_commands = 1;
	while (m->line[++i])
	{
		if (m->line[i] == '\'' || m->line[i] == '\"')
			i = move_to_next_index_with_char(m->line, i, m->line[i]);
		else if (m->line[i] == ';' && m->line[i + 1] == ';')
			return (dorfshell_error("parse error near `;;'"));
		else if (m->line[i] == ';')
			++m->num_of_commands;
	}
	return (m->num_of_commands);
}

static void	*free_strsplit(t_mini *m, int k)
{
	while (k > -1)
		free(m->cmds[k--]);
	free(m->cmds);
	m->cmds = NULL;
	return (NULL);
}

static int	set_initial_split(t_mini *m, int *i, int *k)
{
	if (!m->line || !(n_cmds(m)))
		return (0);
	if (!(m->cmds = (char **)malloc(sizeof(char *) * (m->num_of_commands + 1))))
		return (0);
	*i = -1;
	*k = -1;
	return (1);
}

/*
** split_by_semicolon:
**   - Splits several sets of commands into ';' seperated instructions
*/

char		**split_by_semicolon(t_mini *m)
{
	int		i;
	int		k;
	int		dist;
	char	*start;

	if (!(set_initial_split(m, &i, &k)) || !(start = m->line))
		return (NULL);
	while (++i || 1)
	{
		if (m->line[i] == '\'' || m->line[i] == '\"')
			i = move_to_next_index_with_char(m->line, i, m->line[i]);
		if (!m->line[i] || m->line[i] == ';')
		{
			dist = &m->line[i] - start;
			if (!(m->cmds[++k] = ft_strnew(dist)))
				return (free_strsplit(m, k));
			ft_strncpy(m->cmds[k], start, dist);
			start = m->line[i] ? &m->line[i + 1] : &m->line[i];
		}
		if (!m->line[i])
			break ;
	}
	m->cmds[m->num_of_commands] = NULL;
	return (m->cmds);
}
