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

int			main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	(void)argc;
	(void)argv;
	ft_bzero(&msh, sizeof(t_msh));
	msh.environ = envp;
	while (1)
	{
		// signal(SIGINT, main_signal_catcher);
		ft_printf(C_CYN"minishell $> "C_RESET);
		// can print current directory as bonus
		if ((msh.line = read_input()))
		{
			parse_line(&msh);
			parse_path(&msh);
			minishell(&msh);
		}
	}
	return (0);
}
