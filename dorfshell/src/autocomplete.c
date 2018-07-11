/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:43:02 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/06 21:05:30 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		free_looped_list(void)
{
	t_autoc	*tmp;

	if (g_auto)
	{
		tmp = g_auto;
		g_auto = g_auto->right;
		tmp->right = NULL;
		while (g_auto)
		{
			free(g_auto->name);
			tmp = g_auto;
			g_auto = g_auto->right;
			free(tmp);
		}
	}
}

t_autoc		*add_auto_node(t_autoc *h, char *name)
{
	t_autoc	*node;

	if (!h)
	{
		if (!name)
			return (NULL);
		if (!(node = ft_memalloc(sizeof(t_autoc))))
			return (NULL);
		node->name = ft_strdup(name);
		node->len = ft_strlen(name);
		return (node);
	}
	if (ft_strcmp(h->name, name) < 1)
		h->left = add_auto_node(h->left, name);
	else
		h->right = add_auto_node(h->right, name);
	return (h);
}

t_autoc		*bin_tree_to_cdll(t_autoc *n)
{
	t_autoc	*left;
	t_autoc	*right;

	if (n == NULL)
		return (n);
	if (n->left != NULL)
	{
		left = bin_tree_to_cdll(n->left);
		while (left->right != NULL)
			left = left->right;
		left->right = n;
		n->left = left;
	}
	if (n->right != NULL)
	{
		right = bin_tree_to_cdll(n->right);
		while (right->left != NULL)
			right = right->left;
		right->left = n;
		n->right = right;
	}
	return (n);
}

t_autoc		*transform_bin_tree_into_circularly_doubly_looped_list(t_autoc *n)
{
	t_autoc	*nn;

	if (n == NULL)
		return (n);
	n = bin_tree_to_cdll(n);
	while (n->left != NULL)
		n = n->left;
	nn = n;
	while (nn->right != NULL)
		nn = nn->right;
	nn->right = n;
	n->left = nn;
	return (nn);
}

void		autocomplete_create_from_dir(char *dir_name, char *partial_n)
{
	DIR				*temp;
	struct dirent	*dir;
	int				p_len;
	char			*tmp;

	if ((temp = opendir(dir_name)))
	{
		p_len = ft_strlen(partial_n);
		while ((dir = readdir(temp)))
		{
			if (partial_n)
			{
				if (ft_strnequ(partial_n, dir->d_name, p_len))
					if ((tmp = ft_strsub(dir->d_name, p_len,
									ft_strlen(dir->d_name) - p_len)))
						if ((g_auto = add_auto_node(g_auto, tmp)))
							free(tmp);
			}
			else
				g_auto = add_auto_node(g_auto, dir->d_name);
		}
		closedir(temp);
		g_auto = transform_bin_tree_into_circularly_doubly_looped_list(g_auto);
	}
}
