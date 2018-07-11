/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:29:00 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/06 21:16:55 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
** run_executable_command:
**   - Runs the given executable in a new process and waits to continue
**   - m->tmp contains the path to the executable
**   - m->c contains the executable and its arguments
*/

int			run_executable_command(t_mini *m)
{
	pid_t	child_pid;
	int		status;
	int		success;

	success = 0;
	child_pid = fork();
	if (child_pid < 0)
		ft_putstr("Fork failed for some strange reason\n");
	else if (child_pid == 0)
	{
		execve(m->tmp, m->c, m->environ);
		exit(0);
	}
	else
	{
		if (ft_strstr(m->tmp, MINISHELL_EXECUTABLE_NAME))
			signal(SIGINT, nothing_signal_catcher);
		waitpid(child_pid, &status, 0);
		success = 1;
	}
	return (success);
}

/*
** run_builtin_command:
**   - Runs the given builtin command in the same process
**   - m->c contains the executable and its arguments
*/

int			run_builtin_command(t_mini *m)
{
	int	status;

	status = 0;
	if (ft_strequ("exit", m->c[0]))
		exit(2);
	else if (ft_strequ("env", m->c[0]))
		status = builtin_env(m);
	else if (ft_strequ("setenv", m->c[0]))
		status = builtin_setenv(m);
	else if (ft_strequ("unsetenv", m->c[0]))
		status = builtin_unsetenv(m);
	else if (ft_strequ("cd", m->c[0]))
		status = builtin_cd(m);
	else if (ft_strequ("echo", m->c[0]))
		status = builtin_echo(m);
	else if (ft_strequ("byp", m->c[0]))
		status = builtin_byp(m);
	return (status);
}

/*
** run_command:
**   - Checks if the given argument is a builtin or executable,
**     then runs it.
*/

int			run_command(t_mini *m)
{
	int		status;
	int		len;

	status = -1;
	if (!m->c || !m->c[0] || !m->c[0][0])
		return (0);
	else if (is_valid_builtin_command(m))
		status = run_builtin_command(m);
	else if (is_valid_executable_command(m))
		status = run_executable_command(m);
	else if ((len = ft_strlen(m->c[0])) || !len)
	{
		ft_pflite("dorfshell: command not found: ");
		while (++status < len || (status = 0))
			(m->c[0][status] == '\n') ?
				write(1, "\\n", 2) : write(1, &m->c[0][status], 1);
		write(1, "\n", 1);
	}
	ft_strdel(&m->tmp);
	ft_arraydel(&m->temp);
	return (status);
}

/*
** minishell:
**   - 1) Parses command line, validates, and creates command sets (m->cmds)
**   - 2) Iterates over command sets, split by the ';' character (m->cmds)
**   - 3) Splits command set by '&' or '&&' characters (m->cmd)
**   - 4) Splits command into arguments (m->c)
**   - 5) Runs the individual command
**   - 6) Frees arrays as it iterates over command sets, commands, and args
**   - currently, not doing anything with status, but I could find a use
**     for it in the future...
*/

void		minishell(t_mini *m)
{
	int		i;
	int		j;
	int		status;

	signal(SIGINT, command_signal_catcher);
	if (parse_command_line(m) && (i = -1))
	{
		while (m->cmds && m->cmds[++i] && (j = -1))
		{
			m->cmd = split_by_and(m, m->cmds[i]);
			while (m->cmd && m->cmd[++j])
			{
				m->c = split_by_arg(m, m->cmd[j]);
				status = run_command(m);
				ft_arraydel(&m->c);
			}
			ft_arraydel(&m->cmd);
		}
		ft_arraydel(&m->cmds);
	}
	free_on_complete(m, NULL);
}
