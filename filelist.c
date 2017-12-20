/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:46:36 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/18 16:32:53 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_filelist	*filelist_new(char *input, struct stat *file_info)
{
	t_filelist	*new;

	if (!(new = (t_filelist*)malloc(sizeof(t_filelist))))
		return (NULL);
	if (!(new->fileinfo = fileinfo_new(input, file_info)))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

static void				filelist_insert(t_filelist **filelist,
		t_filelist *new,
		int (*cmp)(t_filelist*, t_filelist*))
{
	t_filelist	*cur;
	t_filelist	*prev;

	cur = *filelist;
	prev = NULL;
	while (cur)
	{
		if (cmp(new, cur) < 0)
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

static t_filelist	**filelist_add(char *options, t_filelist **filelist, t_filelist *new)
{
	if (!*filelist)
		*filelist = new;
	else
	{
		if (option_check(options, 't') && option_check(options, 'r'))
			filelist_insert(filelist, new, &cmp_tr);
		else if (option_check(options, 't'))
			filelist_insert(filelist, new, &cmp_t);
		else if (option_check(options, 'r'))
			filelist_insert(filelist, new, &cmp_r);
		else
			filelist_insert(filelist, new, &cmp_default);
	}
	return (filelist);
}

int				load_file(char *options, char *input, t_filelist **filelist)
{
	struct stat	file_info;

	if (lstat(input, &file_info) < 0)
		return (-1);
	filelist_add(options, filelist, filelist_new(input, &file_info));
	return (0);
}
