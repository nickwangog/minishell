/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 21:16:07 by nwang             #+#    #+#             */
/*   Updated: 2018/06/26 21:16:15 by nwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libft/includes/ft_printf.h"
# define C_RED		"\x1b[31m"
# define C_GRN		"\x1b[32m"
# define C_YEL		"\x1b[33m"
# define C_BLU		"\x1b[34m"
# define C_MAG		"\x1b[35m"
# define C_CYN		"\x1b[36m"
# define C_WHT		"\x1b[37m"
# define C_RESET	"\x1b[0m"

typedef struct				s_msh
{
	char					*line;
	char					**split;
	char					**environ;
	char					**paths;
	char					*executable;
	char					*var;
}							t_msh;

char        *read_input(void);
void    	minierror(char *s);
void        parse_line(t_msh *msh);
void        minishell(t_msh *msh);
void        run_echo(t_msh *msh);
void        run_pwd(void);
void        parse_path(t_msh *msh);
void        run_cd(t_msh *msh);
void		run_setenv(t_msh *msh);
void		run_unsetenv(t_msh *msh, int i, int j);
void		check_var(t_msh *msh, char *var);

#endif
