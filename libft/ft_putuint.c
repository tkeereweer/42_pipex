/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:42:40 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/03 19:17:15 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putuint(unsigned int n, int ret)
{
	char			c;

	if (n < 10)
	{
		c = n + '0';
		ret += ft_putchar(c);
	}
	else
	{
		ret = ft_putuint(n / 10, ret);
		ret = ft_putuint(n % 10, ret);
	}
	return (ret);
}
