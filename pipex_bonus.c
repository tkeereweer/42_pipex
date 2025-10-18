/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:59:10 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/18 15:39:47 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_cmd - 1)
	{
		data->pipe_arr[i] = (int *) malloc(2 * sizeof(int));
		if (data->pipe_arr[i] == (void *) 0)
			return (0);
		if (pipe(data->pipe_arr[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

void	close_pipes(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->num_cmd - 1)
	{
		if (j == i)
			close(data->pipe_arr[j][0]);
		else if (j == i - 1)
			close(data->pipe_arr[j][1]);
		else
		{
			close(data->pipe_arr[j][0]);
			close(data->pipe_arr[j][1]);
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

int	run_first_cmd(t_data *data, int	i)
{
	int	fd_in;

	close_pipes(data, i);
	fd_in = open(data->argv[1], O_RDONLY);
	if (fd_in == -1)
		return (0);
	if (exec_cmd(data->argv[i + 2], fd_in, data->pipe_arr[i][1]) == -1)
		return (0);
	return (1);
}

int	run_last_cmd(t_data *data, int i)
{
	int	fd_out;

	close_pipes(data, i);
	fd_out = open(data->argv[i + 3], O_WRONLY);
	if (fd_out == -1)
		return (0);
	if (exec_cmd(data->argv[i + 2], data->pipe_arr[i - 1][0], fd_out) == -1)
		return (0);
	return (1);	
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;
	pid_t	pid;

	if (argc < 4)
		return (1);
	data.num_cmd = argc - 3;
	data.pipe_arr = (int **) malloc((data.num_cmd - 1) * sizeof(int*));
	if (data.pipe_arr == NULL)
		return (1);
	data.argv = argv;
	create_pipes(&data);
	i = 0;
	while (i < data.num_cmd)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			if (i == 0)
				run_first_cmd(&data, i);
			else if (i == data.num_cmd - 1)
				run_last_cmd(&data, i);
			else
			{
				close_pipes(&data, i);
				exec_cmd(argv[i + 2], data.pipe_arr[i - 1][0], data.pipe_arr[i][1]);
			}
		}
		i++;
	}
	if (pid != 0)
	{
		close_pipes(&data, -1);
		waitpid(pid, NULL, 0);
	}
}
