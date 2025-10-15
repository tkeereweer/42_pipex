/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:51:24 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/15 13:57:37 by mkeerewe         ###   ########.fr       */
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
		return (-1);
	if (dup2(fd_out, 1) == -1)
		return (-1);
	return (execve(cmd_path, args, NULL));
}

int	run_first_cmd(char *argv[], int pipefd[2])
{
	int	fd_in;

	close(pipefd[0]);
	ft_printf("%s", "child one");
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		close(pipefd[1]);
		return (0);
	}
	if (exec_cmd(argv[2], fd_in, pipefd[1]) == -1)
		return (0);
	return (1);
}

void	run_last_cmd(int argc, char *argv[], int pipefd[2])
{
	int	fd_out;

	close(pipefd[1]);
	ft_printf("%s", "child two");
	fd_out = open(argv[argc - 1], O_WRONLY);
	if (fd_out == -1)
	{
		close(pipefd[0]);
		return ;
	}
	exec_cmd(argv[argc - 2], pipefd[0], fd_out);
}

void	exit_process(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}

int	main(int argc, char *argv[])
{
	int		i;
	pid_t	pid;
	int		pipeafd[2];
	int		pipebfd[2];

	if (argc < 4)
		return (1);
	if (pipe(pipeafd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		exit_process(pipeafd);
	if (pid == 0)
	{
		if (!run_first_cmd(argv, pipeafd))
			return (1);
	}
	else
	{
		i = 3;
		while (i < argc - 2)
		{
			// if (dup2(pipeafd[0], pipebfd[1]) == -1)
			// 	return (1);
			if (pipe(pipebfd) == -1)
				return (1);
			pid = fork();
			if (pid == -1)
				return (1);
			if (pid == 0)
			{
				close(pipeafd[1]);
				close(pipebfd[0]);
				exec_cmd(argv[i], pipeafd[0], pipebfd[1]);
			}
			else
			{
				close(pipeafd[0]);
				close(pipeafd[1]);
				i++;
			}
		}
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			if (i == 0)
			{
				if (pipe(pipebfd) == -1)
					return (1);
				if (dup2(pipebfd[0], pipeafd[1]) == -1)
					return (1);
				close(pipeafd[0]);
				close(pipeafd[1]);
			}
			run_last_cmd(argc, argv, pipebfd);
		}
		else
		{
			if (i == 3)
			{
				close(pipeafd[0]);
				close(pipeafd[1]);
			}
			close(pipebfd[0]);
			close(pipebfd[1]);
			waitpid(pid, NULL, 0);
		}
	}
}
