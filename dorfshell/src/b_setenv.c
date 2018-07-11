/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 17:59:54 by bpierce           #+#    #+#             */
/*   Updated: 2018/01/29 20:42:47 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		builtin_setenv2(t_mini *m, int e, int i)
{
	char	*n;
	char	*r;
	char	*t;

	n = ft_strsub(m->c[1], 0, e);
	n = ft_strfremovequotes(&n);
	r = ft_strsub(m->c[1], e + 1, i);
	r = ft_strfremovequotes(&r);
	if (!n || !r)
	{
		free(n);
		free(r);
		return (dorfshell_error("Failed to setenv"));
	}
	t = set_env_var(m, n, r, 0);
	free(n);
	free(r);
	return (t ? 1 : 0);
}

int				builtin_setenv(t_mini *m)
{
	int		i;
	int		e;

	if (!m || !m->c[1])
		return (dorfshell_error("what would you like to set?"));
	if (m->c[2])
		return (dorfshell_error("too many args for setenv"));
	if (m->c[1][0] == '=')
		return (dorfshell_error("Env var name could not be found"));
	e = ft_strccountto(m->c[1], '=');
	if (!m->c[1][e])
		return (dorfshell_error("add an '=' sign to set env var"));
	if (!m->c[1][e + 1])
		return (dorfshell_error("plz declare sthg for setenv"));
	if (ft_iswhitespace(m->c[1][e + 1]) || (i = 0))
		return (dorfshell_error("no whitespace after the '=' plz"));
	while (m->c[1][e + i])
		i = (m->c[1][e + i] == '\"' || m->c[1][e + i] == '\'') ?
			move_to_next_index_with_char(m->c[1], e + i, m->c[1][i]) - e : ++i;
	return (builtin_setenv2(m, e, i));
}
