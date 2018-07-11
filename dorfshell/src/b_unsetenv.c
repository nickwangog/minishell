/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unsetenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 18:06:58 by bpierce           #+#    #+#             */
/*   Updated: 2018/01/25 22:51:55 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				builtin_unsetenv(t_mini *m)
{
	char	*n;
	char	*v;

	if (!m || !m->c[1])
		return (ft_puterror("dorfshell: what var would you like to unset?", 0));
	if (m->c[2])
		return (ft_puterror("dorfshell: too many args for unsetenv", 0));
	if (m->c[1][ft_strccountto(m->c[1], '=')] == '=')
	{
		return (ft_puterror("dorfshell: no equals ( '=' ) sign plz", 0));
	}
	if (!(n = ft_strremovequotes(m->c[1])))
		return (ft_puterror("dorfshell: failed to remove quotes", 0));
	if (!(v = get_env_var(m, m->c[1], INC_ENV_VAR_NAME)))
		ft_pflite("dorfshell: the variable '%s' doesn't exist\n", m->c[1]);
	else
		remove_env_var(m, v);
	free(n);
	return (v ? 1 : 0);
}
