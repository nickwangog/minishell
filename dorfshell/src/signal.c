/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:32:00 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/11 16:26:27 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	command_signal_catcher(int sig)
{
	ft_clearterminal(0, 2);
	ft_pflite("%sdorfshell: Signal caught: %u%s\n", IPURPLE, sig, COLOR_OFF);
}

void	nothing_signal_catcher(int sig)
{
	(void)sig;
}

void	main_signal_catcher(int sig)
{
	(void)sig;
	write(0, "\n", 1);
	print_shell_message();
	free_looped_list();
	if (g_input)
	{
		add_input_to_history(g_input);
		delete_nth_history();
		free(g_input);
		g_input = ft_strnew(0);
		g_tracker = 0;
	}
}
