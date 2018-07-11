/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:30:04 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/06 20:53:10 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
** grab_last_unbroken_string:
**	- gets 'src/hey' from 'yo wassup, it's me ya boi src/hey'
**	- if last char is not a printable char, it returns null
*/

static char	*grab_last_unbroken_string_for(char *s, int len, int dir_or_file)
{
	char	*unbroken_string;

	while (--len > -1 || ++len)
		if ((s[len] < 33 || s[len] > 126) && ++len)
			break ;
	if (!(unbroken_string = ft_strdup(&s[len])))
		return (NULL);
	s = unbroken_string;
	len = ft_strlen(s);
	while (--len > -1 || ++len)
		if (s[len] == '/' && ++len)
			break ;
	unbroken_string = ft_strdup(
			(dir_or_file == 'd' && !(s[len] = '\0'))
			? s : &s[len]);
	free(s);
	return (unbroken_string);
}

/*
** parselastgivendirname:
**	- from given string, return the fully-qualified dir path given
**	- dirname must be complete, else null is returned
**	- if dirname does not appear right at the end of the string, returns null
*/

static char	*parselastgivendirname(char *s)
{
	DIR				*temp;
	char			*dirname;
	int				len;

	if (!s || !(len = ft_strlen(s)) || (s[len - 1] < 33 || s[len - 1] > 126))
		return (NULL);
	if (!(dirname = grab_last_unbroken_string_for(s, len, 'd')))
		return (NULL);
	if ((temp = opendir(dirname)))
	{
		closedir(temp);
		return (dirname);
	}
	free(dirname);
	return (NULL);
}

/*
** parselastgivenfilename
**	- from given string, return the partially-qualified filename
*/

static char	*parselastgivenfilename(char *s)
{
	int		len;
	char	*filename;

	if (!s || !(len = ft_strlen(s)) || s[len - 1] < 33 || s[len - 1] > 126)
		return (NULL);
	filename = grab_last_unbroken_string_for(s, len, 'f');
	return (filename);
}

void		parse_last_given_dir_and_file_name(char **d, char **f, char *s)
{
	char	*dirname;
	char	*filename;

	dirname = parselastgivendirname(s);
	filename = parselastgivenfilename(s);
	if (dirname && filename)
	{
		if (ft_strequ(dirname, filename))
		{
			free(filename);
			filename = NULL;
		}
	}
	*d = dirname;
	*f = filename;
}
