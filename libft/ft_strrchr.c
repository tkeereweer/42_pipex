/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:43:25 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/29 17:53:16 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*out;
	char	ch;

	i = 0;
	out = (void *) 0;
	ch = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			out = (char *) &s[i];
		i++;
	}
	if (s[i] == ch)
		out = (char *) &s[i];
	return (out);
}
