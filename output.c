/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:33:52 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/09 14:21:00 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Prints the given error message. If none, just print 'error'.
*/

void	print_error(char *errmsg)
{
	if (errmsg)
		ft_putendl_fd(errmsg, 2);
	else
		ft_putendl_fd("error", 2);
}

/*
** Fancy way to display error related to a specific file.
*/

void	print_file_error(char *filepath)
{
	ft_putstr_fd("ft_ls: unable to open directory '", 2);
	ft_putstr_fd(filepath, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

/*
** Prints the usage.
*/

void	print_usage(void)
{
	ft_putendl("usage: ft_ls [-lRart1d] [file...]");
}

void	print_illegal_option(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
}

void	print_errlist(t_errlist *errlist)
{
	while (errlist)
	{
		ft_miniprint("ft_ls: cannot access '%r0s%': %r0s%\n",
				errlist->input,
				errlist->errmsg); //NOOOO. a print sur fd 2
		errlist = errlist->next;
	}
}
