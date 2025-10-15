/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:59:10 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/15 15:31:53 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/libft.h"

int	create_pipes(int argc, int **pipe_arr)
{
	int	i;

	i = 1;
	while (i < argc - 3)
	{
		if (pipe(pipe_arr[i]) == -1)
			return (0);
		i++;
	}
}

int	run_first_cmd()
{

}

int	close_pipes(int argc, int **pipe_arr, int i)
{
	int	j;

	j = 1;
	while (j < argc  - 4)
	{
		if (j == i)
			close(pipe_arr[j][0]);
		else if (j == i + 1)
			close(pipe_arr[j][1]);
		else
		{
			close(pipe_arr[j][0]);
			close(pipe_arr[j][1]);
		}
		j++;
	}
}

int	exec_cmd(char *cmd, int fd_in, int fd_out)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	cmd_path = ft_strjoin("/bin/", args[0]);
	if (dup2(fd_in, 0) == -1)
		return (-1);
	if (dup2(fd_out, 1) == -1)
		return (-1);
	return (execve(cmd_path, args, NULL));
}

int	main(int argc, char *argv[])
{
	int	**pipe_arr;
	int	i;
	pid_t	pid;

	if (argc < 4)
		return (1);
	pipe_arr = (int **) malloc((argc - 1) * sizeof(int[2]));
	if (pipe_arr == NULL)
		return (1);
	create_pipes(argc, pipe_arr);
	i = 0;
	while (i < argc - 3)
	{
		pid = fork();
		if (pid == -1);
			return (1);
		if (pid == 0)
		{
			if (i == 0)
				// call function for first command
			else if (i == argc - 4)
				// call function for last command
			else
			{
				close_pipes(argc, pipe_arr, i);
				exec_cmd(argv[i + 2], pipe_arr[i][1], pipe_arr[i + 1][0]);
			}
		}
	}
}
