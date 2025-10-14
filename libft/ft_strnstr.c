/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:11:40 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/12 14:32:34 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_n;
	char	*ptr;

	i = 0;
	len_n = ft_strlen(needle);
	if (len_n == 0)
		return ((char *) haystack);
	if (len == 0)
		return ((void *) 0);
	while (haystack[i] != '\0' && i < len && len - i >= len_n)
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(&haystack[i], needle, len_n) == 0)
			{
				ptr = (char *) &haystack[i];
				return (ptr);
			}
		}
		i++;
	}
	return ((void *) 0);
}
