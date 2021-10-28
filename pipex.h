/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:15:22 by cproesch          #+#    #+#             */
/*   Updated: 2021/10/28 16:32:14 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**cmd1;
	char	*cmd1_path;
	char	**cmd2;
	char	*cmd2_path;
	int		input;
	int		output;
	int		pipefd[2];
	int		child1;
	int		child2;
}	t_data;

char	*find_path(char **envp, char *cmd);
void	error_message(char *error_message, t_data **data);
void	ft_del_stringtab(char **tab);
void	ft_exit(t_data **data, int exit_code);
void	child1_process(t_data *data, char **argv, char **envp);
void	child2_process(t_data *data, char **argv, char **envp);

#endif