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
			msh->var = ft_strcat(msh->split[1], "=");
			msh->var = ft_strcat(msh->var, msh->split[2]);
			msh->environ = ft_addto2darray(msh->environ, msh->var);
		}
	}
}

void		run_unsetenv(t_msh *msh, int i)
{
	if (msh->split[1] == NULL)
	{
		ft_putstr("setenv: Too few arguments.\n");
		return ;
	}
    while (msh->split[i])
    {
        msh->var = ft_strcat(msh->split[1], "=");
        msh->var = ft_strcat(msh->var, msh->split[2]);
        msh->environ = ft_addto2darray(msh->environ, msh->var);
        i++
	}
}

