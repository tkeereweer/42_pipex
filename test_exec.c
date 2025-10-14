/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:41:15 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/14 15:01:17 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/libft.h"
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	char	**args;
	char	*cmd_path;
	int		fd_in;
	int		fd_out;

	if (argc != 5)
		return (1);
	args = ft_split(argv[2], ' ');
	cmd_path = ft_strjoin("/bin/", args[0]);
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[4], O_WRONLY);
	if (fd_in != -1)
	{
		if (dup2(fd_in, 0) == -1)
			return (0); // handle error
	}
	if (fd_out != -1)
	{
		if (dup2(fd_out, 1) == -1)
			return (0); // handle error
	}
	execve(cmd_path, args, NULL);
	return (0);
}
