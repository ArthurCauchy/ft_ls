/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:46:36 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 14:46:43 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Creates a new dirlist element.
**
** params :
** 1) path/name of the directory
** 2) a structure returned by stat() or lstat()
**
** return :
** The created dirlist element, or NULL if it failed.
*/

t_dirlist	*dirlist_new(char *input,
		struct stat *stat_info)
{
	t_dirlist	*new;

	if (!(new = (t_dirlist*)malloc(sizeof(t_dirlist))))
		return (NULL);
	if (!(new->fileinfo = fileinfo_new(input, stat_info)))
	{
		free(new);
		return (NULL);
	}
	new->files = NULL;
	new->next = NULL;
	return (new);
}

/*
** Insert an element in the list.
** Uses a comparison func to know where to perform the insertion.
**
** params :
** 1) the list's head
** 2) the element to insert
** 3) a comparision function
*/

void		dirlist_insert(t_dirlist **dirlist,
		t_dirlist *new,
		int (*cmp)(t_fileinfo*, t_fileinfo*))
{
	t_dirlist	*cur;
	t_dirlist	*prev;

	cur = *dirlist;
	prev = NULL;
	while (cur)
	{
		if (cmp(new->fileinfo, cur->fileinfo) <= 0)
		{
			if (prev)
				prev->next = new;
			else
				*dirlist = new;
			new->next = cur;
			return ;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	prev->next = new;
}

/*
** Add an element in the list.
** The list is ordered accoringly to sort options in the g_options global.
**
** params:
** 1) the list's head
** 2) the element to add
**
** return :
** The new head of the list.
*/

t_dirlist	**dirlist_add(t_dirlist **dirlist, t_dirlist *new)
{
	if (!*dirlist)
		*dirlist = new;
	else
	{
		if (option_check('S') && option_check('r'))
			dirlist_insert(dirlist, new, &cmp_sr);
		else if (option_check('S'))
			dirlist_insert(dirlist, new, &cmp_s);
		else if (option_check('t') && option_check('r'))
			dirlist_insert(dirlist, new, &cmp_tr);
		else if (option_check('t'))
			dirlist_insert(dirlist, new, &cmp_t);
		else if (option_check('r'))
			dirlist_insert(dirlist, new, &cmp_r);
		else
			dirlist_insert(dirlist, new, &cmp_default);
	}
	return (dirlist);
}

/*
** Delete an element of the dirlist.
*/

void		dirlist_delete(t_dirlist *dirlist)
{
	if (!dirlist)
		return ;
	fileinfo_delete(dirlist->fileinfo);
	free(dirlist);
}
