/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 13:51:30 by nwang             #+#    #+#             */
/*   Updated: 2018/07/10 00:45:35 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					check_builtins2(t_msh *msh)
{
	if (!ft_strcmp(ft_strlowcase(msh->split[0]), "unsetenv"))
	{
		run_unsetenv(msh, 1, 0);
		return (1);
	}
	else if (!ft_strcmp(ft_strlowcase(msh->split[0]), "env"))
	{
		ft_print2darray(msh->environ);
		return (1);
	}
	else if (!ft_strcmp(ft_strlowcase(msh->split[0]), "exit"))
		exit(1);
	else if (!ft_strcmp(ft_strlowcase(msh->split[0]), "pwd"))
	{
		run_pwd();
		return (1);
	}
	else
		return (0);
}

int					check_builtins(t_msh *msh)
{
	if (!ft_strcmp(ft_strlowcase(msh->split[0]), "echo"))
	{
		run_echo(msh);
		return (1);
	}
	else if (!ft_strcmp(ft_strlowcase(msh->split[0]), "cd"))
	{
		run_cd(msh);
		return (1);
	}
	else if (!ft_strcmp(ft_strlowcase(msh->split[0]), "setenv"))
	{
		run_setenv(msh);
		return (1);
	}
	else
		return (check_builtins2(msh));
}

void				run_exec(t_msh *msh, int i, DIR *temp)
{
	int			status;
	pid_t		child;

	msh->executable = ft_strcat(msh->paths[i], "/");
	msh->executable = ft_strcat(msh->executable, msh->split[0]);
	child = fork();
	if (child == -1)
		minierror("fork failed");
	else if (child == 0)
	{
		execve(msh->executable, msh->split, msh->environ);
		exit(0);
	}
	else
	{
		waitpid(child, &status, 0);
		closedir(temp);
		return ;
	}
}

int					check_exec(t_msh *msh, int i)
{
	DIR				*temp;
	struct dirent	*dir;

	temp = NULL;
	dir = NULL;
	while (msh->paths[i] != NULL)
	{
		if ((temp = opendir(msh->paths[i])) == NULL)
			i++;
		else
		{
			while ((dir = readdir(temp)))
			{
				if (!ft_strcmp(msh->split[0], dir->d_name))
				{
					run_exec(msh, i, temp);
					return (1);
				}
			}
			closedir(temp);
			i++;
		}
	}
	return (0);
}

void				minishell(t_msh *msh)
{
	if (!msh->split[0])
		return ;
	if (check_builtins(msh))
		return ;
	else if (!check_exec(msh, 0))
		ft_printf("minishell: command not found: %s\n", msh->split[0]);
	else
		return ;
}
