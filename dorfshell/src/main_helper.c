/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:32:00 by bpierce           #+#    #+#             */
/*   Updated: 2018/01/29 21:08:25 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	print_time(void)
{
	time_t	timey;
	char	*ret;

	time(&timey);
	ret = &ctime(&timey)[4];
	ret[16] = '\0';
	if (ret[4] == ' ')
	{
		ret[3] = ret[2];
		ret[2] = ret[1];
		ret[1] = ret[0];
		ret++;
	}
	ft_pflite("%s%s%s", IYELLOW, ret, COLOR_OFF);
}

void	print_shell_message(void)
{
	print_time();
	ft_putstr(SHELL_MESSAGE);
}

int		dorfshell_error(char *message)
{
	if (message)
		ft_pflite("%sdorfshell: %s\n%s", RED, message, COLOR_OFF);
	return (0);
}

void	*dorfshell_null(char *message)
{
	if (message)
		ft_pflite("%sdorfshell: %s\n%s", RED, message, COLOR_OFF);
	return (NULL);
}
