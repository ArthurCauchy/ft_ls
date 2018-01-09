/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_inputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:50:59 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/09 17:22:33 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	process_inputs(t_filelist *filelist, t_dirlist *dirlist, t_errlist *errlist)
{
	process_files(filelist, 0);
	process_dirs(dirlist, filelist, errlist);
}

/*
** Process the files given (print and free actually)
** params :
** 1) filelist : files to print
** 2) short name format ? 1 = yes, 0 = no
**
** pos will be used to know if it's the first, middle or last element
** -1 = first, 0 = middle, 1 = last, 2 = first and last (alone)
*/

void	process_files(t_filelist *filelist, int short_name)
{
	t_filelist	*prev;
	int			pos;

	prev = NULL;
	pos = -1;
	while (filelist)
	{
		prev = filelist;
		filelist = filelist->next;
		if (!filelist)
		{
			if (pos == -1)
				print_file(prev->fileinfo, short_name, 2);
			else
				print_file(prev->fileinfo, short_name, 1);
		}
		else
			print_file(prev->fileinfo, short_name, pos);
		filelist_delete(prev);
		pos = 0;
	}
}
