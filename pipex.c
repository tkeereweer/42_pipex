/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:51:24 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/14 15:38:28 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/libft.h"

int	exec_cmd(char *cmd, int fd_in, int fd_out)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	cmd_path = ft_strjoin("/bin/", args[0]);
	if (dup2(fd_in, 0) == -1)
		return (-1); // handle error
	if (dup2(fd_out, 1) == -1)
		return (-1); // handle error
	return (execve(cmd_path, args, NULL));
}

int	run_child_one(char *argv[], int pipefd[2])
{
	int	fd_in;

	close(pipefd[0]);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		close(pipefd[1]);
		return (0); // handle error
	}
	if (exec_cmd(argv[2], fd_in, pipefd[1]) == -1)
		return (0);
	return (1);
}

void	run_child_two(char *argv[], int pipefd[2])
{
	int	fd_out;

	close(pipefd[1]);
	fd_out = open(argv[4], O_WRONLY);
	if (fd_out == -1)
	{
		close(pipefd[0]);
		return ; // handle error
	}
	exec_cmd(argv[3], pipefd[0], fd_out);
}

void	exit_process(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		pipefd[2];
	int		status;

	if (argc != 5)
		return (1);
	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		exit_process(pipefd);
	if (pid == 0)
	{
		if (!run_child_one(argv, pipefd))
			return (1);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			exit_process(pipefd);
		if (pid == 0)
			run_child_two(argv, pipefd);
		else
		{
			close(pipefd[0]);
			close(pipefd[1]);
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
