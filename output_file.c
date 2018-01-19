/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:55:52 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 19:05:58 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Print a file. Uses the g_options global to decide how to print it.
**
** params :
** 1) fileinfo to print
** 2) short name format ? 1 = yes, 0 = no
** 3) pos in the filelist : -1 = first, 0 = middle, 1 = end
*/

void	print_file(t_fileinfo *fileinfo, int short_name, int pos)
{
	if (option_check('l'))
		print_l_line(fileinfo, short_name, pos);
	else if (option_check('1'))
		print_line(fileinfo, short_name);
	else
		print_default(fileinfo, short_name, pos);
}

/*
** Prints a file's filename.
*/

void	print_default(t_fileinfo *fileinfo, int short_name, int pos)
{
	if (pos != -1 && pos != 2)
		ft_putchar(' ');
	if (short_name)
		ft_putstr(get_name_only(fileinfo->path));
	else
		ft_putstr(fileinfo->path);
	if (pos > 0)
		ft_putchar('\n');
}

/*
** Prints a file's filename and a newline.
*/

void	print_line(t_fileinfo *fileinfo, int short_name)
{
	if (short_name)
		ft_putendl(get_name_only(fileinfo->path));
	else
		ft_putendl(fileinfo->path);
}
