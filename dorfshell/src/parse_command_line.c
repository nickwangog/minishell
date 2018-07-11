/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:45:54 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/11 19:36:04 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		is_relative_path(t_mini *m)
{
	int		len;

	if (!m->c[0])
		return (0);
	if (m->c[0][0] == '/')
		return (1);
	if (!(len = ft_strlen(m->c[0])))
		return (0);
	while (len > 0)
		if (m->c[0][--len] == '/')
			return (1);
	return (0);
}

int		is_valid_builtin_command(t_mini *m)
{
	return (ft_strequ("exit", m->c[0]) ||
			ft_strequ("env", m->c[0]) ||
			ft_strequ("setenv", m->c[0]) ||
			ft_strequ("unsetenv", m->c[0]) ||
			ft_strequ("cd", m->c[0]) ||
			ft_strequ("echo", m->c[0]) ||
			ft_strequ("byp", m->c[0]));
}

int		is_valid_executable_command(t_mini *m)
{
	char		*path;
	int			i;
	struct stat	pstat;

	if (!m->c[0])
		return (0);
	if ((i = -1) && is_relative_path(m))
	{
		if (!(m->tmp = ft_strdup(m->c[0])))
			return (dorfshell_error("Failed to duplicate the path"));
		return (stat(m->tmp, &pstat) != -1 ? S_ISREG(pstat.st_mode) : 0);
	}
	else if (!(path = get_env_var(m, "PATH", 0)))
		return (dorfshell_error("Failed to find \"PATH\""));
	if (!(m->temp = ft_strsplit(path, ':')))
		return (dorfshell_error("No paths exist... ????"));
	while (m->temp[++i])
	{
		if (!(m->tmp = ft_sandwichjoin(m->temp[i], m->c[0], "/")))
			return (dorfshell_error("Join failed m->temp[i] and c"));
		if (stat(m->tmp, &pstat) != -1)
			return (1);
		ft_strdel(&m->tmp);
	}
	return (0);
}

/*
** free_on_complete:
**   - Can be called anytime validation fails, all processes complete,
**   malloc errors occur, etc...
**   Intended to be used for freeing data between different user inputs
**   into minishell
*/

int		free_on_complete(t_mini *m, char *error_message)
{
	ft_arraydel(&m->cmds);
	ft_arraydel(&m->cmd);
	ft_arraydel(&m->c);
	ft_arraydel(&m->temp);
	ft_strdel(&m->line);
	ft_strdel(&m->newline);
	ft_strdel(&m->tmp);
	ft_strdel(&m->cwd);
	return (dorfshell_error(error_message));
}

/*
** parse_command_line:
**   - First, properly closes any unresolved quotes
**   - m->line is set to a malloc'd string, so must be freed later
**   - Second, splits the given single command into ';'-separated command sets,
**     and stores it in m->cmds
*/

int		parse_command_line(t_mini *m)
{
	if (!(check_for_open_quotes(m)))
		return (free_on_complete(m, NULL));
	add_input_to_history(m->line);
	delete_nth_history();
	if (!(expand_environmental_variables(m)))
		return (free_on_complete(m, NULL));
	if (!(split_by_semicolon(m)))
		return (free_on_complete(m, NULL));
	return (1);
}
