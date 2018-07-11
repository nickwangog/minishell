/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_environmental_variables.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 13:34:39 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/11 19:40:35 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	join_environmental_variable_to_newline(t_mini *m, int *i)
{
	char	*env;
	char	buf[2];

	if (!(m->cwd = ft_strnew(0)))
		return (dorfshell_error("why u no work"));
	buf[1] = '\0';
	while (m->line[++(*i)] && !CE_4(ML[*i], '$', '=', '\"', '\'') &&
			!ft_iswhitespace(ML[*i]))
	{
		if (ML[*i] == '\\' && ML[(*i) + 1] == '$' && ++(*i))
		{
			if (!(m->cwd = ft_strfjoin(&m->cwd, "$")))
				return (dorfshell_error("Failed to join '$'"));
		}
		else if ((buf[0] = ML[*i]))
			if (!(m->cwd = ft_strfjoin(&m->cwd, buf)))
				return (dorfshell_error("Could not join var name"));
	}
	--(*i);
	env = get_env_var(m, m->cwd, 0);
	ft_strdel(&m->cwd);
	if (env && !(m->newline = ft_strfjoin(&m->newline, env)))
		return (dorfshell_error("WHYYY"));
	return (1);
}

static int	look_for_environmental_variables(t_mini *m, char *buf, int i)
{
	while (ML[++i])
	{
		buf[0] = '\0';
		if (ML[i] == '$' && ML[(i) + 1] == '$' && ++(i))
		{
			if (!(m->cwd = ft_itoa(getpid())))
				return (dorfshell_error("Failed to get pid"));
			if (!(m->newline = ft_strffjoin(&m->newline, &m->cwd)))
				return (dorfshell_error("Failed to get pid"));
		}
		else if (ML[i] == '\\' && ML[(i) + 1] == '$' && ++(i))
			buf[0] = '$';
		else if (ML[i] == '$' && ML[(i) + 1] && !ft_iswhitespace(ML[(i) + 1]))
		{
			if (!(join_environmental_variable_to_newline(m, &i)))
				return (dorfshell_error("Failed to join env var to newline"));
		}
		else
			buf[0] = ML[i];
		if (buf[0] && !(m->newline = ft_strfjoin(&m->newline, buf)))
			return (dorfshell_error("Failed to expand env variables"));
	}
	return (1);
}

int			expand_environmental_variables(t_mini *m)
{
	int		i;
	char	buf[2];

	if (!ML || !(i = -1))
		return (0);
	buf[1] = '\0';
	if (!(m->newline = ft_strnew(0)))
		return (dorfshell_error("why did this step fail!?!?!?"));
	if (!(look_for_environmental_variables(m, buf, i)))
		return (0);
	free(m->line);
	m->line = m->newline;
	m->newline = NULL;
	return (1);
}
