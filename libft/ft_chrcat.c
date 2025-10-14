/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:56:25 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/06 17:06:07 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chrcat(char *dest, int c)
{
	size_t	i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	dest[i] = c;
	dest[i + 1] = '\0';
	return (dest);
}
