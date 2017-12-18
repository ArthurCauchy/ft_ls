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

static t_filelist	**filelist_add(char *options, t_filelist **filelist, t_filelist *new)
{
	t_filelist	*cur;

	options = NULL; // silence warning. TEMP
	if (!*filelist)
		*filelist = new;
	else
	{
		cur = *filelist;
		while (cur->next) // a order par ordre alphabetique
			cur = cur->next;
		cur->next = new;
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
