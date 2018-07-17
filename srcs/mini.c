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
	else if (msh->split[0][0] == '/')
	{
		if (check_dir(msh, msh->split[0]))
		{
			msh->relative = msh->split[0];
			msh->check_rel = 1;
		}
		return (0);
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
	else if (!ft_strcmp(ft_strlowcase(msh->split[0]), "exit"))
		exit(1);
	else if (!ft_strcmp(ft_strlowcase(msh->split[0]), "pwd"))
	{
		run_pwd();
		return (1);
	}
	else
		return (check_builtins2(msh));
}

void				run_exec(t_msh *msh, int i)
{
	int			status;
	pid_t		child;

	free(msh->executable);
	if (msh->paths != NULL && msh->check_rel == 0)
	{
		// if (msh->executable != NULL)
		// 	free(msh->executable);
		msh->executable = ft_strjoin(msh->paths[i], "/");
		msh->executable = ft_strfjoin(&msh->executable, msh->split[0]);
	}
	else if (msh->check_rel)
	{
		// if (msh->executable != NULL)
		// 	free(msh->executable);
		msh->executable = ft_strdup(msh->relative);
	}
	else
		return ;
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
		return ;
	}
}

int					check_exec(t_msh *msh, int i, DIR *temp)
{
	struct dirent	*dir;

	dir = NULL;
	if (!msh->paths || msh->check_rel)
		return (0);
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
					run_exec(msh, i);
					closedir(temp);
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
	DIR				*temp;

	temp = NULL;
	if (!msh->split || !msh->split[0])
		return ;
	if (check_builtins(msh))
		return ;
	else if (msh->check_rel)
		run_exec(msh, 0);
	else if (!check_exec(msh, 0, temp))
		ft_printf("minishell: command not found: %s\n", msh->split[0]);
	else
		return ;
}
