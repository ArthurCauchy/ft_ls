/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:56:16 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 11:52:08 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_errlist	*errlist_new(char *input, char *errmsg)
{
	t_errlist	*new;

	if (!(new = (t_errlist*)malloc(sizeof(t_errlist))))
		return (NULL);
	new->input = input;
	new->errmsg = errmsg;
	new->next = NULL;
	return (new);
}

static void			errlist_insert(t_errlist **errlist, t_errlist *new)
{
	t_errlist	*cur;
	t_errlist	*prev;

	cur = *errlist;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(new->input, cur->input) <= 0)
		{
			if (prev)
				prev->next = new;
			else
				*errlist = new;
			new->next = cur;
			return ;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

static t_errlist	**errlist_add(t_errlist **errlist, t_errlist *new)
{
	if (!*errlist)
		*errlist = new;
	else
		errlist_insert(errlist, new);
	return (errlist);
}

void				register_err(char *input, t_errlist **errlist)
{
	char		*errmsg;
	t_errlist	*new;

	errmsg = NULL;
	new = NULL;
	errmsg = ft_strdup(strerror(errno));
	if (!errmsg || !(new = errlist_new(input, errmsg)))
		exit_error("error: register_err");
	errlist_add(errlist, new);
}

void				delete_errlist(t_errlist *errlist)
{
	t_errlist	*prev;

	while (errlist)
	{
		free(errlist->errmsg);
		prev = errlist;
		errlist = errlist->next;
		free(prev);
	}
}
