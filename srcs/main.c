/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 21:14:17 by nwang             #+#    #+#             */
/*   Updated: 2018/07/08 14:42:15 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		minierror(char *s)
{
	ft_printf("%s.\n", s);
	exit(1);
}

void		cwd_name(t_msh *msh)
{
	int i;

	i = 0;
	if (msh->dirpath)
		ft_cleararray(msh->dirpath);
	msh->dirpath = NULL;
	msh->cwd = NULL;
	msh->cwd = getcwd(msh->cwd, sizeof(msh->cwd));
	msh->dirpath = ft_strsplit(msh->cwd, '/');
	ft_strdel(&msh->cwd);
	while (msh->dirpath[i] != NULL)
		i++;
	i--;
	msh->cwd = msh->dirpath[i];
}

int			main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	(void)argc;
	(void)argv;
	ft_bzero(&msh, sizeof(t_msh));
	msh.environ = ft_arraydup(envp);
	while (1)
	{
		cwd_name(&msh);
		ft_printf(C_CYN"%s "C_BLU"minishell "C_YEL"$> "C_RESET, msh.cwd);
		if ((msh.line = read_input()))
		{
			parse_line(&msh);
			parse_path(&msh, 0, 0);
			minishell(&msh);
			msh.check_rel = 0;
		}		
	}
	return (0);
}
