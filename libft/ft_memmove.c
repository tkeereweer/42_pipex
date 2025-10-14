/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:42:18 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/29 18:44:00 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_move(unsigned char *str_dst, unsigned char *str_src, int i_len)
{
	int	i;

	if (str_dst <= str_src)
	{
		i = 0;
		while (i < i_len)
		{
			str_dst[i] = str_src[i];
			i++;
		}
	}
	else
	{
		i = i_len - 1;
		while (i >= 0)
		{
			str_dst[i] = str_src[i];
			i--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				i_len;
	unsigned char	*str_dst;
	unsigned char	*str_src;

	if (src == (void *) 0 && dst == (void *) 0)
		return (dst);
	i_len = (int) len;
	str_dst = (unsigned char *) dst;
	str_src = (unsigned char *) src;
	ft_move(str_dst, str_src, i_len);
	return (dst);
}
