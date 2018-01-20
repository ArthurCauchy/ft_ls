/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:55:37 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/20 10:51:32 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Print a directory.
**
** params:
** 1) the directory to print
** 2) the files in the directory
** 3) first directory we're printing ?
**    0 = no, 1 = yes, 2 = yes and the only one
*/

void	print_dir(t_dirlist *dir, t_filelist *files, int is_first)
{
	if (!is_first)
		ft_putchar('\n');
	if (is_first < 2 || option_check('R'))
	{
		ft_putstr(dir->fileinfo->path);
		ft_putendl(":");
	}
	process_files(files, 1);
}
