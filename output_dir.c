/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:55:37 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/08 10:55:39 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dir(t_dirlist *dir, t_filelist *files)
{
	ft_putchar('\n'); // SAUF SI PREMIER
	ft_putstr(dir->fileinfo->path); // SAUF SI PREMIER ET DERNIER
	ft_putendl(":");
	// TODO print total
	process_files(files, 1);
}
