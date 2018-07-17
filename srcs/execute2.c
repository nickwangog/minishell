/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 22:03:17 by nwang             #+#    #+#             */
/*   Updated: 2018/07/11 14:48:20 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		run_setenv(t_msh *msh)
{
	char **temp;

	temp = NULL;
	if (!msh->split[1])
	{
		ft_print2darray(msh->environ);
		return ;
	}
	if (msh->split[3] != NULL)
	{
		ft_putstr("setenv: Too many arguments.\n");
		return ;
	}
	if (msh->split[1] && msh->split[2])
	{
		if (!ft_isalphanumeric(msh->split[1]))
		{
			ft_putstr("setenv: Variable name be alphanumeric.\n");
			return ;
		}
		else
		{
			msh->var = ft_strjoin(msh->split[1], "=");
			msh->var = ft_strfjoin(&msh->var, msh->split[2]);
			temp = ft_addto2darray(msh->environ, msh->var);
			if (msh->environ)
				ft_cleararray(msh->environ);
			msh->environ = temp;
		}
	}
}

void		remove_array(t_msh *msh, int i, int j)
{
	free(msh->environ[j]);
	while (msh->environ[j + i] != NULL)
		i++;
	ft_memcpy(&msh->environ[j], &msh->environ[j + 1], i * sizeof(char *));
}

void		run_unsetenv(t_msh *msh, int i, int j)
{
	if (msh->split[1] == NULL)
	{
		ft_putstr("setenv: Too few arguments.\n");
		return ;
	}
	while (msh->split[i])
	{
		j = 0;
		while (msh->environ[j] != NULL)
		{
			if (!ft_strncmp(msh->environ[j], msh->split[i]
				, ft_strlen(msh->split[i])))
				remove_array(msh, 0, j);
			j++;
		}
		i++;
	}
}

char		*rm_end(t_msh *msh, char *str)
{
	int		i;
	char	*s;

	s = str;
	i = ft_strlen(s);
	while (s[i] != '/')
		i--;
	s[i] = '\0';
	msh->i = i;
	return (s);
}

int			check_dir(t_msh *msh, char *s)
{
	DIR		*dir;

	s = rm_end(msh, s);
	dir = opendir(s);
	s[msh->i] = '/';
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	closedir(dir);
	return (0);
}
