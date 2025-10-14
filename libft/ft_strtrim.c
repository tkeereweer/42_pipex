/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:09:09 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/08/30 15:38:22 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (s1 == (void *) 0)
		return ((void *) 0);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (ft_inset(s1[i], set) == 1 && s1[i] != '\0')
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_inset(s1[j], set) == 1 && j >= 0)
		j--;
	ptr = (char *) malloc(j - i + 2);
	if (ptr == (void *) 0)
		return (ptr);
	ft_strlcpy(ptr, &s1[i], j - i + 2);
	return (ptr);
}
