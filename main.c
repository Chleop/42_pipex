/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:59:40 by cproesch          #+#    #+#             */
/*   Updated: 2021/10/28 17:53:08 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_process1(t_data *data, char **argv, char **envp)
{
	data->child1 = fork();
	if (data->child1 == -1)
		error_message("error - First fork function failed", NULL);
	if (data->child1 == 0)
		child1_process(data, argv, envp);
}

void	create_process2(t_data *data, char **argv, char **envp)
{
	data->child2 = fork();
	if (data->child2 == -1)
		error_message("error - Second fork function failed", NULL);
	if (data->child2 == 0)
		child2_process(data, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 5)
		error_message("error - Argts must be of type\"file cmd cmd file\"", NULL);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		error_message("error - Data malloc failed", NULL);
	if (pipe(data->pipefd) == -1)
		error_message("error - Pipe function failed", NULL);
	create_process1(data, argv, envp);
	create_process2(data, argv, envp);
	close(data->pipefd[1]);
	close(data->pipefd[0]);
	waitpid(data->child1, NULL, 0);
	waitpid(data->child2, NULL, 0);
	ft_exit(&data, 0);
	return (0);
}
