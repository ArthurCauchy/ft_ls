/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:40:01 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/14 18:56:33 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>

# include <stdlib.h>
# include "libft.h"

/*
** output.c
*/

void	print_error(void);
void	print_usage(void);
void	print_illegal_option(char c);

/*
** utils.c
*/

void	exit_error(void);

/*
** options.c
*/

void	read_params(int argc, char **argv, char *options/*, t_flist *flist*/);

#endif
