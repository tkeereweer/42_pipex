/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:42:40 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/04 10:33:44 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_helper(unsigned int nb, int ret)
{
	char			c;

	if (nb < 10)
	{
		c = nb + '0';
		ret += ft_putchar(c);
	}
	else
	{
		ret = ft_putnbr_helper(nb / 10, ret);
		ret = ft_putnbr_helper(nb % 10, ret);
	}
	return (ret);
}

int	ft_putnbr(int n, t_format *format)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		ft_putchar('-');
		return (ft_putnbr_helper(nb, 0) + 1);
	}
	else
		nb = n;
	if (format->plus == 1)
	{
		write(1, "+", 1);
		return (ft_putnbr_helper(nb, 0) + 1);
	}
	else if (format->space == 1)
	{
		write(1, " ", 1);
		return (ft_putnbr_helper(nb, 0) + 1);
	}
	else
		return (ft_putnbr_helper(nb, 0));
}
