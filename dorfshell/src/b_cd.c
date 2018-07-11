/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 18:07:56 by bpierce           #+#    #+#             */
/*   Updated: 2018/02/13 19:24:02 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	cd(t_mini *m, char *path)
{
	if (!(m->cwd = getcwd(NULL, 0)))
		return (dorfshell_error("No current working directory???"));
	if (chdir(path) != 0)
		return (dorfshell_error("Could not change directory"));
	if (!(set_env_var(m, "OLDPWD", m->cwd, 1)))
		return (dorfshell_error("Could not set OLDPWD environmental variable"));
	ft_strdel(&m->cwd);
	if (!(m->cwd = getcwd(NULL, 0)))
		return (dorfshell_error("No current working directory???"));
	if (!(set_env_var(m, "PWD", m->cwd, 1)))
		return (dorfshell_error("Could not set the PWD environment variable"));
	ft_strdel(&m->cwd);
	return (1);
}

static int	cd_to_var(t_mini *m, char *var)
{
	char	*s;

	if (!(s = get_env_var(m, var, 0)))
	{
		ft_pflite("dorfshell: %s '%s' does not exit! WHAT HATH YE DONE\n",
				"The environmental variable", var);
		return (0);
	}
	return (cd(m, s));
}

static void	expand_tilde_to_home_dir(t_mini *m)
{
	char	*home;

	if (!(home = get_env_var(m, "HOME", 0)))
		return ;
	m->tmp = m->c[1];
	if (!(m->c[1] = ft_strreplace(m->c[1], "~", home)))
		ft_pflite("dorfshell: Could not replace the '~' with HOME path\n");
	ft_strdel(&m->tmp);
}

int			builtin_cd(t_mini *m)
{
	struct stat		path_stat;

	if (m->c[1] && m->c[2])
		return (dorfshell_error("Too many arguments for cd"));
	else if (m->c[1] && !ft_strequ(m->c[1], "~"))
	{
		expand_tilde_to_home_dir(m);
		if (ft_strequ(m->c[1], "-"))
			return (cd_to_var(m, "OLDPWD"));
		if (stat(m->c[1], &path_stat) == -1)
		{
			ft_pflite("dorfshell: no such directory exists: %s\n", m->c[1]);
			return (0);
		}
		if (!S_ISDIR(path_stat.st_mode))
		{
			ft_pflite("dorfshell: %s %s\n", m->c[1],
					"IS NOT A DIRECTORY - YOU CRAZY OR SUMMIN'?");
			return (0);
		}
		return (cd(m, m->c[1]));
	}
	return (cd_to_var(m, "HOME"));
}
