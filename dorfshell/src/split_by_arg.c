/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:04:22 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/06 20:56:39 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	**clear_quotes(t_mini *m)
{
	int		i;
	int		len;

	i = -1;
	while (m->c[++i])
	{
		if (m->c[i][0] && (m->c[i][0] == '\'' || m->c[i][0] == '\"'))
		{
			len = ft_strlen(&m->c[i][1]) - 1;
			ft_memcpy(m->c[i], &m->c[i][1], len);
			m->c[i][len] = '\0';
		}
	}
	return (m->c);
}

static int	n_c(t_mini *m, char *s)
{
	int	i;

	if (!s || (i = 0))
		return (0);
	m->num_of_c = 0;
	while (s[i])
	{
		if (!ft_iswhitespace(s[i]) && ++m->num_of_c)
		{
			while (s[i] && !ft_iswhitespace(s[i]))
			{
				if (IS_QUOTE)
					i = move_to_next_index_with_char(s, i, s[i]) + 1;
				else if (s[i] && !ft_iswhitespace(s[i]))
					++i;
			}
		}
		else
			++i;
	}
	return (m->num_of_c);
}

static void	*free_strsplit(t_mini *m, int k)
{
	while (k > -1)
		free(m->c[k--]);
	free(m->c);
	m->c = NULL;
	return (NULL);
}

static int	set_initial_split(t_mini *m, char *s, int *i, int *k)
{
	if (!s || !(n_c(m, s)))
		return (0);
	if (!(m->c = (char **)malloc(sizeof(char *) * (m->num_of_c + 1))))
		return (0);
	*i = 0;
	*k = -1;
	return (1);
}

/*
** split_by_arg:
**   - Splits one command set into argument-seperated instructions
*/

char		**split_by_arg(t_mini *m, char *s)
{
	int		i;
	int		k;
	char	*start;

	if (!(set_initial_split(m, s, &i, &k)))
		return (NULL);
	while (s[i])
	{
		if (!ft_iswhitespace(s[i]) && (start = &s[i]))
		{
			while (s[i] && !ft_iswhitespace(s[i]))
			{
				if (IS_QUOTE)
					i = move_to_next_index_with_char(s, i, s[i]) + 1;
				else if (s[i] && !ft_iswhitespace(s[i]))
					++i;
			}
			if (!(m->c[++k] = ft_strnew(&s[i] - start)))
				return (free_strsplit(m, k));
			ft_strncpy(m->c[k], start, &s[i] - start);
		}
		else
			++i;
	}
	return ((m->c[m->num_of_c] = NULL) ? NULL : clear_quotes(m));
}
