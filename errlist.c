/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:56:16 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 17:02:25 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Creates a new errlist element.
**
** params :
** 1) path/name of the file that caused the error
** 2) an error message
**
** return :
** The created errlist element, or NULL if it failed.
*/

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

/*
** Insert an element in the list.
** Uses ft_strcmp to know where to perform the insertion.
**
** params :
** 1) the list's head
** 2) the element to insert
*/

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

/*
** Add an element in the list.
** The list is ordered using strcmp.
**
** params:
** 1) the list's head
** 2) the element to add
**
** return :
** The new head of the list.
*/

static t_errlist	**errlist_add(t_errlist **errlist, t_errlist *new)
{
	if (!*errlist)
		*errlist = new;
	else
		errlist_insert(errlist, new);
	return (errlist);
}

/*
** Registers a new error.
*/

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

/*
** Delete an element of the errlist.
*/

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
