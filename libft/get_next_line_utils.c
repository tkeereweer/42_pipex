/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:23:30 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/06 17:19:44 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_realloc_gnl(char *ptr, size_t size)
{
	char	*out;

	out = (char *) malloc(size);
	if (out == (void *) 0)
	{
		if (ptr != (void *) 0)
			free(ptr);
		return (out);
	}
	ft_strcpy(out, ptr);
	if (ptr != (void *) 0)
		free(ptr);
	return (out);
}

int	eol_found(char *line)
{
	int	i;

	i = 0;
	if (line == (void *) 0)
		return (-1);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
