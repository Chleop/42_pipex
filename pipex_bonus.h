/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:03:39 by cproesch          #+#    #+#             */
/*   Updated: 2021/10/30 14:03:42 by cproesch         ###   ########.fr       */
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
	int		pipefd[1025][2];
	char	**cmd[1026];
	char	*cmd_path[1026];
	int		max_cmd;
	int		input;
	int		output;
	int		child[1026];
}	t_data;

char	*find_path(char **envp, char *cmd);
void	error_message(char *error_message, t_data **data);
void	ft_del_stringtab(char **tab);
void	ft_exit(t_data **data, int exit_code);
void	child0_process(t_data *data, char **argv, char **envp);
void	childx_process(t_data *data, char **argv, char **envp, int x);
void	childn_process(t_data *data, char **argv, char **envp, int x);
int		open_read(char *file);
int		open_write(char *file);
char	**parse_cmd(char *argv);
void	exec_command(t_data *data, char **envp, char *cmd, int x);

#endif