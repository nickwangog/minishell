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

void		parse_path(t_msh *msh, int i, int j)
{
	if (msh->paths)
		ft_cleararray(msh->paths);
	msh->paths = NULL;
	while (msh->environ[i] != NULL)
	{
		if ((ft_strncmp(msh->environ[i], "PATH", 4)))
			i++;
		else
		{
			msh->paths = ft_strsplit(msh->environ[i], ':');
			break ;
		}
	}
	if (!msh->paths)
		return ;
	i = 0;
	while (msh->paths[0][i] != '/' && msh->paths[0][i])
	{
		i++;
		j++;
	}
	i = 0;
	while (msh->paths[0][j])
		msh->paths[0][i++] = msh->paths[0][j++];
	msh->paths[0][i] = '\0';
}

void		parse_line(t_msh *msh)
{
	msh->line = ft_strctrim(msh->line, '\t');
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
