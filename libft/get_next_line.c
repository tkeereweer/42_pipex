/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:12 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/06 17:20:27 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*init_var(char *line, int fd, char *out, int mode)
{
	int	cnt;

	if (mode == 0)
	{
		line = ft_realloc_gnl(line, BUFFER_SIZE + 1);
		if (line == (void *) 0)
			return (line);
		cnt = read(fd, line, BUFFER_SIZE);
		if (cnt == -1 || cnt == 0)
		{
			free(line);
			line = (void *) 0;
		}
		else
			line[cnt] = '\0';
		return (line);
	}
	else
	{
		out = (char *) malloc(1 * sizeof(char));
		if (out == (void *) 0)
			return (out);
		out[0] = '\0';
		return (out);
	}
}

static char	*ret_null(char **line, char *out)
{
	free(out);
	free(*line);
	*line = (void *) 0;
	out = (void *) 0;
	return (out);
}

static char	*return_line(char *out, char *line)
{
	out = ft_realloc_gnl(out, ft_strlen(out) + ft_strlen(line) + 1);
	if (out == (void *) 0)
		return (out);
	ft_strncat(out, line, eol_found(line) + 1);
	ft_strcpy(line, &line[eol_found(line) + 1]);
	return (out);
}

static int	read_line(char **out, char *line, int fd)
{
	int	cnt;

	*out = ft_realloc_gnl(*out, ft_strlen(*out) + ft_strlen(line) + 1);
	if (*out == (void *) 0)
		return (-1);
	ft_strncat(*out, line, ft_strlen(line));
	cnt = read(fd, line, BUFFER_SIZE);
	if (cnt != -1)
		line[cnt] = '\0';
	return (cnt);
}

char	*get_next_line(int fd)
{
	char			*out;
	static char		*line;
	int				cnt;

	if (line == (void *) 0)
	{
		line = init_var(line, fd, (void *) 0, 0);
		if (line == (void *) 0)
			return ((void *) 0);
	}
	cnt = -2;
	out = (void *) 0;
	out = init_var((void *) 0, fd, out, 1);
	if (out == (void *) 0)
		return (out);
	while (cnt != 0 && cnt != -1)
	{
		if (eol_found(line) != -1)
			return (return_line(out, line));
		cnt = read_line(&out, line, fd);
	}
	if (ft_strlen(out) == 0 || cnt == -1)
		out = ret_null(&line, out);
	return (out);
}
