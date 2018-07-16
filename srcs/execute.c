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
			check_var(msh, msh->split[i], 0, 0);
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
	free(temp);
}

void		run_cd(t_msh *msh)
{
	if (msh->split[1] == NULL)
		chdir("/nfs/2017/n/nwang/");
	else if (!ft_strcmp(msh->split[1], "~"))
		chdir("/nfs/2017/n/nwang/");
	else if (msh->split[1] != NULL)
		chdir(msh->split[1]);
	else if (msh->split[2] != NULL)
		ft_printf("cd: string not in pwd: %s\n", msh->split[1]);
}

char		*rm_dollar(char *s)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (s[i])
	{
		s[j] = s[i];
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

void		check_var(t_msh *msh, char *var, int i, int j)
{
	if (!msh->environ)
	{
		ft_putstr("Error");
		return ;
	}
	var = rm_dollar(var);
	while (msh->environ[i] != NULL)
	{
		if (!ft_strncmp(msh->environ[i], var, ft_strlen(var)))
		{
			while (msh->environ[i][j] != '=')
				j++;
			j++;
			while (msh->environ[i][j])
			{
				ft_putchar(msh->environ[i][j]);
				j++;
			}
			return ;
		}
		i++;
	}
}
