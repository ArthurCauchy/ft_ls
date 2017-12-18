/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 13:12:00 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/18 16:29:56 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		read_params(char **argv, char *options, t_filelist **filelist, t_errlist **errlist)
{
	int	i;
	int	is_opt;

	i = 1;
	is_opt = 1;
	while (argv[i])
	{
		if (is_opt && !read_option(argv[i], options))
		{
			is_opt = 0;
		}
		if (!is_opt)
		{
			//if (load_file(options, argv[i], filelist) == -1)
			//	load_err(options, argv[i], errlist);
			load_file(options, argv[i], filelist);
			errlist = NULL; // silence warning. TEMPORARY
		}
		++i;
	}
}

