/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:44:51 by bpierce           #+#    #+#             */
/*   Updated: 2018/02/13 20:17:02 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
** get_env_var:
**   - Returns a POINTER COPY to the malloc'd string of the given env var name
**     stored in m->environ
**   - Ensure that 'var' is always a string of just PATH, and not $PATH=
**   - If no env var exists, returns NULL
**   - options is if you want to include the 'PATH=' or not, for example
*/

char	*get_env_var(t_mini *m, char *var, int options)
{
	int		i;
	int		len;
	int		flag;

	if (!var)
		return (dorfshell_null("No given variable name"));
	if (!(m->tmp = ft_strjoin(var, "=")))
		return (dorfshell_null("Failed to strjoin '=' in get_env_var func"));
	i = -1;
	flag = 0;
	len = ft_strlen(m->tmp);
	while (m->environ[++i])
		if (ft_strnequ(m->environ[i], m->tmp, len) && (flag = 1))
			break ;
	ft_strdel(&m->tmp);
	if (!flag)
		return (NULL);
	return (options == INC_ENV_VAR_NAME ? m->environ[i] : &m->environ[i][len]);
}

char	*create_new_env_var(t_mini *m, char *new_name, char *new_res)
{
	int		i;

	if (!m || !new_name || !new_res || !(i = -1))
		return (NULL);
	while (m->environ[++i])
		;
	if (!(m->temp = (char **)malloc(sizeof(char *) * (i + 2))))
		return (dorfshell_null("create_new_env_var failed to malloc"));
	i = -1;
	while (m->environ[++i])
		m->temp[i] = m->environ[i];
	if (!(m->temp[i++] = ft_sandwichjoin(new_name, new_res, "=")))
	{
		free(m->temp);
		m->temp = NULL;
		return (dorfshell_null("sandwichjoin failed"));
	}
	m->temp[i] = NULL;
	free(m->environ);
	m->environ = m->temp;
	m->temp = NULL;
	return (m->environ[--i]);
}

char	*set_env_var(t_mini *m, char *var_name, char *var_res, int byp)
{
	int		i;
	int		env_len;

	if (!m || !var_name || !var_res || !(i = -1))
		return (NULL);
	if (!(m->byp || byp) && SEQ_4(var_name, "PATH", "PWD", "OLDPWD", "HOME"))
		return (dorfshell_null("NO! I will eat your SOUL if you try that!"));
	while (m->environ[++i] && (env_len = ft_strccountto(m->environ[i], '=')))
	{
		if (ft_strnequ(var_name, m->environ[i], env_len) &&
				(size_t)env_len == ft_strlen(var_name))
		{
			if (!(m->tmp = ft_sandwichjoin(var_name, var_res, "=")))
				return (dorfshell_null("sandwichjoin failed"));
			free(m->environ[i]);
			m->environ[i] = m->tmp;
			m->tmp = NULL;
			return (m->environ[i]);
		}
	}
	return (create_new_env_var(m, var_name, var_res));
}

/*
** remove_env_var:
**   - char *v must be a pointer to the same memory location of the
**     string to free. It can be aquired with get_env_var return value
*/

char	**remove_env_var(t_mini *m, char *v)
{
	int		i;

	i = -1;
	if (!m || !v || !m->environ || !m->environ[0] || !(i = -1))
		return (dorfshell_null("No env vars to delete"));
	if (!m->byp && (ENV_4(v, "PATH", "PWD", "OLDPWD", "HOME")))
		return (dorfshell_null("NO! I will eat your SOUL if you try that!"));
	while (m->environ[++i])
	{
		if (v == m->environ[i])
		{
			free(m->environ[i]);
			while (m->environ[i + 1])
			{
				m->environ[i] = m->environ[i + 1];
				++i;
			}
			m->environ[i] = NULL;
			break ;
		}
	}
	return (m->environ);
}

/*
** print_env_var:
**   - Prints the given var name
**   - Options: INC_ENV_VAR_NAME means to include PATH= or not
*/

void	print_env_var(t_mini *m, char *var, int options)
{
	int		i;
	int		len;

	if (!m || !var)
		return ;
	i = -1;
	len = ft_strlen(var);
	while (m->environ[++i])
	{
		if (ft_strnequ(m->environ[i], var, len))
		{
			ft_putendl(options == INC_ENV_VAR_NAME ?
					m->environ[i] : &m->environ[i][len + 1]);
			break ;
		}
	}
}
