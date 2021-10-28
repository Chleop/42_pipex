/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:24:39 by cproesch          #+#    #+#             */
/*   Updated: 2021/10/28 16:30:22 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file1(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror("error - open file1 failed");
	return (fd);
}

int	check_file2(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		perror("error - open file2 failed");
	return (fd);
}

char	**parse_cmd(char *argv)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(argv, ' ');
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	tab[i] = NULL;
	return (tab);
}

void	child1_process(t_data *data, char **argv, char **envp)
{
	close(data->pipefd[0]);
	data->input = check_file1(argv[1]);
	data->cmd1 = parse_cmd(argv[2]);
	data->cmd1_path = find_path(envp, data->cmd1[0]);
	if (!data->cmd1 || !(data->cmd1_path))
		perror("cmd1 path error");
	dup2(data->input, 0);
	dup2(data->pipefd[1], 1);
	close(data->pipefd[1]);
	if (execve(data->cmd1_path, data->cmd1, envp) == -1)
		perror("error - Second exceve failed");
	return ;
}

void	child2_process(t_data *data, char **argv, char **envp)
{
	close(data->pipefd[1]);
	data->output = check_file2(argv[4]);
	data->cmd2 = parse_cmd(argv[3]);
	data->cmd2_path = find_path(envp, data->cmd2[0]);
	if (!data->cmd2 || !(data->cmd2_path))
		perror("cmd2 path error");
	dup2(data->output, 1);
	dup2(data->pipefd[0], 0);
	close(data->pipefd[0]);
	if (execve(data->cmd2_path, data->cmd2, envp) == -1)
		perror("error - First exceve failed");
}
