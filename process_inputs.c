/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_inputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:50:59 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 19:34:35 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Basically process everthing that needs to be done by our program after
** reading parameters and options.
*/

void	process_inputs(t_filelist *filelist,
		t_dirlist *dirlist, t_errlist *errlist)
{
	int	files_and_dir;

	files_and_dir = filelist && dirlist;
	process_files(filelist, 0);
	if (files_and_dir)
		ft_putchar('\n');
	process_dirs(dirlist, filelist, errlist);
}

/*
** Process the given files (print and free actually).
**
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
