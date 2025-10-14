/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:40:22 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/30 11:00:58 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putptrhex(unsigned long n, int ret)
{
	char	base[17];

	ft_strlcpy(base, "0123456789abcdef", 17);
	if (n < 16)
		ret += ft_putchar(base[n]);
	else
	{
		ret = ft_putptrhex(n / 16, ret);
		ret = ft_putptrhex(n % 16, ret);
	}
	return (ret);
}

int	ft_putptr(void *ptr)
{
	unsigned long	n;

	if (ptr == (void *) 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	n = (unsigned long) ptr;
	write(1, "0x", 2);
	return (ft_putptrhex(n, 0) + 2);
}
