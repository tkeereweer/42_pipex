/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:40:22 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/04 10:24:25 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_helper(unsigned int n, char *base, int ret)
{
	if (n < 16)
		ret += ft_putchar(base[n]);
	else
	{
		ret = ft_puthex_helper(n / 16, base, ret);
		ret = ft_puthex_helper(n % 16, base, ret);
	}
	return (ret);
}

int	ft_puthex(unsigned int n, int cap, t_format *format)
{
	char	base[17];

	if (cap == 0)
		ft_strlcpy(base, "0123456789abcdef", 17);
	else
		ft_strlcpy(base, "0123456789ABCDEF", 17);
	if (format->ht == 1 && cap == 0 && n != 0)
	{
		write(1, "0x", 2);
		return (ft_puthex_helper(n, base, 0) + 2);
	}
	else if (format->ht == 1 && cap == 1 && n != 0)
	{
		write(1, "0X", 2);
		return (ft_puthex_helper(n, base, 0) + 2);
	}
	else
		return (ft_puthex_helper(n, base, 0));
}
