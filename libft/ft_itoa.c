/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:42:10 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/06 17:05:02 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	int_to_str(char *out, unsigned int nb)
{
	if (nb < 10)
	{
		ft_chrcat(out, nb + '0');
	}
	else
	{
		int_to_str(out, nb / 10);
		int_to_str(out, nb % 10);
	}
}

char	*ft_itoa(int n)
{
	char			*out;
	unsigned int	nb;

	out = (char *) malloc(12 * sizeof(char));
	if (out == (void *) 0)
		return (out);
	if (n < 0)
	{
		out[0] = '-';
		out[1] = '\0';
		nb = -n;
	}
	else
	{
		nb = n;
		out[0] = '\0';
	}
	int_to_str(out, nb);
	return (out);
}
