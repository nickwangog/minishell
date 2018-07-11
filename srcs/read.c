/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 13:51:37 by nwang             #+#    #+#             */
/*   Updated: 2018/07/08 14:42:37 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_path(t_msh *msh)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (msh->environ[i] != NULL)
	{
		if (msh->environ[i][0] != 'P' && msh->environ[i][1] != 'A')
			i++;
		else
		{
			msh->paths = ft_strsplit(msh->environ[i], ':');
			break ;
		}
	}
	i = 0;
	while (msh->paths[0][i] != '/' && msh->paths[0][i])
	{
		i++;
		j++;
	}
	i = 0;
	while (msh->paths[0][j])
		msh->paths[0][i++] = msh->paths[0][j++];
}

void		parse_line(t_msh *msh)
{
	// int		i;
	// int		count;
	// i = 0;
	// count = ft_countwords(msh->line, ' ');
	// if (!(msh->split = (char **)malloc(sizeof(char *) * count)))
	// 	minierror("Split failed to allocate");
	// while (i + 1 < count)
	// {
	// 	if (!(msh->split[i] = (char *)malloc(sizeof(char) * 900)))
	// 		minierror("Split failed to allocate");
	// 	i++;
	// }
	msh->split = ft_strsplit(msh->line, ' ');
}

char		*read_input(void)
{
	int		bufsize;
	char	*buf;
	int		c;
	int		i;

	i = 0;
	bufsize = 900;
	buf = (char *)malloc(sizeof(char) * bufsize);
	if (!buf)
		minierror("Buf failed to allocate");
	while (1)
	{
		c = getchar();
		if (c == EOF || c == '\n')
		{
			buf[i] = '\0';
			return (buf);
		}
		else
			buf[i] = c;
		i++;
	}
}
