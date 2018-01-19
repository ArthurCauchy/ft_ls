/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:46:36 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/19 13:37:04 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Creates a new filelist element.
**
** params :
** 1) path/name of the file
** 2) a structure returned by stat() or lstat()
**
** return :
** The created filelist element, or NULL if it failed.
*/

t_filelist	*filelist_new(char *input, struct stat *stat_info)
{
	t_filelist	*new;

	if (!(new = (t_filelist*)malloc(sizeof(t_filelist))))
		return (NULL);
	if (!(new->fileinfo = fileinfo_new(input, stat_info)))
	{
		free(new);
		return (NULL);
	}
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

static void	filelist_insert(t_filelist **filelist,
		t_filelist *new,
		int (*cmp)(t_fileinfo*, t_fileinfo*))
{
	t_filelist	*cur;
	t_filelist	*prev;

	cur = *filelist;
	prev = NULL;
	while (cur)
	{
		if (cmp(new->fileinfo, cur->fileinfo) <= 0)
		{
			if (prev)
				prev->next = new;
			else
				*filelist = new;
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

t_filelist	**filelist_add(t_filelist **filelist, t_filelist *new)
{
	if (!*filelist)
		*filelist = new;
	else
	{
		if (option_check('S') && option_check('r'))
			filelist_insert(filelist, new, &cmp_sr);
		else if (option_check('S'))
			filelist_insert(filelist, new, &cmp_s);
		else if (option_check('t') && option_check('r'))
			filelist_insert(filelist, new, &cmp_tr);
		else if (option_check('t'))
			filelist_insert(filelist, new, &cmp_t);
		else if (option_check('r'))
			filelist_insert(filelist, new, &cmp_r);
		else
			filelist_insert(filelist, new, &cmp_default);
	}
	return (filelist);
}

/*
** Delete an element of the filelist.
*/

void		filelist_delete(t_filelist *filelist)
{
	fileinfo_delete(filelist->fileinfo);
	free(filelist);
}
