/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:59:40 by cproesch          #+#    #+#             */
/*   Updated: 2021/10/30 14:05:01 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_process0(t_data *data, char **argv, char **envp)
{
	(data->child)[0] = fork();
	if ((data->child)[0] == -1)
		error_message("error - First fork function failed", NULL);
	if ((data->child)[0] == 0)
		child0_process(data, argv, envp);
}

void	create_processx(t_data *data, char **argv, char **envp, int x)
{
	(data->child)[x] = fork();
	if ((data->child)[x] == -1)
		error_message("error - Fork function failed", NULL);
	if ((data->child)[x] == 0)
		childx_process(data, argv, envp, x);
	close(data->pipefd[x - 1][0]);
	close(data->pipefd[x - 1][1]);
}

void	create_processn(t_data *data, char **argv, char **envp, int x)
{
	(data->child)[x] = fork();
	if ((data->child)[x] == -1)
		error_message("error - Last fork function failed", NULL);
	if ((data->child)[x] == 0)
		childn_process(data, argv, envp, x);
	close(data->pipefd[x - 1][0]);
	close(data->pipefd[x - 1][1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		x;

	if (argc < 5)
		error_message("error - Argts must be as \"file cmd ... cmd file\"", NULL);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		error_message("error - Data malloc failed", NULL);
	data->max_cmd = argc - 3;
	x = -1;
	while (++x < (data->max_cmd - 1))
	{
		if (pipe((data->pipefd)[x]) == -1)
			error_message("error - Pipe function failed", NULL);
	}
	create_process0(data, argv, envp);
	x = 0;
	while (++x < (data->max_cmd - 1))
		create_processx(data, argv, envp, x);
	create_processn(data, argv, envp, x);
	x = -1;
	while (++x < data->max_cmd)
		waitpid((data->child)[x], NULL, 0);
	ft_exit(&data, 0);
	return (0);
}
