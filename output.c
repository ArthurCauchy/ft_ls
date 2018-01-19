/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:33:52 by acauchy           #+#    #+#             */
/*   Updated: 2018/01/18 19:01:40 by arthur           ###   ########.fr       */
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
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(filepath, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

/*
** Prints the usage.
*/

void	print_usage(void)
{
	ft_putendl_fd("usage: ft_ls [-lRartS1d] [file...]", 2);
}

/*
** Print an error message saying that the given char is an invalid option.
*/

void	print_illegal_option(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
}

/*
** Display all elements of an errlist.
*/

void	print_errlist(t_errlist *errlist)
{
	while (errlist)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(errlist->input, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(errlist->errmsg, 2);
		ft_putchar_fd('\n', 2);
		errlist = errlist->next;
	}
}
