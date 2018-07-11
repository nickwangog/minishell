/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_revamped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 14:52:31 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/11 19:33:39 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	handle_tabs(void)
{
	char	*last_d;
	char	*last_f;
	int		l;

	l = ft_strlen(g_input);
	if (!g_auto)
	{
		parse_last_given_dir_and_file_name(&last_d, &last_f, g_input);
		last_d = !last_d ? ft_strdup(".") : last_d;
		autocomplete_create_from_dir(last_d, last_f);
		free(last_d);
		free(last_f);
		if (g_auto && ((g_tracker += ft_strlen(g_auto->name)) || !g_tracker))
			g_input = ft_strfsplice(&g_input, &g_input[l], g_auto->name);
		return ;
	}
	g_input = ft_strfsplice(&g_input, &g_input[l - ft_strlen(g_auto->name)],
			g_auto->left->name);
	g_input[l - ft_strlen(g_auto->name) + ft_strlen(g_auto->left->name)] = '\0';
	g_tracker += ft_strlen(g_auto->left->name) - ft_strlen(g_auto->name);
	g_auto = g_auto->left;
}

static void	handle_cursor(void)
{
	int		input_len;
	int		save;

	save = g_input[g_tracker];
	input_len = ft_strlen(g_input);
	write(1, g_input, input_len);
	ft_cbackward(input_len);
	g_input[g_tracker] = '\0';
	write(1, g_input, ft_strlen(g_input));
	g_input[g_tracker] = save;
}

static void	handle_input(char *buf, int r)
{
	ft_cbackward(g_tracker);
	ft_cclearscreen(0);
	if ((r > 31 && r < 127) && (buf[0] = r))
		if ((g_input = ft_strfsplice(&g_input, &g_input[g_tracker], buf)))
			g_tracker += 1;
	if (r == 27)
	{
		r = getchar() == 91 ? getchar() : 0;
		if (r == 65 || r == 66)
			handle_history(r);
		else if (r == 67)
			g_tracker = MIN((int)ft_strlen(g_input), g_tracker + 1);
		else if (r == 68)
			g_tracker = MAX(0, g_tracker - 1);
	}
	else if (r == 127 && g_tracker > 0 && ((g_tracker -= 1) || !g_tracker))
		ft_memcpy(&g_input[g_tracker], &g_input[g_tracker + 1],
				ft_strlen(&g_input[g_tracker]));
	else if (r == '\t')
		handle_tabs();
	handle_cursor();
}

static void	turn_off_stdin_buffering(struct termios *old, struct termios *new)
{
	tcgetattr(STDIN_FILENO, old);
	*new = *old;
	new->c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, new);
}

char		*get_input(void)
{
	char			r;
	char			buf[2];
	struct termios	tio[2];

	if (!(g_input = ft_strfnew(&g_input, 0)))
		return (dorfshell_null("Failed to initialize an input reader"));
	g_tracker = 0;
	buf[1] = '\0';
	turn_off_stdin_buffering(&tio[0], &tio[1]);
	while ((r = getchar()))
	{
		handle_input(buf, r);
		if (r != '\t')
			free_looped_list();
		if (r == '\n')
		{
			g_input = ft_strfjoin(&g_input, "\n");
			write(1, "\n", 1);
			break ;
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &tio[0]);
	return (ft_strdup(g_input));
}
