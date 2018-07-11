/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_and.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:04:22 by bpierce           #+#    #+#             */
/*   Updated: 2018/01/27 20:55:12 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	n_cmd(t_mini *m, char *s)
{
	int	i;

	if (!s || !(i = -1))
		return (0);
	m->num_of_cmd = 1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = move_to_next_index_with_char(s, i, s[i]);
		else if (s[i] == '&')
		{
			if (s[i + 1] == '&')
				if (s[i + 2] == '&')
					return (dorfshell_error("parse error near `&&'"));
			i += s[i + 1] == '&' ? 1 : 0;
			++m->num_of_cmd;
		}
	}
	return (m->num_of_cmd);
}

static void	*free_strsplit(t_mini *m, int last)
{
	while (last > -1)
		free(m->cmd[last--]);
	free(m->cmd);
	m->cmd = NULL;
	return (dorfshell_null("Failed to free strsplit for some reason"));
}

static int	set_initial_split(t_mini *m, char *s, int *i, int *k)
{
	if (!s || !(n_cmd(m, s)))
		return (0);
	if (!(m->cmd = (char **)malloc(sizeof(char *) * (m->num_of_cmd + 1))))
		return (dorfshell_error("Malloc for m->cmd failed"));
	*i = -1;
	*k = -1;
	return (1);
}

/*
** split_by_and:
**   - Splits single command set into '&' or '&&' seperated instructions
*/

char		**split_by_and(t_mini *m, char *s)
{
	int		i;
	int		k;
	char	*start;

	if (!(set_initial_split(m, s, &i, &k)) || !(start = s))
		return (NULL);
	while (++i || 1)
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = move_to_next_index_with_char(s, i, s[i]);
		if (s[i] == '&' || !s[i])
		{
			if (!(m->cmd[++k] = ft_strnew(&s[i] - start)))
				return (free_strsplit(m, k));
			ft_strncpy(m->cmd[k], start, &s[i] - start);
			i += s[i + 1] == '&' ? 1 : 0;
			start = &s[i + 1];
		}
		if (!s[i])
			break ;
	}
	m->cmd[m->num_of_cmd] = NULL;
	return (m->cmd);
}
