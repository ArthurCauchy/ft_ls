/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:33:52 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/14 18:15:20 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Prints the usage.
*/

void	print_error(void)
{
	ft_putendl("error");
}

void	print_usage(void)
{
	ft_putendl("usage: ft_ls [-lRart] [file...]");
}

void	print_illegal_option(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
}
