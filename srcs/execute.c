/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 22:02:56 by nwang             #+#    #+#             */
/*   Updated: 2018/07/04 22:03:05 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		run_echo(t_msh *msh)
{
	int		i;

	i = 1;
	while (msh->split[i] && msh->split[i] != NULL)
	{
		if (msh->split[i][0] == '$')
			check_var(msh->environ, msh->split[i]);
		else
			ft_putstr(msh->split[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void		run_pwd(void)
{
	char	*temp;

	temp = NULL;
	temp = getcwd(temp, sizeof(temp));
	ft_printf("%s\n", temp);
}

void		run_cd(t_msh *msh)
{
	if (msh->split[1] != NULL)
		chdir(msh->split[1]);
	if (msh->split[1] == NULL)
		chdir("/nfs/2017/n/nwang/");
	else if (msh->split[2] != NULL)
		ft_printf("cd: string not in pwd: %s\n", msh->split[1]);
}

void		check_var(t_msh *msh, char *var)
{
	
}