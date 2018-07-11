/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 13:48:28 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/08 15:47:14 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_mini	m;

	(void)argc;
	(void)argv;
	ft_bzero(&m, sizeof(t_mini));
	g_input = NULL;
	g_auto = NULL;
	g_hist = NULL;
	g_hist_head = NULL;
	if (!(m.environ = ft_arraydup(env)))
		return (dorfshell_error("Failed to create env variables"));
	while (1)
	{
		signal(SIGINT, main_signal_catcher);
		print_shell_message();
		if ((m.line = get_input()))
			minishell(&m);
	}
	return (1);
}
