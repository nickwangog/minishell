/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:10:21 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/11 19:41:04 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		handle_history(int r)
{
	if (!g_hist && g_hist_head)
	{
		g_hist = g_hist_head;
		free(g_input);
		g_input = ft_strdup(g_hist->h);
		g_tracker = ft_strlen(g_input);
	}
	else if (g_hist_head)
	{
		if (r == 65 && g_hist->next)
			g_hist = g_hist->next;
		else if (r == 66 && g_hist->prev)
			g_hist = g_hist->prev;
		free(g_input);
		g_input = ft_strdup(g_hist->h);
		g_tracker = ft_strlen(g_input);
	}
}

void		delete_nth_history(void)
{
	t_histo		*great_vanquisher;
	int			count;

	if (g_hist_head)
	{
		if (MINISHELL_HISTORY_LENGTH > 0 && !(count = 0))
		{
			great_vanquisher = g_hist_head;
			while (great_vanquisher->next && ++count < MINISHELL_HISTORY_LENGTH)
				great_vanquisher = great_vanquisher->next;
			if (great_vanquisher->next && count == MINISHELL_HISTORY_LENGTH)
			{
				free(great_vanquisher->next->h);
				free(great_vanquisher->next);
				great_vanquisher->next = NULL;
			}
			return ;
		}
		free(g_hist_head->h);
		free(g_hist_head);
		g_hist_head = NULL;
		g_hist = NULL;
	}
}

void		add_input_to_history(char *addme)
{
	t_histo		*new;

	if (!addme || (addme && addme[0] == '\n' && !addme[1]))
		return ;
	if (!(new = ft_memalloc(sizeof(t_histo))))
		return ;
	if ((new->h = ft_strdup(addme)))
	{
		if (!(g_hist_head))
			g_hist_head = new;
		else
		{
			g_hist_head->prev = new;
			new->next = g_hist_head;
			g_hist_head = new;
		}
		g_hist = NULL;
		return ;
	}
	free(new);
}
