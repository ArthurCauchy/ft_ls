/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:46:36 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/15 14:42:54 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

t_filelist	**filelist_add(t_filelist **filelist, t_filelist *new)
{
	if (!*filelist)
		*filelist = new;
	else
	{
		if (option_check('S') && option_check('r'))
			filelist_insert(filelist, new, &cmp_Sr);
		else if (option_check('S'))
			filelist_insert(filelist, new, &cmp_S);
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

void		filelist_delete(t_filelist *filelist)
{
	fileinfo_delete(filelist->fileinfo);
	free(filelist);
}
