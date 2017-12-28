/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <acauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:56:35 by acauchy           #+#    #+#             */
/*   Updated: 2017/12/21 16:55:43 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	print_padding(int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		ft_putchar(' ');
		++i;
	}
}

static void	printnnbr(long long nbr, int *i, int n)
{
	if ((n == 0 || *i < n) && nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
		++*i;
	}
	if ((n == 0 || *i < n) && nbr > 9)
	{
		printnnbr(nbr / 10, i, n);
		printnnbr(nbr % 10, i, n);
	}
	else if (n != 0 && *i >= n)
		return ;
	else
	{
		ft_putchar('0' + nbr);
		++*i;
	}
}

void		print_errortype(t_arg *arg, void *realarg)
{
	realarg = arg;
	arg = realarg;
	ft_putstr("(type error)");
}

void		print_integer(t_arg *arg, void *realarg)
{
	int			nbr;
	int			len;
	int			padding;
	int			i;
	
	nbr = *(int*)realarg;
	len = ft_nbrlen(nbr);
	padding = arg->width - len;
	i = 0;
	if (!arg->alignleft)
		print_padding(padding);
	printnnbr(nbr, &i, arg->width);
	if (arg->alignleft)
		print_padding(padding);
}

void		print_string(t_arg *arg, void *realarg)
{
	char	*str;
	int		len;
	int		padding;
	int		i;

	str = (char*)realarg;
	len = ft_strlen(realarg);
	padding = arg->width - len;
	i = 0;
	if (!arg->alignleft)
		print_padding(padding);
	while (i < len && (arg->width == 0 || i < arg->width))
	{
		write(1, str + i, 1);
		++i;
	}
	if (arg->alignleft)
		print_padding(padding);
}
