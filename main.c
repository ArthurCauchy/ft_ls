/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:36:33 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/14 18:59:52 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	char	*options;

	if (!(options = ft_strnew(5)))
		exit_error();
	read_params(argc, argv, options);
	ft_putendl(options);
	return (EXIT_SUCCESS);
}
